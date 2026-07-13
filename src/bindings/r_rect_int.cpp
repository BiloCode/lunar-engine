#include <Engine/bindings/r_rect_int.h>

#include <mruby.h>
#include <mruby/hash.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <Engine/core/rect.h>
#include <Engine/utils/ruby.h>
#include <Engine/bindings/r_types.h>
#include <Engine/singletons/interpreter.h>

namespace Ruby = Engine::Ruby;

namespace
{
   mrb_value rect_initialize(mrb_state* mrb, mrb_value self)
   {
      mrb_value hash;
      mrb_int args_c = mrb_get_args(mrb, "|H", &hash);

      if (args_c == 0) {
         mrb_data_init(self, new Rect<int>(), &r_rect2i_type);
      }
      else if (args_c == 1) {
         mrb_sym sym_x = mrb_intern_lit(mrb, "x");
         mrb_sym sym_y = mrb_intern_lit(mrb, "y");
         mrb_sym sym_width = mrb_intern_lit(mrb, "w");
         mrb_sym sym_height = mrb_intern_lit(mrb, "h");
   
         mrb_value vx = mrb_hash_get(mrb, hash, mrb_symbol_value(sym_x));
         mrb_value vy = mrb_hash_get(mrb, hash, mrb_symbol_value(sym_y));
         mrb_value vw = mrb_hash_get(mrb, hash, mrb_symbol_value(sym_width));
         mrb_value vh = mrb_hash_get(mrb, hash, mrb_symbol_value(sym_height));
   
         int x = Ruby::to_int(mrb, vx);
         int y = Ruby::to_int(mrb, vy);
         int width = Ruby::to_int(mrb, vw);
         int height = Ruby::to_int(mrb, vh);
   
         mrb_data_init(self, new Rect<int>(x, y, width, height), &r_rect2i_type);
      }
      else {
         mrb_raise(mrb, E_RUNTIME_ERROR, "Invalid arguments");
      }

      return self;
   }
}

void ruby::bind_rect_int()
{
   auto* ref = Interpreter::bind_class("Rect2i");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
   Interpreter::bind_instance_method(ref, "initialize", rect_initialize, MRB_ARGS_ARG(0, 1));
}