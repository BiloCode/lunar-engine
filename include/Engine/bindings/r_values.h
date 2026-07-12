#pragma once

#include <mruby.h>
#include <unordered_map>

class Bitmap;
class Sprite;

extern std::unordered_map<Bitmap*, mrb_value> bitmap_fonts;
extern std::unordered_map<Sprite*, mrb_value> sprite_bitmaps;