#pragma once

#include "texture_manager.h"

class TextureLoader
{
public:
   TextureLoader(const std::string& path);
   const TextureManager& get_cache();

private:
   TextureManager textures;
   TextureManager load_textures(const std::string& path);
};
