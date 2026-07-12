#include <Engine/singletons/scene.h>

#include <Engine/singletons/timestamp.h>
#include <Engine/singletons/interpreter.h>

void Scene::update()
{
   if (!mrb_nil_p(current)) {
      Interpreter::call(current, "process", mrb_float_value(Interpreter::get_state(), Timestamp::get_delta_time()));
   }
}

const mrb_value& Scene::get_current()
{
   return Scene::current;
}

void Scene::set_current(const mrb_value& scene)
{
   Scene::current = scene;
}
