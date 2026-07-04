#include <Engine/resources/texture_loader.h>
#include <Engine/utils/path.h>
#include <iostream>

namespace Path = Engine::Path;

TextureLoader::TextureLoader(const std::string& path) : textures(load_textures(path))
{
}

const TextureManager& TextureLoader::get_cache()
{
   return textures;
}

TextureManager TextureLoader::load_textures(const std::string& path)
{
   std::filesystem::path basepath = Path::get_executable_dir() / path;

   if (!std::filesystem::exists(basepath))
   {
      std::cerr << "[TextureLoader]: Path does not exist -> \"" << basepath << "\"" << std::endl;
      return {};
   }

   if (!std::filesystem::is_directory(basepath))
   {
      std::cerr << "[TextureLoader]: Path is not a directory -> \"" << basepath << "\"" << std::endl;
      return {};
   }

   TextureManager textures;

   for (const auto& entry : std::filesystem::recursive_directory_iterator(basepath))
   {
      if (entry.is_regular_file()) {
         auto key = std::filesystem::relative(entry.path(), basepath).string();
         auto value = entry.path();
         textures.add(key, value);
      }
   }

   return textures;
}
