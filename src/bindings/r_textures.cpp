#include <Engine/bindings/r_textures.h>

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/variable.h>
#include <Engine/core/texture.h>
#include <Engine/resources/texture_manager.h>
#include <Engine/bindings/r_types.h>
#include <Engine/singletons/interpreter.h>

namespace
{
   mrb_value textures_get(mrb_state* mrb, mrb_value self)
   {
      const char* t_key;
      mrb_get_args(mrb, "z", &t_key);

      auto t_class = mrb_class_get(mrb, "Texture");
      auto t_module = mrb_module_get(mrb, "Textures");
      auto t_property = (TextureManager*) mrb_cptr(
         mrb_iv_get(mrb, mrb_obj_value(t_module), mrb_intern_lit(mrb, "@cache"))
      );
      auto t_cpp = new Texture(t_property->get(t_key));

      return mrb_obj_value(
         mrb_data_object_alloc(mrb, t_class, t_cpp, &r_texture_type)
      );
   }
}

void ruby::bind_textures(TextureManager& manager)
{
   auto ref = Interpreter::bind_module("Textures");
   Interpreter::bind_property(ref, "@cache", &manager);
   Interpreter::bind_singleton_method(ref, "get", textures_get, MRB_ARGS_REQ(1));
}
