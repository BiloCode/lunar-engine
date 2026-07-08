#include <Engine/bindings/r_kernel.h>
#include <Engine/singletons/scene.h>
#include <Engine/singletons/interpreter.h>

namespace
{
   mrb_value cpp_set_scene(mrb_state* mrb, mrb_value self)
   {
      mrb_value room;
      mrb_value room_prev = Scene::get_current();
      mrb_get_args(mrb, "o", &room);
      if (!mrb_nil_p(room_prev)) {
         mrb_funcall(mrb, room_prev, "exit_tree", 0);
         mrb_gc_unregister(mrb, room_prev);
         if (mrb->exc) {
            mrb_raise(mrb, E_RUNTIME_ERROR, "exit_tree error");
         }
      }
      Scene::set_current(room);
      mrb_gc_register(mrb, Scene::get_current());
      mrb_funcall(mrb, Scene::get_current(), "enter_tree", 0);
      if (mrb->exc) {
         mrb_raise(mrb, E_RUNTIME_ERROR, "enter_tree error");
      }
      return mrb_nil_value();
   }
}

void ruby::bind_kernel()
{
   auto* ref = Interpreter::get_module("Kernel");
   Interpreter::bind_instance_method(ref, "cpp_set_scene", cpp_set_scene, MRB_ARGS_REQ(1));
}
