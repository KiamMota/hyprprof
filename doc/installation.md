# Hyprprof Installation Pipeline

This document explains the step-by-step process of the Hyprprof profile installation pipeline, detailing how a profile is validated, parsed, and installed.

## Installation Pipeline Steps

1. **Profile Layout Analysis**

   * The path provided by the user is analyzed.
   * Hyprprof generates an internal representation of the profile's folder structure.
   * The pipeline checks if all mandatory and optional folders/files are present, following the Hyprprof profile layout.

2. **Manifest Parsing**

   * Once the folder structure is validated, Hyprprof reads and parses the `hyprprof.json` manifest.
   * This manifest is used to generate the profile domain, which includes metadata such as name, authors, version, version constraints, and dotfile mappings.

3. **Destination Path Generation**

   * Hyprprof constructs the destination path for the profile in the user's system.
   * The path follows the format: `~/.config/hyprprof/<profile_name>`.

4. **Path Ensuring**

   * The pipeline ensures that critical paths exist:

     * `~/.config/hyprprof/` directory
     * `profile_list.json` file (to maintain the list of installed profiles)

5. **Profile Directory Creation and Moving**

   * A new directory is created for the profile using its name.
   * The profile content is moved into this directory.

6. **Updating Profile List**

   * The `profile_list.json` is updated to include the newly installed profile.
   * The new profile is marked as `current` in the list.

7. **Cleanup and Finalization**

   * Any temporary directories used during the installation are removed.
   * If all steps complete without errors, the profile is successfully installed and ready to be used via the `hyprprof use` command.
