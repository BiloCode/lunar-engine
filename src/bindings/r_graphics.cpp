#include <Engine/bindings/r_graphics.h>

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/variable.h>
#include <Engine/core/image.h>
#include <Engine/resources/image_manager.h>
#include <Engine/bindings/r_types.h>
#include <Engine/singletons/interpreter.h>

namespace
{
   mrb_value graphics_load(mrb_state* mrb, mrb_value self)
   {
      const char* t_key;
      mrb_int args_c = mrb_get_args(mrb, "z", &t_key);

      auto r_class = mrb_class_get(mrb, "Image");
      auto r_module = mrb_module_get(mrb, "Graphics");
      
      Image* image;
      ImageManager* image_manager = (ImageManager*) mrb_cptr(
         mrb_iv_get(mrb, mrb_obj_value(r_module), mrb_intern_lit(mrb, "@cache"))
      );

      if (args_c == 1) {
         image = new Image(image_manager->load(t_key));
      }
      else {
         mrb_raise(mrb, E_ARGUMENT_ERROR, "Invalid arguments");
      }

      return mrb_obj_value(
         mrb_data_object_alloc(mrb, r_class, image, &r_image_type)
      );
   }
}

void ruby::bind_graphics(ImageManager& manager)
{
   auto ref = Interpreter::bind_module("Graphics");
   Interpreter::bind_property(ref, "@cache", &manager);
   Interpreter::bind_singleton_method(ref, "load", graphics_load, MRB_ARGS_REQ(1));
}
