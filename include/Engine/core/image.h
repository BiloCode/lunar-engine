#pragma once

#include <SDL3/SDL.h>

class Image
{
public:
   Image(const SDL_Surface* surface);
   SDL_Surface* get_source_clone() const;
   const SDL_Surface* get_source_ref() const;
   int get_width() const;
   int get_height() const;

private:
   const SDL_Surface* surface;
};
