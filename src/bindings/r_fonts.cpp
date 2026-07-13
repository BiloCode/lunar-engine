#include <Engine/bindings/r_fonts.h>

#include <mruby.h>
#include <mruby/variable.h>
#include <Engine/core/font.h>
#include <Engine/bindings/r_types.h>
#include <Engine/resources/font_manager.h>
#include <Engine/singletons/interpreter.h>

namespace
{
   mrb_value fonts_load(mrb_state* mrb, mrb_value self)
   {
      const char* f_name;
      mrb_int args_c = mrb_get_args(mrb, "z", &f_name);
      
      auto r_class = mrb_class_get(mrb, "Font");
      auto r_module = mrb_module_get(mrb, "Fonts");
      
      Font* font;
      FontManager* font_manager = (FontManager*) mrb_cptr(
         mrb_iv_get(mrb, mrb_obj_value(r_module), mrb_intern_lit(mrb, "@cache"))
      );


      if (args_c == 1) {
         font = new Font(font_manager->load(f_name));
      }
      else {
         mrb_raise(mrb, E_ARGUMENT_ERROR, "Invalid arguments");
      }

      return mrb_obj_value(
         mrb_data_object_alloc(mrb, r_class, font, &r_font_type)
      );
   }
}

void ruby::bind_fonts(FontManager& manager)
{
   auto ref = Interpreter::bind_module("Fonts");
   Interpreter::bind_property(ref, "@cache", &manager);
   Interpreter::bind_singleton_method(ref, "load", fonts_load, MRB_ARGS_REQ(1));
}
