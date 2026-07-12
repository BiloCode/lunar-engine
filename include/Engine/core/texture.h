#pragma once

#include <SDL3/SDL.h>

class Texture
{
public:
   Texture(const SDL_Texture* texture);
   operator const SDL_Texture*() const;

private:
   const SDL_Texture* texture;
};
