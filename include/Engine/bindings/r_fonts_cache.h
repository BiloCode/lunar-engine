#pragma once

#include "r_font.h"
#include <Engine/resources/ruby_loader.h>
#include <Engine/resources/fonts_cache.h>

class r_fonts_cache
{
public:
   r_fonts_cache(RubyLoader& ruby, FontsCache& fonts);

private:
   RubyLoader& ruby;
};
