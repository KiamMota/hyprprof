# **hyprprof.json**

---



Before any validation, the HyprProf engine will first look for this file in the target directory or .hyprprof file that the user provides.

These are the objects that the manifesto allows:

`"hyprprof"`: object (required).

- `hyprprof.name`: string (required).

  - your hyprprof profile name

- `hyprprof.version` : string (required).

  - The version of your HyprProf profile.
  - The field value follows an a.b.c. rule.

- `hyprprof.run_scripts`: string array (optional).

  - This allows HyprProf to run the scripts you provide.

    NOTE: The scripts are stored in a list and will be executed in the same sequence they were entered into the array.

---

example:

``` json
{
  "hyprprof": {
    "name": "MeuPerfil",
    "version": "1.0.0",
    "run_scripts": [
      "script1.sh",
      "script2.sh"
    ]
  }
}
```