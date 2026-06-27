#pragma once

#include <SFML/Graphics.hpp>

class Font
{
public:
   Font(const sf::Font& font);
   Font(const sf::Font& font, unsigned int font_size);
   operator const sf::Font&() const;
   const unsigned int get_size() const;

private:
   sf::Font font;
   unsigned int font_size;
};
