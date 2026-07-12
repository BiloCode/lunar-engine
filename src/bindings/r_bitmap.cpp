#include <Engine/bindings/r_bitmap.h>

#include <mruby.h>
#include <mruby/class.h>
#include <Engine/core/bitmap.h>
#include <Engine/bindings/r_types.h>
#include <Engine/bindings/r_values.h>
#include <Engine/singletons/interpreter.h>

namespace
{
   mrb_value bitmap_initialize(mrb_state* mrb, mrb_value self)
   {
      mrb_int arg_count = mrb_get_argc(mrb);

      if (arg_count == 0) {
         auto* bitmap = new Bitmap();
         mrb_data_init(self, bitmap, &r_bitmap_type);
      }
      else if (arg_count == 2) {
         mrb_int width, height;
         mrb_get_args(mrb, "ii", &width, &height);
         auto* bitmap = new Bitmap(width, height);
         mrb_data_init(self, bitmap, &r_bitmap_type);
      }
      else {
         mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid arguments");
      }

      return self;
   }

   mrb_value bitmap_width(mrb_state* mrb, mrb_value self)
   {
      auto* bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, self, &r_bitmap_type));
      return mrb_fixnum_value(bitmap->get_width());
   }

   mrb_value bitmap_height(mrb_state* mrb, mrb_value self)
   {
      auto* bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, self, &r_bitmap_type));
      return mrb_fixnum_value(bitmap->get_height());
   }

   mrb_value bitmap_font(mrb_state* mrb, mrb_value self)
   {
      auto* bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, self, &r_bitmap_type));

      if (auto it = bitmap_fonts.find(bitmap); it != bitmap_fonts.end()) {
         return it->second;
      }

      return mrb_nil_value();
   }

   mrb_value bitmap_font_set(mrb_state* mrb, mrb_value self)
   {
      mrb_value obj;
      mrb_get_args(mrb, "o", &obj);

      auto* font = static_cast<Font*>(mrb_data_get_ptr(mrb, obj, &r_font_type));
      auto* bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, self, &r_bitmap_type));

      if (auto it = bitmap_fonts.find(bitmap); it != bitmap_fonts.end()) {
         mrb_gc_unregister(mrb, it->second);
         bitmap_fonts.erase(it);
      }

      bitmap->font = font;
      bitmap_fonts[bitmap] = obj;
      mrb_gc_register(mrb, obj);
      return mrb_nil_value();
   }

   mrb_value bitmap_clear(mrb_state* mrb, mrb_value self)
   {
      auto* bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, self, &r_bitmap_type));
      bitmap->clear();
      return mrb_nil_value();
   }

   mrb_value bitmap_resize(mrb_state* mrb, mrb_value self)
   {
      mrb_int width, height;
      mrb_get_args(mrb, "ii", &width, &height);
      auto* bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, self, &r_bitmap_type));
      bitmap->resize(width, height);
      return mrb_nil_value();
   }

   mrb_value bitmap_dispose(mrb_state* mrb, mrb_value self)
   {
      auto* bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, self, &r_bitmap_type));
      bitmap->dispose();
      return mrb_nil_value();
   }

   mrb_value bitmap_disposed(mrb_state* mrb, mrb_value self)
   {
      auto* bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, self, &r_bitmap_type));
      return mrb_bool_value(bitmap->is_invalid());
   }

   mrb_value bitmap_draw_text(mrb_state* mrb, mrb_value self)
   {
      const char* text;
      mrb_int align;
      mrb_float x, y, width, height;
      mrb_value v_color;

      mrb_int args_c = mrb_get_args(mrb, "ffffz|oi", &x, &y, &width, &height, &text, &v_color, &align);

      auto* bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, self, &r_bitmap_type));

      if (args_c == 5) {
         bitmap->draw_text(x, y, width, height, text);
      }
      else if (args_c == 6) {
         auto color = static_cast<Color*>(mrb_data_get_ptr(mrb, v_color, &r_color_type));
         bitmap->draw_text(x, y, width, height, text, *color);
      }
      else if (args_c == 7) {
         auto color = static_cast<Color*>(mrb_data_get_ptr(mrb, v_color, &r_color_type));
         bitmap->draw_text(x, y, width, height, text, *color, align);
      }
      else {
         mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid arguments");
      }

      return mrb_nil_value();
   }

   mrb_value bitmap_draw_limits(mrb_state* mrb, mrb_value self)
   {
      auto* bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, self, &r_bitmap_type));
      bitmap->draw_limits();
      return mrb_nil_value();
   }
}

void ruby::bind_bitmap()
{
   auto* ref = Interpreter::bind_class("Bitmap");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
   Interpreter::bind_instance_method(ref, "initialize", bitmap_initialize, MRB_ARGS_ARG(0, 2));
   Interpreter::bind_instance_method(ref, "width", bitmap_width, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "height", bitmap_height, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "font", bitmap_font, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "font=", bitmap_font_set, MRB_ARGS_REQ(1));
   Interpreter::bind_instance_method(ref, "clear", bitmap_clear, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "resize", bitmap_resize, MRB_ARGS_REQ(2));
   Interpreter::bind_instance_method(ref, "dispose", bitmap_dispose, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "disposed?", bitmap_disposed, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "draw_text", bitmap_draw_text, MRB_ARGS_ARG(5, 2));
   Interpreter::bind_instance_method(ref, "draw_limits", bitmap_draw_limits, MRB_ARGS_NONE());
}
