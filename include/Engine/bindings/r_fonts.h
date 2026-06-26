#pragma once

#include "r_font.h"
#include <Engine/resources/ruby_loader.h>
#include <Engine/resources/fonts_cache.h>

class r_fonts
{
public:
   r_fonts(RubyLoader& ruby, FontsCache& fonts);

private:
   RubyLoader& ruby;
};
