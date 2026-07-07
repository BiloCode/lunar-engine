#include <Engine/core/bitmap.h>
#include <iostream>

Bitmap::Bitmap(unsigned int width, unsigned int height) : width(std::max(width, 1u)), height(std::max(height, 1u))
{
}

Bitmap::~Bitmap()
{
   dispose();
}

unsigned int Bitmap::get_width() const
{
   return width;
}

unsigned int Bitmap::get_height() const
{
   return height;
}

/*const sf::Texture& Bitmap::get_texture()
{
   if (sf_dirty) {
      sf_canvas.display();
      sf_dirty = false;
   }
   return sf_canvas.getTexture();
}*/

void Bitmap::clear()
{
   if (is_invalid()) return;
   //sf_canvas.clear(sf::Color::Transparent);
   sf_dirty = true;
}

void Bitmap::debug()
{
   if (is_invalid()) return;
   /*auto sf_bounds = sf::RectangleShape();
   sf_bounds.setSize({ static_cast<float>(width), static_cast<float>(height) });
   sf_bounds.setPosition({ 0.f, 0.f });
   sf_bounds.setFillColor(sf::Color::Transparent);
   sf_bounds.setOutlineThickness(-2.f);
   sf_bounds.setOutlineColor(sf::Color::Red);
   sf_canvas.draw(sf_bounds);*/
   sf_dirty = true;
}

void Bitmap::resize(unsigned int width, unsigned int height)
{
   if (is_invalid()) return;
   this->width = std::max(width, 1u);
   this->height = std::max(height, 1u);
   /*if (!this->sf_canvas.resize({ this->width, this->height }))
   {
      throw std::runtime_error("Failed to resize Bitmap");
   }*/
   sf_dirty = true;
}

// void Bitmap::draw_text(float x, float y, float width, float height, const std::string& text, const Font& font)
// {
//    if (is_invalid()) return;
//    draw_text(x, y, width, height, text, font, Color::Black, 0);
// }

// void Bitmap::draw_text(float x, float y, float width, float height, const std::string& text, const Font& font, const Color& color)
// {
//    if (is_invalid()) return;
//    draw_text(x, y, width, height, text, font, color, 0);
// }

// void Bitmap::draw_text(float x, float y, float width, float height, const std::string& text, const Font& font, const Color& color, int align)
// {
//    if (is_invalid()) return;

//    auto sf_text = sf::Text(font, sf::String::fromUtf8(text.begin(), text.end()), font.get_font_size());
//    auto sf_text_bounds = sf_text.getLocalBounds();

//    sf_text.setOrigin({ sf_text_bounds.position.x, sf_text_bounds.position.y });

//    float draw_x = x;
//    float draw_y = y + (height - sf_text_bounds.size.y) * 0.5f;

//    switch (align)
//    {
//       case 1:
//          draw_x += (width - sf_text_bounds.size.x) * 0.5f;
//          break;

//       case 2:
//          draw_x += width - sf_text_bounds.size.x;
//          break;
//    }

//    sf_text.setFillColor(color.get_value());
//    sf_text.setPosition({
//       std::round(draw_x),
//       std::round(draw_y)
//    });

//    sf_canvas.draw(sf_text);
//    sf_dirty = true;
// }

void Bitmap::draw_texture(float x, float y, const Texture& texture)
{
   if (is_invalid()) return;
   /*auto sf_sprite = sf::Sprite(texture);
   sf_sprite.setPosition({ x, y });
   sf_canvas.draw(sf_sprite);*/
   sf_dirty = true;
}

void Bitmap::on_dispose()
{
   //sf_canvas = sf::RenderTexture();
}
