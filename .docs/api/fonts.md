# Fonts (Module)

Module that acts as a font factory. Manages an internal `FontsCache`.

## Methods

| Method | Returns |
|---|---|
| [`get`](#get) | `Font` |

---

### get

```ruby
Fonts.get(name)
Fonts.get(name, size)
```

Loads a font by file name.

- `name` — `String` — font file name or path
- `size` — `Integer` (optional) — font size in pixels (defaults to 0)
