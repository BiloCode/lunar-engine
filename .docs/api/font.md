# Font

Represents a typeface. **Cannot be instantiated directly** from Ruby; use `Fonts.load` instead.

## Constructor

```ruby
Font.new
```

Raises `RuntimeError`. Fonts are created through the `Fonts` module.

## Methods

| Method | Returns |
|---|---|
| [`t_size`](#t_size) | `Vector2i` |
| [`c_size`](#c_size) | `Vector2i` |

---

### t_size

```ruby
font.t_size(text)
```

Returns the pixel dimensions of the given string as a `Vector2i`.

- `text` — `String` — the text to measure

### c_size

```ruby
font.c_size(char)
```

Returns the size of a single character. Raises `ArgumentError` if the string is not exactly 1 character.

- `char` — `String` — a single character
