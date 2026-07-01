#include <Engine/core/sprite.h>
#include <Engine/singletons/canvas.h>

Sprite::Sprite()
{
   Canvas::add(this);
}

Sprite::~Sprite()
{
   dispose();
}

void Sprite::draw(sf::RenderTarget& target)
{
   if (bitmap && bitmap->is_valid()) {
      sf::Sprite sprite(bitmap->get_texture());
      sprite.setPosition({ x, y });
      target.draw(sprite);
   }
}

void Sprite::on_dispose()
{
   bitmap = nullptr;
}
