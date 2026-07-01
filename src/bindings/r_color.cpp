#include <Engine/bindings/r_color.h>
#include <Engine/bindings/r_types.h>

namespace
{
   mrb_value color_initialize(mrb_state* mrb, mrb_value self)
   {
      mrb_int r, g, b, a;
      mrb_int args_c = mrb_get_args(mrb, "iii|i", &r, &g, &b, &a);

      if (args_c == 3) {
         auto color = new Color(r, g, b);
         mrb_data_init(self, color, &r_color_type);
      }
      else if (args_c == 4) {
         auto color = new Color(r, g, b, a);
         mrb_data_init(self, color, &r_color_type);
      }
      else {
         mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid arguments");
      }

      return self;
   }
}

void ruby::bind_color(RubyLoader& ruby)
{
   auto ref = ruby.bind_class("Color");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
   ruby.bind_instance_method(ref, "initialize", color_initialize, MRB_ARGS_ARG(3, 1));
}
