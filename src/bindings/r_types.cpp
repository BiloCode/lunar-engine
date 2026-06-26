#include <Engine/bindings/r_types.h>
#include <Engine/core/font.h>
#include <Engine/core/color.h>
#include <Engine/core/sprite.h>
#include <Engine/core/bitmap.h>

const mrb_data_type r_font_type = {
   "Font",
   [](mrb_state*, void* ptr) {
      delete static_cast<Font*>(ptr);
   }
};

const mrb_data_type r_bitmap_type = {
   "Bitmap",
   [](mrb_state*, void* ptr) {
      delete static_cast<Bitmap*>(ptr);
   }
};

const mrb_data_type r_color_type = {
   "Color",
   [](mrb_state*, void* ptr) {
      delete static_cast<Color*>(ptr);
   }
};

const mrb_data_type r_sprite_type = {
   "Sprite",
   [](mrb_state*, void* ptr) {
      delete static_cast<Sprite*>(ptr);
   }
};

const mrb_data_type r_input_type = {
   "Input",
   nullptr
};

const mrb_data_type r_audio_type = {
   "Audio",
   nullptr
};

const mrb_data_type r_fonts_cache_type = {
   "FontsCache",
   nullptr
};

const mrb_data_type r_graphics_cache_type = {
   "GraphicsCache",
   nullptr
};
