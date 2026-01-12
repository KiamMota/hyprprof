# **hyprprof.json**

---



Before any validation, the HyprProf engine will first look for this file in the target directory or .hyprprof file that the user provides.

These are the objects that the manifesto allows:

`schema`: string (required).

- This instructs the JSON interpreter on the schema it should follow.

  Internally, hyprprof has a rule specified by a json file, which it interprets as a yacc to validate other manifests.
  
  NOTE: It follows the "hyperprof/a.b" pattern.

`"hyprprof"`: object (required).

- `name`: string (required).

  - your hyprprof profile name
  - It should not contain spaces, special characters such as commas, accents, or exclamation marks

- `version` : string (required).

  - The version of your HyprProf profile.
  - The field value follows an a.b.c. rule.

- `scripts`: string array (optional).

  - This allows HyprProf to run the scripts you provide.

    NOTE: The scripts are stored in a list and will be executed in the same sequence they were entered into the array.
    These scripts will be searched for in the scripts/ folder.

    No need to specify any directory, just the names.
  

---

example:

``` json
{
  "schema": "hyprprof/0.1",
 
  "hyprprof": {
    "name": "MySimpleProfile",
    "version": "1.0.0",
    "scripts": [
      "script1.sh",
      "script2.sh"
    ]
  }
}
```
