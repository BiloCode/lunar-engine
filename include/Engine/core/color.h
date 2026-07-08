#pragma once

#include <string>

class Color
{
public:
   unsigned int r, g, b, a;
   Color(const Color& color);
   Color(unsigned int r, unsigned int g, unsigned int b);
   Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
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
