#pragma once

#include <Engine/core/color.h>
#include <Engine/resources/ruby_loader.h>

class r_color
{
public:
   r_color(RubyLoader& ruby);

private:
   RubyLoader& ruby;
};
