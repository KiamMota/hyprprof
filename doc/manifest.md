# **hyprprof.json**

---



This is the JSON manifest that the HyprProf engine looks for first before any validation.

These are the objects that the manifesto allows:

`"hyprprof"`: object (required).

- `hyprprof.name`: string (required).
- `hyprprof.version` : string (required).
- `hyprprof.run_scripts`: string array (optional).

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
}
```