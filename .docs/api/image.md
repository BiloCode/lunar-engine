# Image

Represents a loaded texture. Cannot be instantiated directly — obtain instances via `Graphics.load`.

## Constructor

```ruby
Image.new
```

Raises `RuntimeError`. Images are created through `Graphics.load`.

## Properties

| Property | Type | Access |
|---|---|---|
| `width` | `Integer` | read-only |
| `height` | `Integer` | read-only |

## Methods

| Method | Returns |
|---|---|
| [`to_s`](#to_s) | `String` |
| [`inspect`](#inspect) | `String` |

---

### to_s

```ruby
image.to_s
```

Returns a string representation of the image dimensions.

### inspect

```ruby
image.inspect
```

Returns a debug-friendly string representation of the image dimensions.
