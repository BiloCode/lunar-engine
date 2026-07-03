# Vector2i

2D vector with integer components.

## Constructor

```ruby
Vector2i.new
Vector2i.new(x, y)
Vector2i.new(vector)
```

- `x` — `Integer` — X component
- `y` — `Integer` — Y component
- `vector` — `Vector2i` or `Vector2f` — vector to copy from

## Properties

| Property | Type | Access |
|---|---|---|
| `x` / `x=` | `Integer` | read-write |
| `y` / `y=` | `Integer` | read-write |

## Methods

| Method | Returns |
|---|---|
| [`to_s`](#to_s) | `String` |
| [`inspect`](#inspect) | `String` |

---

### to_s

```ruby
vec.to_s
```

Returns a string representation of the vector.

### inspect

```ruby
vec.inspect
```

Returns a debug-friendly string representation.
