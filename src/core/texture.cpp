#include <Engine/core/texture.h>

Texture::Texture(const SDL_Texture* texture) : texture(texture)
{
}

Texture::operator const SDL_Texture*() const
{
   return texture;
}
