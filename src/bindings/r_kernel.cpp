#include <Engine/bindings/r_kernel.h>
#include <Engine/singletons/scene.h>
#include <Engine/singletons/interpreter.h>

namespace
{
   mrb_value cpp_set_background(mrb_state* mrb, mrb_value self)
   {
      return mrb_nil_value();
   }

   mrb_value cpp_set_scene(mrb_state* mrb, mrb_value self)
   {
      mrb_value scene;
      mrb_value scene_prev = Scene::current;
      mrb_get_args(mrb, "o", &scene);
      if (!mrb_nil_p(scene_prev)) {
         mrb_funcall(mrb, scene_prev, "exit_tree", 0);
         mrb_gc_unregister(mrb, scene_prev);
         if (mrb->exc) {
            mrb_raise(mrb, E_RUNTIME_ERROR, "exit_tree error");
         }
      }
      Scene::current = scene;
      mrb_gc_register(mrb, Scene::current);
      mrb_funcall(mrb, Scene::current, "enter_tree", 0);
      if (mrb->exc) {
         mrb_raise(mrb, E_RUNTIME_ERROR, "enter_tree error");
      }
      return mrb_nil_value();
   }
}

void ruby::bind_kernel()
{
   auto* ref = Interpreter::get_module("Kernel");
   Interpreter::bind_instance_method(ref, "cpp_set_background", cpp_set_background, MRB_ARGS_REQ(1));
   Interpreter::bind_instance_method(ref, "cpp_set_scene", cpp_set_scene, MRB_ARGS_REQ(1));
}
