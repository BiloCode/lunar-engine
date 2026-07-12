#include <Engine/bindings/r_types.h>

#include <Engine/core/font.h>
#include <Engine/core/color.h>
#include <Engine/core/vector.h>
#include <Engine/core/sprite.h>
#include <Engine/core/bitmap.h>
#include <Engine/core/texture.h>
#include <Engine/bindings/r_values.h>

const mrb_data_type r_font_type = {
   "Font",
   [](mrb_state*, void* ptr) {
      delete static_cast<Font*>(ptr);
   }
};

const mrb_data_type r_color_type = {
   "Color",
   [](mrb_state*, void* ptr) {
      delete static_cast<Color*>(ptr);
   }
};

const mrb_data_type r_texture_type = {
   "Texture",
   [](mrb_state*, void* ptr) {
      delete static_cast<Texture*>(ptr);
   }
};

const mrb_data_type r_vector2i_type = {
   "Vector2i",
   [](mrb_state*, void* ptr) {
      delete static_cast<Vector<int>*>(ptr);
   }
};

const mrb_data_type r_vector2f_type = {
   "Vector2f",
   [](mrb_state*, void* ptr) {
      delete static_cast<Vector<float>*>(ptr);
   }
};

const mrb_data_type r_bitmap_type = {
   "Bitmap",
   [](mrb_state* mrb, void* ptr) {
      auto* bitmap = static_cast<Bitmap*>(ptr);

      if (auto it = bitmap_fonts.find(bitmap); it != bitmap_fonts.end()) {
         mrb_gc_unregister(mrb, it->second);
         bitmap_fonts.erase(it);
      }

      delete bitmap;
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

const mrb_data_type r_fonts_type = {
   "Fonts",
   nullptr
};

const mrb_data_type r_textures_type = {
   "Graphics",
   nullptr
};

