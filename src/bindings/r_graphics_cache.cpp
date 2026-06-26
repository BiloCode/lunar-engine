#include <Engine/bindings/r_graphics_cache.h>
#include <Engine/bindings/r_types.h>

r_graphics_cache::r_graphics_cache(RubyLoader& ruby, GraphicsCache& graphics) : ruby(ruby)
{
   auto ref = this->ruby.bind_class("GraphicsCache");
   MRB_SET_INSTANCE_TT(ref, MRB_TT_CDATA);
}
