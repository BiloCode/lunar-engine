#pragma once

#include <Engine/resources/ruby_loader.h>

class r_input
{
public:
   r_input(RubyLoader& ruby);

private:
   RubyLoader& ruby;
};
