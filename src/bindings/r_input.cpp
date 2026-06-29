#include <Engine/bindings/r_input.h>

void ruby::bind_input(RubyLoader& ruby)
{
   auto ref = ruby.bind_class("Input");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
}
