#include <Engine/bindings/r_audio.h>

r_audio::r_audio(RubyLoader& ruby) : ruby(ruby)
{
   auto ref = this->ruby.bind_class("Audio");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
}
