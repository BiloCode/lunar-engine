# Vector2f

2D vector with floating-point components.

## Constructor

```ruby
Vector2f.new
Vector2f.new(x, y)
Vector2f.new(vector)
```

- `x` — `Float` — X component
- `y` — `Float` — Y component
- `vector` — `Vector2f` or `Vector2i` — vector to copy from

## Properties

| Property | Type | Access |
|---|---|---|
| `x` / `x=` | `Float` | read-write |
| `y` / `y=` | `Float` | read-write |

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
