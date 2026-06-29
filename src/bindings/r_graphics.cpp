#include <Engine/bindings/r_graphics.h>
#include <Engine/bindings/r_types.h>

void ruby::bind_graphics(RubyLoader& ruby, GraphicsCache& graphics)
{
   auto ref = ruby.bind_module("Graphics");
}
