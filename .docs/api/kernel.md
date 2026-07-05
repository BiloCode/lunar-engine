# Kernel (Module)

Global engine methods available everywhere.

## Methods

| Method | Returns |
|---|---|
| [`cpp_set_background`](#cpp_set_background) | `nil` (stub) |
| [`cpp_set_room`](#cpp_set_room) | `nil` |

---

### cpp_set_background

```ruby
cpp_set_background(color)
```

Not yet implemented (stub).

- `color` — `Color` — background color

### cpp_set_room

```ruby
cpp_set_room(room)
```

Switches the active room. Calls `exit_tree` on the previous room and `enter_tree` on the new one.

- `room` — `Object` — the new room object
