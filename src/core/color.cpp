#include <Engine/core/color.h>

Color::Color(const sf::Color& color) : sf_color(color)
{
}

Color::Color(unsigned int r, unsigned int g, unsigned int b)
{
   sf_color = sf::Color(r, g, b);
}

Color::Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
   sf_color = sf::Color(r, g, b, a);
}

const sf::Color Color::get_value() const
{
   return sf_color;
}
