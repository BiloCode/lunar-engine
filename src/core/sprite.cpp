#include <Engine/core/sprite.h>
#include <Engine/singletons/renderer.h>

Sprite::Sprite()
{
   Renderer::attach(this);
}

Sprite::~Sprite()
{
   dispose();
}

void Sprite::draw(sf::RenderTarget& target)
{
   if (bitmap && bitmap->is_valid()) {
      auto sprite = sf::Sprite(bitmap->get_texture());
      sprite.setPosition({ x, y });
      target.draw(sprite);
   }
}

void Sprite::on_dispose()
{
   bitmap = nullptr;
}
