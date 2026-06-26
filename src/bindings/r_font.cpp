#include <Engine/bindings/r_font.h>
#include <Engine/bindings/r_types.h>

namespace
{
   mrb_value font_new(mrb_state* mrb, mrb_value self)
   {
      mrb_raise(mrb, E_RUNTIME_ERROR, "Font cannot be instantiated");
      return mrb_nil_value();
   }
}

r_font::r_font(RubyLoader& ruby) : ruby(ruby)
{
   auto ref = this->ruby.bind_class("Font");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
   this->ruby.bind_singleton_method(ref, "new", font_new, MRB_ARGS_NONE());
}
