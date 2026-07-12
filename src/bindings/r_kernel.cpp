#include <Engine/bindings/r_kernel.h>

#include <mruby.h>
#include <mruby/data.h>
#include <Engine/core/color.h>
#include <Engine/bindings/r_types.h>
#include <Engine/singletons/scene.h>
#include <Engine/singletons/environment.h>
#include <Engine/singletons/interpreter.h>

namespace
{
   mrb_value cpp_set_scene(mrb_state* mrb, mrb_value self)
   {
      mrb_value scene;
      mrb_value scene_prev = Scene::get_current();
      mrb_get_args(mrb, "o", &scene);
      if (!mrb_nil_p(scene_prev)) {
         mrb_funcall(mrb, scene_prev, "exit_tree", 0);
         mrb_gc_unregister(mrb, scene_prev);
         if (mrb->exc) {
            mrb_raise(mrb, E_RUNTIME_ERROR, "exit_tree error");
         }
      }
      Scene::set_current(scene);
      mrb_gc_register(mrb, Scene::get_current());
      mrb_funcall(mrb, Scene::get_current(), "enter_tree", 0);
      if (mrb->exc) {
         mrb_raise(mrb, E_RUNTIME_ERROR, "enter_tree error");
      }
      return mrb_nil_value();
   }

   mrb_value cpp_set_background(mrb_state* mrb, mrb_value self)
   {
      mrb_value color_v;
      mrb_get_args(mrb, "o", &color_v);
      auto* color = static_cast<Color*>(mrb_data_get_ptr(mrb, color_v, &r_color_type));
      Environment::set_background(*color);
      return mrb_nil_value();
   }
}

void ruby::bind_kernel()
{
   auto* ref = Interpreter::get_module("Kernel");
   Interpreter::bind_instance_method(ref, "cpp_set_scene", cpp_set_scene, MRB_ARGS_REQ(1));
   Interpreter::bind_instance_method(ref, "cpp_set_background", cpp_set_background, MRB_ARGS_REQ(1));
}
