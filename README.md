# How HyprProf Works

HyprProf is a simple tool to **import and export Hyprland configurations** between different systems using a structured payload. It relies on a specific folder layout and a manifest file (`hyprprof.json`) to work correctly.

---

## Directory Structure

```
profile/
├── hyprprof.json
└── payload/
    ├── hyprland/
    │   └── hyprconf
    ├── bg/            (optional)
    └── bar/           (optional, conditional)
```


