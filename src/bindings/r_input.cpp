#include <Engine/bindings/r_input.h>

r_input::r_input(RubyLoader& ruby) : ruby(ruby)
{
   auto ref = this->ruby.bind_class("Input");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
}
