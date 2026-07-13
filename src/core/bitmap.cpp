#include <Engine/core/bitmap.h>

#include <Engine/core/font.h>
#include <Engine/utils/debug.h>
#include <Engine/singletons/runtime.h>

namespace Debug = Engine::Debug;

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

SDL_Texture* Bitmap::get_texture()
{
   if (texture_invalid)
   {
      texture = SDL_CreateTexture(Runtime::get_renderer(), 
         SDL_PIXELFORMAT_RGBA32,
         SDL_TEXTUREACCESS_STREAMING,
         this->width,
         this->height
      );

      if (texture == nullptr) {
         Debug::print_exception(SDL_GetError());
      }

      SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

      texture_invalid = false;
   }

   if (texture_dirty)
   {
      if (!SDL_UpdateTexture(texture, nullptr, surface->pixels, surface->pitch)) {
         Debug::print_exception(SDL_GetError());
      }

      texture_dirty = false;
   }

   return texture;
}

void Bitmap::debug()
{
   if (is_invalid()) return;
   draw_rect(0, 0, this->width, this->height, Color::Red, 2);
}

void Bitmap::clear()
{
   if (is_invalid()) return;
   SDL_ClearSurface(surface, 0, 0, 0, 0);
   texture_dirty = true;
}

void Bitmap::resize(int width, int height)
{
   if (is_invalid()) return;
   
   this->width = std::max(width, 1);
   this->height = std::max(height, 1);

   auto new_surface = SDL_CreateSurface(this->width, this->height, SDL_PIXELFORMAT_RGBA32);

   if (new_surface == nullptr)
   {
      Debug::print_exception(SDL_GetError());
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

   thickness = std::max(1, thickness);
   thickness = std::min(thickness, width);
   thickness = std::min(thickness, height);

   auto pixel = SDL_MapSurfaceRGBA(surface, color.r, color.g, color.b, color.a);

   SDL_Rect top { x, y, width, thickness };
   SDL_Rect left { x, y, thickness, height };
   SDL_Rect right { x + width - thickness, y, thickness, height };
   SDL_Rect bottom { x, y + height - thickness, width, thickness };

   if (!SDL_FillSurfaceRect(surface, &top, pixel))
   {
      Debug::print_exception(SDL_GetError());
   }
   
   if (!SDL_FillSurfaceRect(surface, &left, pixel))
   {
      Debug::print_exception(SDL_GetError());
   }
   
   if (!SDL_FillSurfaceRect(surface, &right, pixel))
   {
      Debug::print_exception(SDL_GetError());
   }

   if (!SDL_FillSurfaceRect(surface, &bottom, pixel))
   {
      Debug::print_exception(SDL_GetError());
   }

   texture_dirty = true;
}

void Bitmap::draw_text(int x, int y, int width, int height, const std::string& text, const Color& color, int align)
{
   if (is_invalid()) return;

   auto* text_surface = TTF_RenderText_Blended(font->c_sdl(), text.c_str(), text.size(), color.c_sdl());

   if (text_surface == nullptr)
   {
      Debug::print_exception(SDL_GetError());
   }

   SDL_Rect dst;
   dst.x = x;
   dst.y = y;
   dst.w = text_surface->w;
   dst.h = text_surface->h;

   if (!SDL_BlitSurface(text_surface, nullptr, surface, &dst))
   {
      Debug::print_exception(SDL_GetError());
   }

   SDL_DestroySurface(text_surface);

   texture_dirty = true;
}

void Bitmap::draw_texture(const Image& image, int x, int y)
{
   auto bounds = Rect<int>(0, 0, image.get_width(), image.get_height());
   draw_texture_region(image, x, y, bounds);
}

void Bitmap::draw_texture_region(const Image& image, int x, int y, const Rect<int>& bounds)
{
   if (is_invalid()) return;

   SDL_Surface* src = const_cast<SDL_Surface*>(image.get_source_ref());

   SDL_Rect src_rect;
   src_rect.x = bounds.x;
   src_rect.y = bounds.y;
   src_rect.w = bounds.width;
   src_rect.h = bounds.height;

   SDL_Rect dst_rect;
   dst_rect.x = x;
   dst_rect.y = y;
   dst_rect.w = 0;
   dst_rect.h = 0;

   if (!SDL_BlitSurface(src, &src_rect, surface, &dst_rect))
   {
      Debug::print_exception(SDL_GetError());
   }

   texture_dirty = true;
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
