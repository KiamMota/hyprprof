# HyprProf

HyprProf is a simple tool to import and export Hyprland configurations, between different systems using a structured payload.

Hyprprof works with both .hyprprof files and folders, however they must all have the same structure:
``` ascii
your_profile/
├── hyprprof.json
└── payload/
    ├── hyprland/
    │   └── hyprconf
    |   └── bg/
    └── bar/           (optional, conditional)
```


