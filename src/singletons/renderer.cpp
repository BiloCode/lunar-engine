#include <Engine/singletons/renderer.h>
#include <algorithm>

void Renderer::attach(Renderable* element)
{
   elements.push_back(element);
}

void Renderer::detach(Renderable* element)
{
   elements.erase(
      std::remove(elements.begin(), elements.end(), element),
      elements.end()
   );
}

void Renderer::update()
{
}

// void Renderer::update(sf::RenderTarget& target)
// {
//    draw(target);
//    draw_cleanup();
// }

void Renderer::refresh()
{
   std::sort(elements.begin(), elements.end(), [](const Renderable* a, const Renderable* b){
      return a->get_z() < b->get_z();
   });
}

// void Renderer::draw(sf::RenderTarget& target)
// {
//    for (auto* element : elements) {
//       if (element->is_valid() && element->is_visible()) {
//          element->draw(target);
//       }
//    }
// }

// void Renderer::draw_cleanup()
// {
//    elements.erase(
//       std::remove_if(elements.begin(), elements.end(), [](const Renderable* element) {
//          return element->is_invalid();
//       }),
//       elements.end()
//    );
// }
