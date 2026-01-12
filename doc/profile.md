Every profile must have the following folder structure (based on the hyprprof/0.1 schema)

``` ascii
your_profile/
├── hyprprof.json
├── scripts/
└── payload/
    ├── hyprland/
    ├── bg/
    └── bar/           (optional, conditional)

```

First, it must have the hyprprof.json file, which is the [manifest](https://github.com/KiamMota/hyprprof/blob/main/doc/manifest.md) that hyprprof will look for and read.

Secondly: the profile must have a directory called "payload," where all the files and settings for porting the environment are located.
These are the required directories that CANNOT be empty:

- `scripts` (if present)
  - If this directory exists, the scripts and their order must be specified in the [manifest](https://github.com/KiamMota/hyprprof/blob/main/doc/manifest.md).

`payload/`
- `payload/hyprland`
  - Here is your complete Hyprland configuration, and the necessary files.
- `payload/bar` (if present)
  - This is where your toolbar configuration should be located. If this folder exists, the toolbar type should be added to the [manifest](https://github.com/KiamMota/hyprprof/blob/main/doc/manifest.md).
- `payload/bg` (if present)
  - Your background files should be located here; once installed, they will be created within the hyprland/bg/ directory.
