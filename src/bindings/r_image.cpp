#include <Engine/bindings/r_image.h>

#include <mruby.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <Engine/core/image.h>
#include <Engine/utils/string.h>
#include <Engine/bindings/r_types.h>
#include <Engine/singletons/interpreter.h>

namespace String = Engine::String;

namespace
{
   mrb_value image_new(mrb_state* mrb, mrb_value self)
   {
      mrb_raise(mrb, E_RUNTIME_ERROR, "Image cannot be instantiated");
      return mrb_nil_value();
   }

   mrb_value image_width(mrb_state* mrb, mrb_value self)
   {
      auto* image = static_cast<Image*>(mrb_data_get_ptr(mrb, self, &r_image_type));
      return mrb_int_value(mrb, image->get_width());
   }

   mrb_value image_height(mrb_state* mrb, mrb_value self)
   {
      auto* image = static_cast<Image*>(mrb_data_get_ptr(mrb, self, &r_image_type));
      return mrb_int_value(mrb, image->get_height());
   }

   mrb_value image_to_string(mrb_state* mrb, mrb_value self)
   {
      auto image = static_cast<Image*>(mrb_data_get_ptr(mrb, self, &r_image_type));
      auto output = String::format_object("#<Image>", {
         { "width", std::to_string(image->get_width()) },
         { "height", std::to_string(image->get_height()) }
      });
      return mrb_str_new_cstr(mrb, output.c_str());
   }
}

void ruby::bind_image()
{
   auto* ref = Interpreter::bind_class("Image");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
   Interpreter::bind_singleton_method(ref, "new", image_new, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "width", image_width, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "height", image_height, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "to_s", image_to_string, MRB_ARGS_NONE());
}
