#pragma once

#include "graphics_cache.h"

class GraphicsLoader {
public:
   GraphicsLoader(const std::string& path);
   const GraphicsCache& get_cache();

private:
   GraphicsCache graphics;
   GraphicsCache load_graphics(const std::string& path);
};
