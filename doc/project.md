The HyprProf structure was designed to be scalable and focused on fixed pipelines. 
Although it follows some DDD principles and a bit of layer architecture, HyprProf uses its own internal structure.

`core/`
  - This layer is expected to contain validators, domain objects, and all business logic.
  - It does not emit I/O, but it can use fs to detect parts of the system, even without saving anything.

`infra/`
  - The part that actually deals with external things like file systems, networking, fork execution, or pipes.
  - It throws exceptions and can handle generic exceptions, but it's the caller's responsibility to handle those exceptions.

`app/`
  - This part manages all the system installation logic; it's the central point for accessing the entire system.
  - It doesn't validate on its own, it doesn't create huge functions, it calls actuators for that coming from `core/`.

`cli/`
  - The system's official gateway.
  - It calls the appservice through command interpretation in the CLI.

### specifications

Currently, hyprprof is a library, so the CLI acts as a client that calls this library.

In the future, it will accept RPC calls and similar services.
