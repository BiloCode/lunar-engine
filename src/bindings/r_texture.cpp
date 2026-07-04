#include <Engine/bindings/r_texture.h>
#include <Engine/singletons/interpreter.h>

namespace
{
   mrb_value texture_new(mrb_state* mrb, mrb_value self)
   {
      mrb_raise(mrb, E_RUNTIME_ERROR, "Texture cannot be instantiated");
      return mrb_nil_value();
   }
}

void ruby::bind_texture()
{
   auto* ref = Interpreter::bind_class("Texture");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
   Interpreter::bind_singleton_method(ref, "new", texture_new, MRB_ARGS_NONE());
}
