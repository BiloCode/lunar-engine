#include <Engine/core/bitmap.h>

Bitmap::Bitmap(unsigned int width, unsigned int height) : width(std::max(width, 1u)), height(std::max(height, 1u))
{
   sf_canvas = sf::RenderTexture({ this->width, this->height });
}

unsigned int Bitmap::get_width() const
{
   return width;
}

unsigned int Bitmap::get_height() const
{
   return height;
}

const sf::Texture& Bitmap::get_texture()
{
   if (sf_dirty) {
      sf_canvas.display();
      sf_dirty = false;
   }
   return sf_canvas.getTexture();
}

void Bitmap::clear()
{
   sf_canvas.clear(sf::Color::Transparent);
   sf_dirty = true;
}

void Bitmap::resize(unsigned int width, unsigned int height)
{
   this->width = std::max(width, 1u);
   this->height = std::max(height, 1u);
   if (!this->sf_canvas.resize({ this->width, this->height }))
   {
      throw std::runtime_error("Failed to resize Bitmap");
   }
   sf_dirty = true;
}

void Bitmap::draw_text(const float x, const float y, const std::string& text, const Font& font)
{
   draw_text(x, y, text, font, Color(sf::Color::White));
}

void Bitmap::draw_text(const float x, const float y, const std::string& text, const Font& font, const Color& color)
{
   sf::Text sf_text(font);
   sf_text.setString(text);
   sf_text.setPosition({ x, y });
   sf_text.setFillColor(color.get_value());
   sf_text.setCharacterSize(font.get_size());
   sf_canvas.draw(sf_text);
   sf_dirty = true;
}

void Bitmap::draw_texture(const float x, const float y, const sf::Texture& texture)
{
   sf_dirty = true;
}
