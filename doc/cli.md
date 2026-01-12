# cli

---

The CLI is the official and primary client for accessing HyprProf. Primarily, hyprprof was developed to be a static library, so that multiple clients could connect to it via pipes from the proprietary CLI or by compiling and creating their own versions, opening the way for graphical interfaces in the future.

## `prof` commands 

`prof install <file/url>`:

- Install the hyprprof environment on your machine, running the entire execution pipeline.
  It is recommended to use sudo when using it. It can install dependencies if necessary.

`prof export <name>`:

- Export your environment to a tangible profile for hyprprof as a .hyprprof file.

  That is: scan folders, find, copy files, and create a JSON.

`prof info`

- Information about your profile, such as the name, version, and, if retrieved by URL, the repository.
