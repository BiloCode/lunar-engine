# Bitmap

Represents a renderable canvas (2D).

## Constructor

```ruby
Bitmap.new
Bitmap.new(width, height)
```

- `width` — `Integer` — width in pixels
- `height` — `Integer` — height in pixels

## Properties

| Property | Type | Access |
|---|---|---|
| `width` | `Integer` | read-only |
| `height` | `Integer` | read-only |

## Methods

| Method | Returns |
|---|---|
| [`clear`](#clear) | `nil` |
| [`debug`](#debug) | `nil` |
| [`resize`](#resize) | `nil` |
| [`dispose`](#dispose) | `nil` |
| [`disposed?`](#disposed) | `Boolean` |
| [`draw_text`](#draw_text) | `nil` |
| [`draw_texture`](#draw_texture) | `nil` |

---

### clear

```ruby
bitmap.clear
```

Clears the entire bitmap.

### debug

```ruby
bitmap.debug
```

Draws a debug overlay showing the bitmap bounds.

### resize

```ruby
bitmap.resize(width, height)
```

Resizes the bitmap to the given dimensions.

- `width` — `Integer` — new width in pixels
- `height` — `Integer` — new height in pixels

### dispose

```ruby
bitmap.dispose
```

Releases the bitmap resources.

### disposed?

```ruby
bitmap.disposed?
```

Returns `true` if the bitmap has been disposed.

### draw_text

```ruby
bitmap.draw_text(x, y, w, h, text, font[, color[, align]])
```

Renders text on the bitmap within the specified area.

- `x` — `Float` — text area position
- `y` — `Float` — text area position
- `width` — `Float` — text area width
- `height` — `Float` — text area height
- `text` — `String`
- `font` — `Font`
- `color` — `Color` (optional) — text color
- `align` — `Integer` (optional) — text alignment

### draw_texture

```ruby
bitmap.draw_texture(x, y, texture)
```

Renders a texture onto the bitmap at the given position.

- `x` — `Float` — x position
- `y` — `Float` — y position
- `texture` — `Texture` — the texture to draw
