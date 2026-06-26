#include <Engine/core/font.h>

Font::Font(const sf::Font& font) : font(font)
{
}

Font::operator const sf::Font&() const
{
   return font;
}
