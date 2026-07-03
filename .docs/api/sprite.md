# Sprite

A renderable 2D object with a bitmap.

## Constructor

```ruby
Sprite.new
```

## Properties

| Property | Type | Access |
|---|---|---|
| `bitmap` / `bitmap=` | `Bitmap` or `nil` | read-write |
| `x` / `x=` | `Float` | read-write |
| `y` / `y=` | `Float` | read-write |
| `z` / `z=` | `Float` | read-write |
| `visible` / `visible=` | `Boolean` | read-write |

## Methods

| Method | Returns |
|---|---|
| [`dispose`](#dispose) | `nil` |
| [`disposed?`](#disposed) | `Boolean` |

---

### dispose

```ruby
sprite.dispose
```

Releases the sprite resources.

### disposed?

```ruby
sprite.disposed?
```

Returns `true` if the sprite has been disposed.
