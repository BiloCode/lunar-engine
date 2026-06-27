#include <Engine/singletons/canvas.h>

std::vector<Sprite*> Canvas::sprites = {};

void Canvas::add(Sprite* sprite)
{
   sprites.push_back(sprite);
}

void Canvas::remove(Sprite* sprite)
{
   auto it = std::find_if(sprites.begin(), sprites.end(), [sprite](Sprite* ptr) {
      return ptr == sprite;
   });

   if (it != sprites.end())
   {
      sprites.erase(it);
   }
}

void Canvas::update(sf::RenderTarget& target)
{
   for (auto sprite : sprites)
   {
      sprite->draw(target);
   }
}
