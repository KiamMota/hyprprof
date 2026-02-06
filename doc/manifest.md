# Hyprprof Manifest Explained — Detailed Guide

This document provides a detailed explanation of each field in the Hyprprof manifest, describing not just the syntax and validation rules, but also **what each field represents within the system**, how it is used, and why it matters.

---

## `hyprprof`

The `hyprprof` object contains general information about the profile. It defines the profile's identity and serves as a reference for both the system and the user.

* **`authors`**

  * An array of the profile's authors.
  * **Why it exists:** Records who created or maintains the profile. Useful for documentation, accountability, and tracking changes.
  * **How it is used:** Displayed in the CLI or TUI, but does not affect profile execution.

* **`name`**

  * The unique name of the profile.
  * **Why it exists:** This field is **the primary identifier of the profile within the Hyprprof system**. All configuration files and directories are organized based on this name.
  * **How it is used:** Used as a reference for commands like `use <name>`, `remove <name>`, and to locate the profile in `~/.config/hyprprof/<name>`.
  * **Rules:** Must contain only letters and underscores, and cannot be empty.

* **`version`**

  * The version of the profile.
  * **Why it exists:** Allows tracking updates and compatibility. Profiles can evolve with fixes or layout changes.
  * **How it is used:** Hyprprof checks versions to warn about potential incompatibilities or significant changes.

* **`description`**

  * A short description of the profile.
  * **Why it exists:** Helps users understand the purpose and function of the profile.
  * **How it is used:** Shown in the CLI or TUI when listing profiles or viewing profile details, purely informational.
