#include <Engine/core/bitmap.h>
#include <Engine/singletons/runtime.h>
#include <iostream>

Bitmap::Bitmap() : width(1u), height(1u), texture_dirty(true), texture_invalid(true)
{
   surface = SDL_CreateSurface(width, height, SDL_PIXELFORMAT_RGBA32);
}

Bitmap::Bitmap(int width, int height) : width(std::max(width, 1)), height(std::max(height, 1)), texture_dirty(true), texture_invalid(true)
{
   surface = SDL_CreateSurface(this->width, this->height, SDL_PIXELFORMAT_RGBA32);
}

Bitmap::~Bitmap()
{
   dispose();
}

int Bitmap::get_width() const
{
   return width;
}

int Bitmap::get_height() const
{
   return height;
}

Font* Bitmap::get_font() const
{
   return font;
}

SDL_Texture* Bitmap::get_texture()
{
   if (texture_invalid) {
      texture = SDL_CreateTexture(Runtime::get_renderer(), 
         SDL_PIXELFORMAT_RGBA32,
         SDL_TEXTUREACCESS_STREAMING,
         this->width,
         this->height
      );

      if (texture == nullptr) {
         throw std::runtime_error(SDL_GetError());
      }

      texture_invalid = false;
   }

   if (texture_dirty) {
      SDL_UpdateTexture(texture, nullptr, surface->pixels, surface->pitch);
      texture_dirty = false;
   }

   return texture;
}

void Bitmap::set_font(Font* font)
{
   this->font = font;
}

void Bitmap::clear()
{
   if (is_invalid()) return;
   SDL_FillSurfaceRect(surface, nullptr, SDL_MapSurfaceRGBA(surface, 0, 0, 0, 0));
   texture_dirty = true;
}

void Bitmap::resize(int width, int height)
{
   if (is_invalid()) return;
   
   this->width = std::max(width, 1);
   this->height = std::max(height, 1);

   auto new_surface = SDL_CreateSurface(this->width, this->height, SDL_PIXELFORMAT_RGBA32);

   if (surface == nullptr)
   {
      throw std::runtime_error(SDL_GetError());
   }

   SDL_DestroySurface(surface);
   surface = new_surface;

   SDL_DestroyTexture(texture);
   texture = nullptr;

   texture_dirty = true;
   texture_invalid = true;
}

void Bitmap::draw_rect(int x, int y, int width, int height, const Color& color, int thickness)
{
   if (is_invalid()) return;

   auto pixel = SDL_MapSurfaceRGBA(surface, color.r, color.g, color.b, color.a);

   SDL_Rect top { x, y, width, thickness };
   if (!SDL_FillSurfaceRect(surface, &top, pixel)) {
      throw std::runtime_error(SDL_GetError());
   }
   
   SDL_Rect bottom { x, y + height - thickness, width, thickness };
   if (!SDL_FillSurfaceRect(surface, &bottom, pixel)) {
      throw std::runtime_error(SDL_GetError());
   }
   
   SDL_Rect left { x, y, thickness, height };
   if (!SDL_FillSurfaceRect(surface, &left, pixel)) {
      throw std::runtime_error(SDL_GetError());
   }

   SDL_Rect right { x + width - thickness, y, thickness, height };
   if (!SDL_FillSurfaceRect(surface, &right, pixel)) {
      throw std::runtime_error(SDL_GetError());
   }

   texture_dirty = true;
}

void Bitmap::draw_text(int x, int y, int width, int height, const std::string& text, const Color& color, int align)
{
   if (is_invalid()) return;
   texture_dirty = true;
}

void Bitmap::draw_limits()
{
   if (is_invalid()) return;
   draw_rect(1, 1, this->width - 2, this->height - 2, Color::Red);
}

void Bitmap::on_dispose()
{
   SDL_DestroySurface(surface);
   SDL_DestroyTexture(texture);
   surface = nullptr;
   texture = nullptr;
   texture_dirty = false;
   texture_invalid = false;
}
