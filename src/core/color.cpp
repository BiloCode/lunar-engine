#include <Engine/core/color.h>

Color::Color(const Color& color) : r(color.r), g(color.g), b(color.b), a(color.a)
{
}

Color::Color(unsigned int r, unsigned int g, unsigned int b) : r(r), g(g), b(b), a(255u)
{
}

Color::Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a) : r(r), g(g), b(b), a(a)
{
}

SDL_Color Color::c_sdl() const
{
    SDL_Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    return color;
}

const Color Color::Transparent(0, 0, 0, 0);
const Color Color::Black(0, 0, 0);
const Color Color::White(255, 255, 255);
const Color Color::Red(255, 0, 0);
const Color Color::Green(0, 255, 0);
const Color Color::Blue(0, 0, 255);
const Color Color::Yellow(255, 255, 0);
const Color Color::Magenta(255, 0, 255);
const Color Color::Cyan(0, 255, 255);