#include <Engine/bindings/r_audio.h>

void ruby::bind_audio(RubyLoader& ruby)
{
   auto ref = ruby.bind_class("Audio");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
}
