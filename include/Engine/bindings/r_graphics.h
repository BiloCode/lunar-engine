#pragma once

#include <Engine/resources/ruby_loader.h>
#include <Engine/resources/graphics_loader.h>

namespace ruby
{
   void bind_graphics(RubyLoader& ruby, GraphicsCache& graphics);
}
