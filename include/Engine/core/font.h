#pragma once

#include <SFML/Graphics.hpp>

class Font
{
public:
   unsigned int size = 16u;
   Font(const sf::Font& font);
   operator const sf::Font&() const;

private:
   sf::Font font;
};
