#include <Engine/bindings/r_graphics.h>
#include <Engine/bindings/r_types.h>

r_graphics::r_graphics(RubyLoader& ruby, GraphicsCache& graphics) : ruby(ruby)
{
   auto ref = this->ruby.bind_module("Graphics");
}
