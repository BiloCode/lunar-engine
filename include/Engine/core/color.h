#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Color
{
public:
   Color(const sf::Color& color);
   Color(unsigned int r, unsigned int g, unsigned int b);
   Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a);
   const sf::Color get_value() const;

private:
   sf::Color sf_color;
};
