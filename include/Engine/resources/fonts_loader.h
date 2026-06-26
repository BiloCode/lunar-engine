#pragma once

#include "fonts_cache.h"

class FontsLoader
{
public:
   FontsLoader(const std::string& path);
   const FontsCache& get_cache() const;

private:
   FontsCache fonts;
   FontsCache load_fonts(const std::string& path);
};
