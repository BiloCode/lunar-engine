#pragma once

#include <string>

class Color
{
public:
   Color(unsigned int r, unsigned int g, unsigned int b);
   Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a);

private:
   unsigned int r;
   unsigned int g;
   unsigned int b;
   unsigned int a;
};
