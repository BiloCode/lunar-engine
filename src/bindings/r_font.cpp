#include <Engine/bindings/r_font.h>

#include <mruby.h>
#include <mruby/class.h>
#include <cstring>
#include <Engine/core/font.h>
#include <Engine/bindings/r_types.h>
#include <Engine/singletons/interpreter.h>

namespace
{
   mrb_value font_new(mrb_state* mrb, mrb_value self)
   {
      mrb_raise(mrb, E_RUNTIME_ERROR, "Font cannot be instantiated");
      return mrb_nil_value();
   }

   mrb_value font_text_size(mrb_state* mrb, mrb_value self)
   {
      const char* text;
      mrb_get_args(mrb, "z", &text);
      auto font = static_cast<Font*>(mrb_data_get_ptr(mrb, self, &r_font_type));
      auto vector = new Vector(font->get_text_size(text));
      auto vector_class = mrb_class_get(mrb, "Vector2i");
      return mrb_obj_value(
         mrb_data_object_alloc(mrb, vector_class, vector, &r_vector2i_type)
      );
   }

   mrb_value font_character_size(mrb_state* mrb, mrb_value self)
   {
      const char* c;
      mrb_get_args(mrb, "z", &c);
      if (std::strlen(c) != 1) {
         mrb_raise(mrb, E_ARGUMENT_ERROR, "expected a single character");
      }
      auto font = static_cast<Font*>(mrb_data_get_ptr(mrb, self, &r_font_type));
      auto vector = new Vector(font->get_character_size(c[0]));
      auto vector_class = mrb_class_get(mrb, "Vector2i");
      return mrb_obj_value(
         mrb_data_object_alloc(mrb, vector_class, vector, &r_vector2i_type)
      );
   }
}

void ruby::bind_font()
{
   auto ref = Interpreter::bind_class("Font");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
   Interpreter::bind_singleton_method(ref, "new", font_new, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "t_size", font_text_size, MRB_ARGS_REQ(1));
   Interpreter::bind_instance_method(ref, "c_size", font_character_size, MRB_ARGS_REQ(1));
}
