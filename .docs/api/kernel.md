# Kernel (Module)

Global engine methods available everywhere.

## Methods

| Method | Returns |
|---|---|
| [`cpp_set_scene`](#cpp_set_scene) | `nil` |
| [`cpp_set_background`](#cpp_set_background) | `nil` |

---

### cpp_set_scene

```ruby
cpp_set_scene(scene)
```

Switches the active scene. Calls `exit_tree` on the previous scene and `enter_tree` on the new one.

- `scene` — `Object` — the new scene object

### cpp_set_background

```ruby
cpp_set_background(color)
```

Sets the background color of the environment.

- `color` — `Color` — the background color
