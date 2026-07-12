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

- `x` — `Float` — text area position
- `y` — `Float` — text area position
- `width` — `Float` — text area width
- `height` — `Float` — text area height
- `text` — `String`
- `color` — `Color` (optional) — text color
- `align` — `Integer` (optional) — text alignment

### draw_rect

```ruby
bitmap.draw_rect(x, y, width, height)
bitmap.draw_rect(x, y, width, height, color)
bitmap.draw_rect(x, y, width, height, color, align)
```

Draws a rectangle outline on the bitmap within the specified area.

- `x` — `Float` — rectangle area position
- `y` — `Float` — rectangle area position
- `width` — `Float` — rectangle area width
- `height` — `Float` — rectangle area height
- `color` — `Color` (optional) — rectangle color
- `align` — `Integer` (optional) — rectangle alignment
