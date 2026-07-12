#include <Engine/bindings/r_fonts.h>

#include <mruby.h>
#include <mruby/variable.h>
#include <Engine/core/font.h>
#include <Engine/bindings/r_types.h>
#include <Engine/resources/font_manager.h>
#include <Engine/singletons/interpreter.h>

namespace
{
   mrb_value fonts_get(mrb_state* mrb, mrb_value self)
   {
      const char* f_name;
      mrb_int args_c = mrb_get_args(mrb, "z", &f_name);
      
      auto f_class = mrb_class_get(mrb, "Font");
      auto f_module = mrb_module_get(mrb, "Fonts");
      auto f_property = (FontManager*) mrb_cptr(
         mrb_iv_get(mrb, mrb_obj_value(f_module), mrb_intern_lit(mrb, "@cache"))
      );

      Font* f_cpp;

      if (args_c == 1) {
         f_cpp = new Font(f_property->get(f_name));
      }
      else {
         mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid arguments");
      }

      return mrb_obj_value(
         mrb_data_object_alloc(mrb, f_class, f_cpp, &r_font_type)
      );
   }
}

void ruby::bind_fonts(FontManager& manager)
{
   auto ref = Interpreter::bind_module("Fonts");
   Interpreter::bind_property(ref, "@cache", &manager);
   Interpreter::bind_singleton_method(ref, "get", fonts_get, MRB_ARGS_REQ(1));
}
