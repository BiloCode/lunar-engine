#pragma once

#include <Engine/core/font.h>
#include <Engine/resources/ruby_loader.h>

class r_font
{
public:
   r_font(RubyLoader& ruby);

private:
   RubyLoader& ruby;
};
