# HyprProf

HyprProf is a simple tool to import and export Hyprland configurations, between different systems using a structured payload.
Essentially, hyprprof serves to transfer profiles from hyprland in a simpler way.

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

## install 

To install, simply use this in your shell:
``` bash

git clone https://github.com/KiamMota/hyprprof.git 
cd hyprprof
chmod +x ./install.sh
./install.sh
```

## To understand more:

[structure](https://github.com/KiamMota/hyprprof/blob/main/doc/profile.md)

[hyprprof.json](https://github.com/KiamMota/hyprprof/blob/main/doc/manifest.md)

# usage 

To install profiles, simply:

``` bash
hyprprof prof install <path> 
```

to export your profile, simply:

``` bash
hyprprof prof export <profile_name>
```

to view your profile specifications:

``` bash
hyprprof prof info
```

info return example:

``` bash
profile name: my_profile
profile version: 1.0.0
```


