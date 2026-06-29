#include <Engine/core/font.h>

Font::Font(const sf::Font& font) : sf_font(font), sf_font_size(16u)
{
}

Font::Font(const sf::Font& font, unsigned int font_size) : sf_font(font), sf_font_size(font_size)
{
}

Font::operator const sf::Font&() const
{
   return sf_font;
}

const unsigned int Font::get_size() const
{
   return sf_font_size;
}

const Vector<float> Font::get_text_size(const std::string text) const
{
   float x, y;

   for (char c : text) {
      auto c_size = get_character_size(c);
      x += c_size.get_x();
      y = std::max(c_size.get_y(), y);
   }

   return Vector<float>(x, y);
}

const Vector<float> Font::get_character_size(char c) const
{
   auto glyph = sf_font.getGlyph(c, sf_font_size, false);
   return Vector<float>(glyph.advance, glyph.bounds.size.y);
}
