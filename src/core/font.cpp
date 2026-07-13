#include <Engine/core/font.h>

#include <Engine/utils/debug.h>

namespace Debug = Engine::Debug;

Font::Font(TTF_Font* font) : font(font)
{
}

TTF_Font* Font::c_sdl() const
{
   return font;
}

const Vector<int> Font::get_text_size(const std::string& text) const
{
   int w = 0;
   int h = 0;

   if (TTF_GetStringSize(font, text.c_str(), text.size(), &w, &h))
   {
      Debug::print_exception(SDL_GetError());
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