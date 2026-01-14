# installation

Installing a Hyprland profile on your system follows certain pipeline rules that must be adhered to.

## Validation 

### 1 - Manifest validation
  - In this part, the Hyperproof engine will pass your JSON to a JSON validation and parsing core, using the schema you specified.
    
### 2 - Folder structure validation
  - In this part, the engine will validate the entire directory structure, checking for folders, whether they are empty, and performing other validations.

### 3 - Script validation
  - In this third part, the profile scripts undergo validation and security testing with malicious script patterns, only then moving on to the next stage.

## Shoot

### 1 - Backup 
  - The installer will transfer all the configuration present in the directories that will be changed to a subdirectory within the folders called prof_backup/
    and insert the new profile using .bak files.

### 2 - Copy of the manifest
  - Copy the hyprprof.json manifest file to `.config/hypr/profile.json`

### 3 - Run the scripts
  - In this step, the environment scripts are executed sequentially.
  - You can run the configuration without running the scripts, more info [here](https://github.com/KiamMota/hyprprof/blob/main/doc/cli.md).

### 4 - Go!
  - In this final stage, the engine analyzes inconsistencies, does not leave partial states, and executes "hyprctl reload" via the pipe.
