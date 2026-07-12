#include <Engine/singletons/renderer.h>

#include <algorithm>
#include <Engine/interfaces/renderable.h>

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
   draw();
   draw_cleanup();
}

void Renderer::refresh()
{
   std::sort(elements.begin(), elements.end(), [](const Renderable* a, const Renderable* b){
      return a->get_z() < b->get_z();
   });
}

void Renderer::draw()
{
   for (auto* element : elements)
   {
      if (element->is_valid() && element->is_visible()) {
         element->draw();
      }
   }
}

void Renderer::draw_cleanup()
{
   elements.erase(
      std::remove_if(elements.begin(), elements.end(), [](const Renderable* element) {
         return element->is_invalid();
      }),
      elements.end()
   );
}
