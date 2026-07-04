#include <Engine/core/font.h>

Font::Font(const sf::Font& font) : sf_font(&font), sf_font_size(16u)
{
}

Font::Font(const sf::Font& font, unsigned int font_size) : sf_font(&font), sf_font_size(font_size)
{
}

Font::operator const sf::Font&() const
{
   return *sf_font;
}

unsigned int Font::get_font_size() const
{
   return sf_font_size;
}

const Vector<float> Font::get_text_size(const std::string& text) const
{
   auto sf_text = sf::Text(*sf_font, sf::String::fromUtf8(text.begin(), text.end()), sf_font_size);
   auto sf_text_bounds = sf_text.getLocalBounds();

   return {
      sf_text_bounds.size.x,
      sf_text_bounds.size.y
   };
}

const Vector<float> Font::get_character_size(char c) const
{
   auto width = sf_font->getGlyph(c, sf_font_size, false).advance;
   auto height = sf_font->getLineSpacing(sf_font_size);

   return {
      width,
      height
   };
}
