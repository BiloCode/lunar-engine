#pragma once

#include <SFML/Graphics.hpp>

class Texture
{
public:
   Texture(const sf::Texture& texture);
   operator const sf::Texture&() const;

private:
   const sf::Texture* sf_texture;
};
