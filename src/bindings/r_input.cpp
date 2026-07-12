#include <Engine/bindings/r_input.h>

#include <mruby.h>
#include <mruby/class.h>
#include <Engine/singletons/interpreter.h>

void ruby::bind_input()
{
   auto ref = Interpreter::bind_class("Input");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
}
