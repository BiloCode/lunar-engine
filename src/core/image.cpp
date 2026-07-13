#include <Engine/core/image.h>

#include <Engine/singletons/runtime.h>

Image::Image(const SDL_Surface* surface) : surface(surface)
{
}

SDL_Surface* Image::get_source_clone() const
{
   return SDL_DuplicateSurface(const_cast<SDL_Surface*>(surface));
}

const SDL_Surface* Image::get_source_ref() const
{
   return surface;
}

int Image::get_width() const
{
   return surface->w;
}

int Image::get_height() const
{
   return surface->h;
}