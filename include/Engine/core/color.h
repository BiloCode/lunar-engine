#pragma once

#include <string>
#include <SDL3/SDL.h>

class Color
{
public:
   unsigned int r, g, b, a;
   Color(const Color& color);
   Color(unsigned int r, unsigned int g, unsigned int b);
   Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
   SDL_Color c_sdl() const;
   static const Color Transparent;
   static const Color Black;
   static const Color White;
   static const Color Red;
   static const Color Green;
   static const Color Blue;
   static const Color Yellow;
   static const Color Magenta;
   static const Color Cyan;
};
