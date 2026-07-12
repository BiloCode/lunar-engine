#include <Engine/bindings/r_sprite.h>

#include <mruby.h>
#include <mruby/class.h>
#include <Engine/core/sprite.h>
#include <Engine/core/bitmap.h>
#include <Engine/bindings/r_types.h>
#include <Engine/bindings/r_values.h>
#include <Engine/singletons/interpreter.h>

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
      auto* sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));

      if (auto it = sprite_bitmaps.find(sprite); it != sprite_bitmaps.end()) {
         return it->second;
      }

      return mrb_nil_value();
   }

   mrb_value sprite_bitmap_set(mrb_state* mrb, mrb_value self)
   {
      mrb_value obj;
      mrb_get_args(mrb, "o", &obj);

      auto* bitmap = static_cast<Bitmap*>(mrb_data_get_ptr(mrb, obj, &r_bitmap_type));
      auto* sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));

      if (auto it = sprite_bitmaps.find(sprite); it != sprite_bitmaps.end()) {
         mrb_gc_unregister(mrb, it->second);
         sprite_bitmaps.erase(it);
      }

      sprite->bitmap = bitmap;
      sprite_bitmaps[sprite] = obj;
      mrb_gc_register(mrb, obj);

      return mrb_nil_value();
   }

   mrb_value sprite_x(mrb_state* mrb, mrb_value self)
   {
      auto* sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      return mrb_float_value(mrb, sprite->get_x());
   }

   mrb_value sprite_x_set(mrb_state* mrb, mrb_value self)
   {
      mrb_float x;
      mrb_get_args(mrb, "f", &x);
      auto* sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      sprite->set_x(static_cast<float>(x));
      return mrb_nil_value();
   }

   mrb_value sprite_y(mrb_state* mrb, mrb_value self)
   {
      auto* sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      return mrb_float_value(mrb, sprite->get_y());
   }

   mrb_value sprite_y_set(mrb_state* mrb, mrb_value self)
   {
      mrb_float y;
      mrb_get_args(mrb, "f", &y);
      auto* sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      sprite->set_y(static_cast<float>(y));
      return mrb_nil_value();
   }

   mrb_value sprite_z(mrb_state* mrb, mrb_value self)
   {
      auto* sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      return mrb_float_value(mrb, sprite->get_z());
   }

   mrb_value sprite_z_set(mrb_state* mrb, mrb_value self)
   {
      mrb_float z;
      mrb_get_args(mrb, "f", &z);
      auto* sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      sprite->set_z(static_cast<float>(z));
      return mrb_nil_value();
   }

   mrb_value sprite_visible(mrb_state* mrb, mrb_value self)
   {
      auto* sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      return mrb_bool_value(sprite->is_visible());
   }

   mrb_value sprite_visible_set(mrb_state* mrb, mrb_value self)
   {
      mrb_float visible;
      mrb_get_args(mrb, "b", &visible);
      auto* sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      sprite->set_visible(visible);
      return mrb_nil_value();
   }

   mrb_value sprite_dispose(mrb_state* mrb, mrb_value self)
   {
      auto* sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      sprite->dispose();
      return mrb_nil_value();
   }

   mrb_value sprite_disposed(mrb_state* mrb, mrb_value self)
   {
      auto* sprite = static_cast<Sprite*>(mrb_data_get_ptr(mrb, self, &r_sprite_type));
      return mrb_bool_value(sprite->is_invalid());
   }
}

void ruby::bind_sprite()
{
   auto ref = Interpreter::bind_class("Sprite");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
   Interpreter::bind_instance_method(ref, "initialize", sprite_initialize, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "bitmap", sprite_bitmap, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "bitmap=", sprite_bitmap_set, MRB_ARGS_REQ(1));
   Interpreter::bind_instance_method(ref, "x", sprite_x, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "x=", sprite_x_set, MRB_ARGS_REQ(1));
   Interpreter::bind_instance_method(ref, "y", sprite_y, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "y=", sprite_y_set, MRB_ARGS_REQ(1));
   Interpreter::bind_instance_method(ref, "z", sprite_z, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "z=", sprite_z_set, MRB_ARGS_REQ(1));
   Interpreter::bind_instance_method(ref, "visible", sprite_visible, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "visible=", sprite_visible_set, MRB_ARGS_REQ(1));
   Interpreter::bind_instance_method(ref, "dispose", sprite_dispose, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "disposed?", sprite_disposed, MRB_ARGS_NONE());
}
