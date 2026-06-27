#include <Engine/core/sprite.h>
#include <Engine/core/render.h>
#include <iostream>

Sprite::Sprite()
{
   Render::add(this);
}

Sprite::~Sprite()
{
   Render::remove(this);
}

void Sprite::draw(sf::RenderTarget& target)
{
   if (bitmap) {
      sf::Sprite sprite(bitmap->get_texture());
      sprite.setPosition({ x, y });
      target.draw(sprite);
   }
}
