#include <Engine/bindings/r_bitmap.h>
#include <Engine/bindings/r_types.h>
#include <Engine/bindings/r_font.h>

namespace
{
   mrb_value bitmap_initialize(mrb_state* mrb, mrb_value self)
   {
      Bitmap* bitmap;
      mrb_int width, height;
      int arg_count = mrb_get_argc(mrb);

      if (arg_count == 0) {
         bitmap = new Bitmap();
      }
      else if (arg_count == 2) {
         mrb_get_args(mrb, "ii", &width, &height);
         bitmap = new Bitmap(width, height);
      }
      else {
         mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid arguments");
      }

      mrb_data_init(self, bitmap, &r_bitmap_type);
      return self;
   }

   mrb_value bitmap_width(mrb_state* mrb, mrb_value self)
   {
      auto bitmap = static_cast<Bitmap*>(
         mrb_data_get_ptr(mrb, self, &r_bitmap_type)
      );
      return mrb_fixnum_value(bitmap->get_width());
   }

   mrb_value bitmap_height(mrb_state* mrb, mrb_value self)
   {
      auto bitmap = static_cast<Bitmap*>(
         mrb_data_get_ptr(mrb, self, &r_bitmap_type)
      );
      return mrb_fixnum_value(bitmap->get_height());
   }

   mrb_value bitmap_clear(mrb_state* mrb, mrb_value self)
   {
      auto bitmap = static_cast<Bitmap*>(
         mrb_data_get_ptr(mrb, self, &r_bitmap_type)
      );
      bitmap->clear();
      return mrb_nil_value();
   }

   mrb_value bitmap_resize(mrb_state* mrb, mrb_value self)
   {
      mrb_int width, height;
      mrb_get_args(mrb, "ii", &width, &height);
      auto bitmap = static_cast<Bitmap*>(
         mrb_data_get_ptr(mrb, self, &r_bitmap_type)
      );
      bitmap->resize(width, height);
      return mrb_nil_value();
   }

   mrb_value bitmap_draw_text(mrb_state* mrb, mrb_value self)
   {
      mrb_int x, y;
      mrb_value value;
      const char* text;
      mrb_get_args(mrb, "iiz", &x, &y, &text, &value);
      auto font = static_cast<Font*>(mrb_data_get_ptr(mrb, value, &r_font_type));
      auto bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, self, &r_bitmap_type));
      bitmap->draw_text(x, y, text, *font);
      return mrb_nil_value();
   }

   mrb_value bitmap_draw_texture(mrb_state* mrb, mrb_value self)
   {
      return mrb_nil_value();
   }
}

r_bitmap::r_bitmap(RubyLoader& ruby) : ruby(ruby)
{
   auto ref = this->ruby.bind_class("Bitmap");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
   this->ruby.bind_instance_method(ref, "initialize", bitmap_initialize, MRB_ARGS_ARG(0, 2));
   this->ruby.bind_instance_method(ref, "width", bitmap_width, MRB_ARGS_NONE());
   this->ruby.bind_instance_method(ref, "height", bitmap_height, MRB_ARGS_NONE());
   this->ruby.bind_instance_method(ref, "clear", bitmap_clear, MRB_ARGS_NONE());
   this->ruby.bind_instance_method(ref, "resize", bitmap_resize, MRB_ARGS_REQ(2));
   this->ruby.bind_instance_method(ref, "draw_text", bitmap_draw_text, MRB_ARGS_REQ(4));
   this->ruby.bind_instance_method(ref, "draw_texture", bitmap_draw_texture, MRB_ARGS_NONE());
}
