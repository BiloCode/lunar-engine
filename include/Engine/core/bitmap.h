#pragma once

#include <SFML/Graphics.hpp>
#include <Engine/interfaces/disposable.h>
#include "font.h"
#include "color.h"

class Bitmap : public Disposable
{
public:
   Bitmap() = default;
   Bitmap(unsigned int width, unsigned int height);
   ~Bitmap() override;
   unsigned int get_width() const;
   unsigned int get_height() const;
   const sf::Texture& get_texture();
   void clear();
   void debug();
   void resize(unsigned int width, unsigned int height);
   void draw_text(float x, float y, float width, float height, const std::string& text, const Font& font);
   void draw_text(float x, float y, float width, float height, const std::string& text, const Font& font, const Color& color);
   void draw_text(float x, float y, float width, float height, const std::string& text, const Font& font, const Color& color, int align);
   void draw_texture(const float x, const float y, const sf::Texture& texture);

protected:
   void on_dispose() override;

private:
   bool sf_dirty;
   unsigned int width;
   unsigned int height;
   sf::RenderTexture sf_canvas;
};
