#include <Engine/core/sprite.h>

void Sprite::draw(sf::RenderTarget& render)
{
   if (bitmap) {
      bitmap->display();
      sf::Sprite sf_sprite(bitmap->get_texture());
      sf_sprite.setPosition({ x, y });
      render.draw(sf_sprite);
   }
}
