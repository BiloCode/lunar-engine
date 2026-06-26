#pragma once

#include <Engine/resources/ruby_loader.h>
#include <Engine/resources/graphics_loader.h>

class r_graphics_cache
{
public:
   r_graphics_cache(RubyLoader& ruby, GraphicsCache& graphics);

private:
   RubyLoader& ruby;
};
