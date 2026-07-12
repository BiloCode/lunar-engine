#pragma once

#include <mruby.h>
#include <unordered_map>

class Bitmap;

extern std::unordered_map<Bitmap*, mrb_value> bitmap_fonts;