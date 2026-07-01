#pragma once

#include <SFML/Graphics.hpp>
#include "vector.h"

class Font
{
public:
   Font(const sf::Font& font);
   Font(const sf::Font& font, unsigned int font_size);
   operator const sf::Font&() const;
   const unsigned int get_size() const;
   const Vector<float> get_text_size(const std::string& text) const;
   const Vector<float> get_character_size(char c) const;

private:
   sf::Font sf_font;
   unsigned int sf_font_size;
};
