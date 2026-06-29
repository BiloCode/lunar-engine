#include <Engine/bindings/r_sprite.h>
#include <Engine/bindings/r_types.h>
#include <Engine/core/sprite.h>
#include <Engine/core/bitmap.h>

namespace
{
   mrb_value sprite_initialize(mrb_state* mrb, mrb_value self)
   {
      Sprite* sprite = new Sprite();
      mrb_data_init(self, sprite, &r_sprite_type);
      return self;
   }

   mrb_value sprite_bitmap(mrb_state* mrb, mrb_value self)
   {
      auto klass = mrb_class_get(mrb, "Bitmap");
      auto sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      if (!sprite->bitmap) {
         return mrb_nil_value();
      }
      return mrb_obj_value(
         mrb_data_object_alloc(mrb, klass, sprite->bitmap, &r_bitmap_type)
      );
   }

   mrb_value sprite_bitmap_set(mrb_state* mrb, mrb_value self)
   {
      mrb_value obj;
      mrb_get_args(mrb, "o", &obj);
      auto bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, obj, &r_bitmap_type));
      auto sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      sprite->bitmap = bitmap;
      return mrb_nil_value();
   }

   mrb_value sprite_x(mrb_state* mrb, mrb_value self)
   {
      auto sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      return mrb_float_value(mrb, sprite->x);
   }

   mrb_value sprite_x_set(mrb_state* mrb, mrb_value self)
   {
      mrb_float x;
      mrb_get_args(mrb, "f", &x);
      auto sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      sprite->x = (float)x;
      return mrb_nil_value();
   }

   mrb_value sprite_y(mrb_state* mrb, mrb_value self)
   {
      auto sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      return mrb_float_value(mrb, sprite->y);
   }

   mrb_value sprite_y_set(mrb_state* mrb, mrb_value self)
   {
      mrb_float y;
      mrb_get_args(mrb, "f", &y);
      auto sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      sprite->y = (float)y;
      return mrb_nil_value();
   }

   mrb_value sprite_dispose(mrb_state* mrb, mrb_value self)
   {
      auto sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      sprite->dispose();
      return mrb_nil_value();
   }
}

void ruby::bind_sprite(RubyLoader& ruby)
{
   auto ref = ruby.bind_class("Sprite");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
   ruby.bind_instance_method(ref, "initialize", sprite_initialize, MRB_ARGS_NONE());
   ruby.bind_instance_method(ref, "bitmap", sprite_bitmap, MRB_ARGS_NONE());
   ruby.bind_instance_method(ref, "bitmap=", sprite_bitmap_set, MRB_ARGS_REQ(1));
   ruby.bind_instance_method(ref, "x", sprite_x, MRB_ARGS_NONE());
   ruby.bind_instance_method(ref, "x=", sprite_x_set, MRB_ARGS_REQ(1));
   ruby.bind_instance_method(ref, "y", sprite_y, MRB_ARGS_NONE());
   ruby.bind_instance_method(ref, "y=", sprite_y_set, MRB_ARGS_REQ(1));
   ruby.bind_instance_method(ref, "dispose", sprite_dispose, MRB_ARGS_NONE());
}
