# Lunar Engine

**Lunar Engine** is a C++ game engine built on top of **SDL3**. It exposes a Ruby scripting layer via **mruby**, allowing game logic to be written entirely in Ruby while the heavy lifting (rendering, audio, input) stays in native C++.

<div align="center">

```
┌─────────────────────┐
│   Ruby Scripting    │
│  (game logic, UI)   │
└──────────┬──────────┘
      | mruby
┌──────────▼──────────┐
│   C++ Bindings      │
│  (mruby wrappers)   │
└──────────┬──────────┘
│
┌──────────▼──────────┐
│   C++ Core (SDL3)   │
│  (rendering, audio, │
│   input, resources) │
└─────────────────────┘
```

</div>

The engine initializes the C++ core first, then boots the mruby VM. Ruby scripts can instantiate engine objects (sprites, bitmaps, fonts, vectors, colors) and call methods on them. Memory management is handled per-object — most bindings free their C++ resources automatically when the Ruby object is garbage collected.

## Examples

```ruby
# Load a font and create a bitmap with text
font = Fonts.load("arial.ttf")
bitmap = Bitmap.new(320, 80)
bitmap.font = font
bitmap.draw_text(10, 10, 300, 60, "Hello, Lunar Engine!")

# Create a sprite and assign the bitmap
sprite = Sprite.new
sprite.bitmap = bitmap
sprite.x = 100
sprite.y = 200

# Position vectors
pos = Vector2f.new(150, 75)
size = Vector2i.new(32, 32)

# Rectangles for layout and texture regions
rect = Rect2f.new(50, 50, 200, 100)
area = Rect2i.new(x: 0, y: 0, width: 64, height: 64)

# Draw a texture region using a rect
bitmap.draw_texture_region(image, 0, 0, area)
```

