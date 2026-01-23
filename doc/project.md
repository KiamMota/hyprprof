# HyprProf Architecture — Layer Rules

This document defines **strict, non-negotiable rules** for each layer of HyprProf.
The goal is not flexibility. The goal is **clarity, scalability, and long-term sanity**.

---

## Core Layer (`core/`)

### Purpose

The **Core** is the *mind* of the system.
It knows **what is valid**, **what is allowed**, and **what must happen** — but never **how it happens**.

### Allowed

* Business rules
* Domain validation
* Policy enforcement
* Domain models (immutable where possible)
* Pure decision-making logic
* Returning `bool`, `Result`, or throwing **domain-level exceptions**

### Forbidden

* File system writes or execution
* Network access
* Process execution
* Logging
* Printing
* Environment inspection with side effects

### Important Clarification

If the core **touches the real world**, it stops being a core.

Reading the filesystem *only* to **detect state** (no mutation, no execution) is tolerated **only if abstracted and replaceable** — otherwise it belongs in infra.

### Design Principle

> The core must be testable without a machine.

If a rule cannot be tested without the OS, the rule is misplaced.

---

## Infrastructure Layer (`infra/`)

### Purpose

The **Infrastructure** is the system’s *hands*.
It touches the operating system, filesystem, shell, network, pipes, and processes.

### Allowed

* File system manipulation
* Process execution
* Shell script execution
* Logging
* Network calls
* OS-specific behavior
* Exception throwing (technical exceptions)

### Forbidden

* Business rules
* Validation logic
* Decision-making
* Conditional behavior based on domain meaning

### Why Infra Looks Like Utilities

Infra functions may look like utilities (e.g. `make_bak()`), but they are **deliberately dumb**.

They do **one thing**, predictably, without understanding *why* it is needed.

### Design Principle

> Infra executes. It does not decide.

If infra starts asking *"should I?"*, the design is broken.

---

## Application Layer (`app/`)

### Purpose

The **Application** layer is the *orchestrator*.
It coordinates **what happens first, second, and last**.

### Allowed

* Calling core validators and policies
* Calling infra actuators
* Managing pipelines
* Translating domain intent into execution order

### Forbidden

* Deep validation logic
* Low-level OS operations
* Large conditional trees

### Responsibility

The app layer answers:

* *Which rule applies now?*
* *Which infra action executes it?*

It never invents rules. It only **applies them**.

### Design Principle

> The app layer is a conductor, not a composer.

---

## CLI Layer (`cli/`)

### Purpose

The **CLI** is the official gateway.
It translates **human intent** into application commands.

### Allowed

* Argument parsing
* Command routing
* User feedback
* Calling application services

### Forbidden

* Business rules
* File manipulation
* Pipeline logic

### Responsibility

The CLI must remain **replaceable**.
If tomorrow CLI is replaced by RPC or GUI, the system must survive unchanged.

### Design Principle

> The CLI is a client — not the system.

---

## Cross-Layer Rules

### Dependency Direction

```
CLI → App → Core
        ↓
      Infra
```

* Core depends on **nothing**
* Infra depends on **nothing**
* App depends on Core and Infra
* CLI depends only on App

### Exception Policy

* Core: domain exceptions or boolean results
* Infra: technical exceptions
* App: handles mapping between them
* CLI: reports to user


Architecture is not about *power*.
It is about **containment**.
