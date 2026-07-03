#include <Engine/singletons/scene.h>
#include <Engine/singletons/interpreter.h>

mrb_value Scene::current = mrb_nil_value();

void Scene::update(sf::RenderTarget& target)
{
   if (!mrb_nil_p(current)) {
      Interpreter::call(current, "process");
   }
}
