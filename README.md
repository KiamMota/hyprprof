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


