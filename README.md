# How HyprProf Works

HyprProf is a simple tool to **import and export Hyprland configurations** between different systems using a structured payload. It relies on a specific folder layout and a manifest file (`hyprprof.json`) to work correctly.

## Dependencies

Inside the HyprProf folder, the following structure and files are required:

### Manifest File: `hyprprof.json`

This JSON file acts as the main descriptor of your profile. It must include:

```json
{
  "schema": "hyprprof/x.x",
  "hyprprof": {
    "profile_name": "your-profile-name",
    "version": "x.x",
    "dependencies": {}
  }
}
```

`schema`: A string indicating the schema version of the HyprProf profile. It must appear at the root of the JSON file, e.g., "hyprprof/1.0".

`hyprprof`: Root object containing the main profile information.

`hyprprof.profile_name` (required): The name of your profile.

`hyprprof.version` (required): The version of your profile.

`dependencies` (required, but can be empty initially): An object reserved for listing external dependencies such as tools, scripts, or sources needed by your setup.

## Payload Folder: payload/

The `payload/` directory must exist inside your HyprProf folder and cannot be empty. 
It contains subfolders representing different components of your Hyprland configuration:

`payload/hyprland/`

Place all .conf files for Hyprland here.
(Backgrounds should be in payload/hyprland/bg/).

`payload/bar/`

Contains all configuration files for your bar setup.
All these subfolders are mandatory if they exist in the payload and must not be empty.

HyprProf works by reading the hyprprof.json manifest and the structured payload folder. It ensures that profiles are portable and reproducible 
across systems, with all necessary configurations and assets in their expected locations. Proper folder structure and required JSON fields are crucial for HyprProf to function correctly.
