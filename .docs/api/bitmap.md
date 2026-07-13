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
| `font` / `font=` | `Font` or `nil` | read-write |

## Methods

| Method | Returns |
|---|---|
| [`clear`](#clear) | `nil` |
| [`debug`](#debug) | `nil` |
| [`resize`](#resize) | `nil` |
| [`dispose`](#dispose) | `nil` |
| [`disposed?`](#disposed) | `Boolean` |
| [`draw_text`](#draw_text) | `nil` |
| [`draw_rect`](#draw_rect) | `nil` |
| [`draw_texture`](#draw_texture) | `nil` |
| [`draw_texture_region`](#draw_texture_region) | `nil` |

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
bitmap.draw_text(x, y, width, height, text)
bitmap.draw_text(x, y, width, height, text, color)
bitmap.draw_text(x, y, width, height, text, color, align)
```

Renders text on the bitmap within the specified area.

- `x` — `Integer` — text area position
- `y` — `Integer` — text area position
- `width` — `Integer` — text area width
- `height` — `Integer` — text area height
- `text` — `String`
- `color` — `Color` (optional) — text color
- `align` — `Integer` (optional) — text alignment

### draw_rect

```ruby
bitmap.draw_rect(x, y, width, height)
bitmap.draw_rect(x, y, width, height, color)
bitmap.draw_rect(x, y, width, height, color, thickness)
```

Draws a rectangle outline on the bitmap within the specified area.

- `x` — `Integer` — rectangle area X
- `y` — `Integer` — rectangle area Y
- `width` — `Integer` — rectangle width
- `height` — `Integer` — rectangle height
- `color` — `Color` (optional) — rectangle color
- `thickness` — `Integer` (optional) — outline thickness

### draw_texture

```ruby
bitmap.draw_texture(image, x, y)
```

Draws an image texture onto the bitmap at the specified position.

- `image` — `Image` — the texture to draw
- `x` — `Integer` — X position
- `y` — `Integer` — Y position

### draw_texture_region

```ruby
bitmap.draw_texture_region(image, x, y, bounds)
```

Draws a region of an image texture onto the bitmap.

- `image` — `Image` — the texture to draw from
- `x` — `Integer` — target X position
- `y` — `Integer` — target Y position
- `bounds` — `Rect2i` — source rectangle region
