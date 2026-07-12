---
name: api-docs-conventions
description: Conventions for documenting mruby binding classes in .docs/api/
---

## Source of Truth

The documentation is based on the binding files in `src/bindings/`. Each `r_xxx.cpp` defines what methods, properties, and constructors are exposed to mruby for a given class, and gets documented in a corresponding `.md` file.

## File Structure

```
.docs/
├── index.html          # docsify loader (CDN)
├── _sidebar.md         # navigation sidebar
├── README.md           # home page
└── api/
    └── *.md            # one file per class/module
```

## Document Structure per File

    # ClassName (Module)

    Brief description.

    ## Constructor

    ```ruby
    ClassName.new
    ClassName.new(param1, param2)
    ```

    - `param1` — `Type` — description
    - `param2` — `Type` — description

## Properties

Only include if the class has properties. Columns: Property, Type, Access.

| Property | Type | Access |
|---|---|---|
| `x` / `x=` | `Float` | read-write |
| `width` | `Integer` | read-only |

- `read-write` if has `=` setter
- `read-only` if only getter

## Methods

Table with clickable links:

| Method | Returns |
|---|---|
| [`method_name`](#method_name) | `ReturnType` |

Then below `---` separator, details for each method:

    ### method_name

    ```ruby
    object.method_name(param1, param2)
    ```

    Brief description.

    - `param1` — `Type` — description
    - `param2` — `Type` (optional) — description

## Key Rules

1. **Properties vs Methods**: if it has `=` setter → Property. Read-only getter → Property too. Everything else → Method.
2. **Every method with params** must follow: code example + description + parameter list.
3. **Constructors** follow same pattern as methods with params.
4. **Code examples**: no comments allowed (`# =>`, `# copy from...`, etc.). Just the call.
5. **Parameter list**: one parameter per line with `- \`name\` — \`Type\` — description`. Never comma-separated on one line.
6. **Placeholders** (no implementation): only class name and type (`Audio`, `Graphics (Module)`, `Input`).
7. **Labels in titles**: `(Module)` with capital M, `(stub)` lowercase.
8. **Home page** (`README.md`): architecture diagram centered with `<div align="center">`, "Examples" section with Ruby snippets.
