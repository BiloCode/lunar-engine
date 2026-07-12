#pragma once

#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include "vector.h"

class Font
{
public:
    Font(const TTF_Font* font);
    operator const TTF_Font*() const;
    const Vector<int> get_text_size(const std::string& text) const;
    const Vector<int> get_character_size(char c) const;

private:
    TTF_Font* font;
};