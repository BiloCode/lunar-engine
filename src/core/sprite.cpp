#include <Engine/core/sprite.h>
#include <Engine/singletons/canvas.h>

Sprite::Sprite()
{
   Canvas::add(this);
}

Sprite::~Sprite()
{
   Canvas::remove(this);
}

void Sprite::draw(sf::RenderTarget& target)
{
   if (bitmap) {
      sf::Sprite sprite(bitmap->get_texture());
      sprite.setPosition({ x, y });
      target.draw(sprite);
   }
}
