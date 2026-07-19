#include <Engine/bindings/r_rect_int.h>

#include <mruby.h>
#include <mruby/class.h>
#include <Engine/core/rect.h>
#include <Engine/utils/ruby.h>
#include <Engine/utils/string.h>
#include <Engine/bindings/r_types.h>
#include <Engine/singletons/interpreter.h>

namespace Ruby = Engine::Ruby;
namespace String = Engine::String;

namespace
{
   mrb_value rect_initialize(mrb_state* mrb, mrb_value self)
   {
      mrb_int x, y, width, height;

      constexpr mrb_int kw_num = 4;
      constexpr mrb_int kw_required = 0;

      mrb_sym kw_names[] = {
         mrb_intern_lit(mrb, "x"),
         mrb_intern_lit(mrb, "y"),
         mrb_intern_lit(mrb, "width"),
         mrb_intern_lit(mrb, "height") 
      };
      mrb_value kw_values[kw_num];
      mrb_kwargs kw_args = {
         kw_num,
         kw_required,
         kw_names,
         kw_values,
         NULL
      };

      mrb_int args_c = mrb_get_args(mrb, "|iiii:", &x, &y, &width, &height, &kw_args);
      
      if (args_c > 0) {
         if (args_c < 4) {
            mrb_raise(mrb, E_ARGUMENT_ERROR, "Invalid arguments");
            return self;
         }
         mrb_data_init(self, new Rect<int>(x, y, width, height), &r_rect2i_type);
      }
      else {
         for (int i = 0; i < kw_num; ++i) {
            if (mrb_undef_p(kw_values[i])) {
               mrb_data_init(self, new Rect<int>(), &r_rect2i_type);
               return self;
            }
         }
         
         int x = Ruby::to_int(mrb, kw_values[0]);
         int y = Ruby::to_int(mrb, kw_values[1]);
         int width = Ruby::to_int(mrb, kw_values[2]);
         int height = Ruby::to_int(mrb, kw_values[3]);

         mrb_data_init(self, new Rect<int>(x, y, width, height), &r_rect2i_type);
      }

      return self;
   }

   mrb_value rect_x(mrb_state* mrb, mrb_value self)
   {
      auto rect = static_cast<Rect<int>*>(mrb_data_get_ptr(mrb, self, &r_rect2i_type));
      return mrb_fixnum_value(rect->x);
   }

   mrb_value rect_y(mrb_state* mrb, mrb_value self)
   {
      auto rect = static_cast<Rect<int>*>(mrb_data_get_ptr(mrb, self, &r_rect2i_type));
      return mrb_fixnum_value(rect->y);
   }

   mrb_value rect_width(mrb_state* mrb, mrb_value self)
   {
      auto rect = static_cast<Rect<int>*>(mrb_data_get_ptr(mrb, self, &r_rect2i_type));
      return mrb_fixnum_value(rect->width);
   }

   mrb_value rect_height(mrb_state* mrb, mrb_value self)
   {
      auto rect = static_cast<Rect<int>*>(mrb_data_get_ptr(mrb, self, &r_rect2i_type));
      return mrb_fixnum_value(rect->height);
   }

   mrb_value rect_x_set(mrb_state* mrb, mrb_value self)
   {
      mrb_int x;
      mrb_get_args(mrb, "i", &x);
      auto rect = static_cast<Rect<int>*>(mrb_data_get_ptr(mrb, self, &r_rect2i_type));
      rect->x = x;
      return mrb_nil_value();
   }

   mrb_value rect_y_set(mrb_state* mrb, mrb_value self)
   {
      mrb_int y;
      mrb_get_args(mrb, "i", &y);
      auto rect = static_cast<Rect<int>*>(mrb_data_get_ptr(mrb, self, &r_rect2i_type));
      rect->y = y;
      return mrb_nil_value();
   }

   mrb_value rect_width_set(mrb_state* mrb, mrb_value self)
   {
      mrb_int width;
      mrb_get_args(mrb, "i", &width);
      auto rect = static_cast<Rect<int>*>(mrb_data_get_ptr(mrb, self, &r_rect2i_type));
      rect->width = width;
      return mrb_nil_value();
   }

   mrb_value rect_height_set(mrb_state* mrb, mrb_value self)
   {
      mrb_int height;
      mrb_get_args(mrb, "i", &height);
      auto rect = static_cast<Rect<int>*>(mrb_data_get_ptr(mrb, self, &r_rect2i_type));
      rect->height = height;
      return mrb_nil_value();
   }

   mrb_value rect_to_string(mrb_state* mrb, mrb_value self)
   {
      auto rect = static_cast<Rect<int>*>(mrb_data_get_ptr(mrb, self, &r_rect2i_type));
      auto output = String::format_object("#<Rect2i>", {
         { "x", std::to_string(rect->x) },
         { "y", std::to_string(rect->y) },
         { "width", std::to_string(rect->width) },
         { "height", std::to_string(rect->height) }
      });
      return mrb_str_new_cstr(mrb, output.c_str());
   }
}

void ruby::bind_rect_int()
{
   auto* ref = Interpreter::bind_class("Rect2i");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
   Interpreter::bind_instance_method(ref, "initialize", rect_initialize, MRB_ARGS_ARG(0, 4));
   Interpreter::bind_instance_method(ref, "x", rect_x, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "x=", rect_x_set, MRB_ARGS_REQ(1));
   Interpreter::bind_instance_method(ref, "y", rect_y, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "y=", rect_y_set, MRB_ARGS_REQ(1));
   Interpreter::bind_instance_method(ref, "width", rect_width, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "width=", rect_width_set, MRB_ARGS_REQ(1));
   Interpreter::bind_instance_method(ref, "height", rect_height, MRB_ARGS_NONE());
   Interpreter::bind_instance_method(ref, "height=", rect_height_set, MRB_ARGS_REQ(1));
   Interpreter::bind_instance_method(ref, "to_s", rect_to_string, MRB_ARGS_NONE());
}