#include <Engine/core/color.h>

Color::Color(const Color& color) : r(color.r), g(color.g), b(color.b), a(color.a)
{
}

Color::Color(unsigned int r, unsigned int g, unsigned int b) : r(r), g(g), b(b)
{
}

Color::Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a) : r(r), g(g), b(b), a(a)
{
}

const Color Color::Red = Color(255, 0, 0);
const Color Color::White = Color(255, 255, 255);
const Color Color::Black = Color(0, 0, 0);