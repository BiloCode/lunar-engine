#pragma once

#include <Engine/core/font.h>
#include <Engine/resources/ruby_loader.h>
#include <Engine/resources/fonts_cache.h>

namespace ruby
{
   void bind_fonts(RubyLoader& ruby, FontsCache& fonts);
}
