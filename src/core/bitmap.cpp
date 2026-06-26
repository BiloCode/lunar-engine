#include <Engine/core/bitmap.h>

Bitmap::Bitmap() : font(nullptr)
{
}

Bitmap::Bitmap(unsigned int width, unsigned int height) : width(std::max(width, 1u)), height(std::max(height, 1u)), font(nullptr)
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

const sf::Texture& Bitmap::get_texture() const
{
   return sf_canvas.getTexture();
}

void Bitmap::clear()
{
   sf_canvas.clear();
}

void Bitmap::display()
{
   sf_canvas.display();
}

void Bitmap::resize(unsigned int width, unsigned int height)
{
   this->width = std::max(width, 1u);
   this->height = std::max(height, 1u);
   if (!this->sf_canvas.resize({ this->width, this->height }))
   {
      throw std::runtime_error("Failed to resize Bitmap");
   }
}

void Bitmap::draw_text(const float x, const float y, const std::string& text)
{
   if (!font) {
      throw std::runtime_error("[Bitmap::draw_text]: font is null");
   }
   sf::Text sf_text(*font);
   sf_text.setString(text);
   sf_text.setPosition({ x, y });
   sf_text.setCharacterSize(font->size);
   sf_canvas.draw(sf_text);
}

void Bitmap::draw_texture(const float x, const float y, const sf::Texture& texture)
{
}
