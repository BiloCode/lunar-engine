#include <Engine/bindings/r_audio.h>
#include <Engine/singletons/interpreter.h>

void ruby::bind_audio()
{
   auto* ref = Interpreter::bind_class("Audio");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
}
