#include <Engine/core/font.h>

Font::Font(const sf::Font& font) : font(font), font_size(16u)
{
}

Font::Font(const sf::Font& font, unsigned int font_size) : font(font), font_size(font_size)
{
}

Font::operator const sf::Font&() const
{
   return font;
}

const unsigned int Font::get_size() const
{
   return font_size;
}
