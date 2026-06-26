#pragma once

#include <Engine/resources/ruby_loader.h>
#include <Engine/resources/graphics_loader.h>

class r_graphics
{
public:
   r_graphics(RubyLoader& ruby, GraphicsCache& graphics);

private:
   RubyLoader& ruby;
};
