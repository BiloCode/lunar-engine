#include <Engine/core/texture.h>

Texture::Texture(const sf::Texture& texture) : sf_texture(&texture)
{
}

Texture::operator const sf::Texture &() const
{
   return *sf_texture;
}
