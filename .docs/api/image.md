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
