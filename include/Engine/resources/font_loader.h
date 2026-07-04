#pragma once

#include "font_manager.h"

class FontLoader
{
public:
   FontLoader(const std::string& path);
   const FontManager& get_cache() const;

private:
   FontManager fonts;
   FontManager load_fonts(const std::string& path);
};
