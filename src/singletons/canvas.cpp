#include <Engine/singletons/canvas.h>

std::vector<Sprite*> Canvas::elements = {};

void Canvas::add(Sprite* sprite)
{
   elements.push_back(sprite);
}

void Canvas::update(sf::RenderTarget& target)
{
   render(target);
   cleanup();
}

void Canvas::render(sf::RenderTarget& target)
{
   for (auto* element : elements)
   {
      if (element->is_valid())
      {
         element->draw(target);
      }
   }
}

void Canvas::cleanup()
{
   elements.erase(
      std::remove_if(
         elements.begin(),
         elements.end(),
         [](Sprite* sprite) {
            return sprite->is_invalid();
         }
      ),
      elements.end()
   );
}
