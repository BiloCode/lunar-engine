#pragma once

#include <SFML/Graphics.hpp>
#include "font.h"
#include "color.h"

class Bitmap
{
public:
   Bitmap() = default;
   Bitmap(unsigned int width, unsigned int height);
   unsigned int get_width() const;
   unsigned int get_height() const;
   const sf::Texture& get_texture();
   void clear();
   void resize(unsigned int width, unsigned int height);
   void draw_text(const float x, const float y, const std::string& text, const Font& font);
   void draw_text(const float x, const float y, const std::string& text, const Font& font, const Color& color);
   void draw_texture(const float x, const float y, const sf::Texture& texture);

private:
   bool sf_dirty;
   unsigned int width;
   unsigned int height;
   sf::RenderTexture sf_canvas;
};
