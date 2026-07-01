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

void Bitmap::debug()
{
   auto sf_bounds = sf::RectangleShape();
   sf_bounds.setSize({ static_cast<float>(width), static_cast<float>(height) });
   sf_bounds.setPosition({ 0.f, 0.f });
   sf_bounds.setFillColor(sf::Color::Transparent);
   sf_bounds.setOutlineThickness(-2.f);
   sf_bounds.setOutlineColor(sf::Color::Red);
   sf_canvas.draw(sf_bounds);
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

void Bitmap::draw_text(float x, float y, float width, float height, const std::string& text, const Font& font)
{
   draw_text(x, y, width, height, text, font, 0, Color(sf::Color::White));
}

void Bitmap::draw_text(float x, float y, float width, float height, const std::string& text, const Font& font, int align)
{
   draw_text(x, y, width, height, text, font, align, Color(sf::Color::White));
}

void Bitmap::draw_text(float x, float y, float width, float height, const std::string& text, const Font& font, int align, const Color& color)
{
   auto sf_text = sf::Text(font, sf::String::fromUtf8(text.begin(), text.end()), font.get_size());
   auto sf_text_bounds = sf_text.getLocalBounds();

   float draw_x = x;
   float draw_y = y;

   switch(align)
   {
      case 1:
         draw_x += (width - sf_text_bounds.size.x) / 2.f;
         draw_y += (height - sf_text_bounds.size.y) / 2.f;
         break;

      case 2:
         draw_x += width - sf_text_bounds.size.x;
         draw_y += (height - sf_text_bounds.size.y) / 2.f;
         break;

      default:
         draw_y += (height - sf_text_bounds.size.y) / 2.f;
         break;
   }

   sf_text.setFillColor(color.get_value());
   sf_text.setPosition({
      std::floor(draw_x - sf_text_bounds.position.x),
      std::floor(draw_y - sf_text_bounds.position.y)
   });

   sf_canvas.draw(sf_text);
   sf_dirty = true;
}

void Bitmap::draw_texture(const float x, const float y, const sf::Texture& texture)
{
   sf_dirty = true;
}
