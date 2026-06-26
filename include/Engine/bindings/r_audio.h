#pragma once

#include <Engine/resources/ruby_loader.h>

class r_audio
{
public:
   r_audio(RubyLoader& ruby);

private:
   RubyLoader& ruby;
};
