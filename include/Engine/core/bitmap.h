#pragma once

#include <Engine/interfaces/disposable.h>
#include "rect.h"
#include "color.h"
#include "image.h"

class Font;

class Bitmap : public Disposable
{
public:
   Bitmap();
   Bitmap(int width, int height);
   ~Bitmap() override;
   Font* font;
   int get_width() const;
   int get_height() const;
   SDL_Texture* get_texture();
   void debug();
   void clear();
   void resize(int width, int height);
   void draw_rect(int x, int y, int width, int height, const Color& color = Color::Red, int thickness = 1);
   void draw_text(int x, int y, int width, int height, const std::string& text, const Color& color = Color::Black, int align = 0);
   void draw_texture(const Image& image, int x, int y);
   void draw_texture_region(const Image& image, int x, int y, const Rect<int>& bounds);

protected:
   void on_dispose() override;

private:
   SDL_Surface* surface;
   SDL_Texture* texture;
   int width;
   int height;
   bool texture_dirty;
   bool texture_invalid;
};
