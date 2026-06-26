#pragma once

#include <Engine/core/bitmap.h>
#include <Engine/resources/ruby_loader.h>

class r_bitmap
{
public:
   r_bitmap(RubyLoader& ruby);

private:
   RubyLoader& ruby;
};
