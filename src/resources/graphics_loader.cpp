#include <Engine/resources/graphics_loader.h>
#include <Engine/utils/paths.h>
#include <iostream>

namespace Paths = Engine::Paths;

GraphicsLoader::GraphicsLoader(const std::string& path) : graphics(load_graphics(path))
{
}

const GraphicsCache& GraphicsLoader::get_cache()
{
   return graphics;
}

GraphicsCache GraphicsLoader::load_graphics(const std::string& path)
{
   std::filesystem::path basepath = Paths::get_executable_dir() / path;

   if (!std::filesystem::exists(basepath))
   {
      std::cerr << "[GraphicsLoader]: Path does not exist -> \"" << basepath << "\"" << std::endl;
      return {};
   }

   if (!std::filesystem::is_directory(basepath))
   {
      std::cerr << "[GraphicsLoader]: Path is not a directory -> \"" << basepath << "\"" << std::endl;
      return {};
   }

   GraphicsCache graphics;

   for (const auto& entry : std::filesystem::recursive_directory_iterator(basepath))
   {
      if (entry.is_regular_file()) {
         auto key = std::filesystem::relative(entry.path(), basepath).string();
         auto value = entry.path();
         graphics.add(key, value);
      }
   }

   return graphics;
}
