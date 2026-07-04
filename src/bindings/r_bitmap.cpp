#include <Engine/bindings/r_bitmap.h>
#include <Engine/bindings/r_font.h>
#include <Engine/bindings/r_types.h>
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

   mrb_value bitmap_clear(mrb_state* mrb, mrb_value self)
   {
      auto* bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, self, &r_bitmap_type));
      bitmap->clear();
      return mrb_nil_value();
   }

   mrb_value bitmap_debug(mrb_state* mrb, mrb_value self)
   {
      auto* bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, self, &r_bitmap_type));
      bitmap->debug();
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
      mrb_value v_font, v_color;

      mrb_int args_c = mrb_get_args(mrb, "ffffzo|oi", &x, &y, &width, &height, &text, &v_font, &v_color, &align);

      auto* font = static_cast<Font*>(mrb_data_get_ptr(mrb, v_font, &r_font_type));
      auto* bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, self, &r_bitmap_type));

      if (args_c == 6) {
         bitmap->draw_text(x, y, width, height, text, *font);
      }
      else if (args_c == 7) {
         auto color = static_cast<Color*>(mrb_data_get_ptr(mrb, v_color, &r_color_type));
         bitmap->draw_text(x, y, width, height, text, *font, *color);
      }
      else if (args_c == 8) {
         auto color = static_cast<Color*>(mrb_data_get_ptr(mrb, v_color, &r_color_type));
         bitmap->draw_text(x, y, width, height, text, *font, *color, align);
      }
      else {
         mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid arguments");
      }

      return mrb_nil_value();
   }

   mrb_value bitmap_draw_texture(mrb_state* mrb, mrb_value self)
   {
      mrb_float x, y;
      mrb_value v_texture;

      mrb_int args_c = mrb_get_args(mrb, "ffo", &x, &y, &v_texture);

      auto* bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, self, &r_bitmap_type));

      if (args_c == 3) {
         auto texture = static_cast<Texture*>(mrb_data_get_ptr(mrb, v_texture, &r_texture_type));
         bitmap->draw_texture(x, y, *texture);
      }
      else {
         mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid arguments");
      }

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
   Interpreter::bind_instance_method(ref, "clear", bitmap_clear, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "debug", bitmap_debug, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "resize", bitmap_resize, MRB_ARGS_REQ(2));
   Interpreter::bind_instance_method(ref, "dispose", bitmap_dispose, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "disposed?", bitmap_disposed, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "draw_text", bitmap_draw_text, MRB_ARGS_ARG(6, 2));
   Interpreter::bind_instance_method(ref, "draw_texture", bitmap_draw_texture, MRB_ARGS_REQ(3));
}
