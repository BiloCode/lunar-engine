#include <Engine/bindings/r_values.h>

std::unordered_map<Bitmap*, mrb_value> bitmap_fonts;
std::unordered_map<Sprite*, mrb_value> sprite_bitmaps;