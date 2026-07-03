#include <Engine/bindings/r_fonts.h>
#include <Engine/bindings/r_types.h>
#include <Engine/singletons/interpreter.h>

namespace
{
   mrb_value fonts_get(mrb_state* mrb, mrb_value self)
   {
      const char* f_name;
      mrb_int f_size = 0;
      mrb_int args_c = mrb_get_args(mrb, "z|i", &f_name, &f_size);
      auto f_class = mrb_class_get(mrb, "Font");
      auto f_module = mrb_module_get(mrb, "Fonts");
      auto f_property = (FontsCache*) mrb_cptr(
         mrb_iv_get(mrb, mrb_obj_value(f_module), mrb_intern_lit(mrb, "@cache"))
      );

      Font* f_cpp;

      if (args_c == 1) {
         f_cpp = new Font(f_property->get(f_name));
      }
      else {
         f_cpp = new Font(f_property->get(f_name), f_size);
      }

      return mrb_obj_value(
         mrb_data_object_alloc(mrb, f_class, f_cpp, &r_font_type)
      );
   }
}

void ruby::bind_fonts(FontsCache& fonts)
{
   auto ref = Interpreter::bind_module("Fonts");
   Interpreter::bind_property(ref, "@cache", &fonts);
   Interpreter::bind_singleton_method(ref, "get", fonts_get, MRB_ARGS_ARG(1, 1));
}
