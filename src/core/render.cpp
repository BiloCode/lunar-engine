#include <Engine/core/render.h>

std::vector<Sprite*> Render::sprites = {};

void Render::add(Sprite* sprite)
{
   sprites.push_back(sprite);
}

void Render::remove(Sprite* sprite)
{
   auto it = std::find_if(sprites.begin(), sprites.end(), [sprite](Sprite* ptr) {
      return ptr == sprite;
   });

   if (it != sprites.end())
   {
      sprites.erase(it);
   }
}

void Render::update(sf::RenderTarget& target)
{
   for (auto sprite : sprites)
   {
      sprite->draw(target);
   }
}
