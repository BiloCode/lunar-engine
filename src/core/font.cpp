#include <Engine/core/font.h>
#include <iostream>

Font::Font(const TTF_Font* font) : font(const_cast<TTF_Font*>(font))
{
}

Font::operator const TTF_Font*() const
{
   return font;
}

const Vector<int> Font::get_text_size(const std::string& text) const
{
   int w = 0;
   int h = 0;

   if (TTF_GetStringSize(font, text.c_str(), text.size(), &w, &h)) {
      throw std::runtime_error(SDL_GetError());
   }

   return {
      w,
      h
   };
}

const Vector<int> Font::get_character_size(char c) const
{
   return get_text_size(std::string(1, c));
}