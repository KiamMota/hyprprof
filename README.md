# HyprProf — Your Hyprland Super Toolkit 🛠️

Hyprprof is like a magic wand for your Hyprland setup. It lets you pack all your favorite configs, dotfiles, and tools into a neat, shareable profile so you can summon your perfect workspace anywhere.

## Features ✨

* **Core Components Configuration**: Set up your terminal, launcher, notification system, and status bar effortlessly.
* **Providers**: Control your wallpaper, screenshots, clipboard, and screen recording tools.
* **Build Scripts**: Automate installations, uninstallations, and other setup spells.
* **Version Constraints**: Make sure your profile only works with Hyprland or Wayland versions that won't break your magic.
* **Portable & Shareable**: Move profiles across systems without losing your mojo.

## Getting Started 🚀

### Quick Installation

Clone, build, and install in one swoop:

```bash
git clone https://github.com/KiamMota/hyprprof.git
cd hyprprof

mkdir build
cd build
cmake ..                 # configure
make -j$(nproc)          # build
sudo make install         # install binary and configs

cd ..
rm -rf ./*               # clean up leftover junk
```

### Repository Setup

Prefer just cloning and running a script? Easy:

```bash
git clone https://github.com/KiamMota/hyprprof.git
cd hyprprof
./install.sh
```

## CLI Commands 🧙‍♂️

* `install <path/url>` — Bring a profile from somewhere else into your system.
* `use <name>` — Activate a profile to cast its magic.
* `using` — See which profile is currently active.
* `list` — Peek at all your installed profiles.
* `remove <name|current>` — Delete a profile that you no longer need.

## Documentation

For the nerdy deep-dive:

* Start [here!](https://github.com/KiamMota/hyprprof/blob/main/doc/create_profile.md)

Go forth, young wizard, and make your Hyprland experience magical!
