#include <Engine/bindings/r_color.h>
#include <Engine/bindings/r_types.h>

namespace
{
   mrb_value color_initialize(mrb_state* mrb, mrb_value self)
   {
      Color* color;
      mrb_int r, g, b, a;
      mrb_int args_c = mrb_get_args(mrb, "iii|i", &r, &g, &b, &a);

      if (args_c == 3) {
         color = new Color(r, g, b);
      }
      else if (args_c == 4) {
         color = new Color(r, g, b, a);
      }
      else {
         mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid arguments");
      }

      mrb_data_init(self, color, &r_color_type);
      return self;
   }
}

r_color::r_color(RubyLoader& ruby) : ruby(ruby)
{
   auto ref = this->ruby.bind_class("Color");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
   this->ruby.bind_instance_method(ref, "initialize", color_initialize, MRB_ARGS_ARG(3, 1));
}
