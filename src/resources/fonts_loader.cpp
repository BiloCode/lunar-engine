#include <Engine/resources/fonts_loader.h>
#include <Engine/utils/paths.h>
#include <iostream>

namespace Paths = Engine::Paths;

FontsLoader::FontsLoader(const std::string& path) : fonts(load_fonts(path))
{
}

const FontsCache& FontsLoader::get_cache() const
{
   return fonts;
}

FontsCache FontsLoader::load_fonts(const std::string& path)
{
   FontsCache fonts;
   std::string basepath = (Paths::get_executable_dir() / path).string();
   std::string extensions[3] = { ".ttf", ".otf", ".cff" };

   if (!std::filesystem::exists(basepath))
   {
      std::cerr << "[FontLoader]: Path does not exist -> \"" << basepath << "\"" << std::endl;
      return fonts;
   }

   if (!std::filesystem::is_directory(basepath))
   {
      std::cerr << "[FontLoader]: Path is not a directory -> \"" << basepath << "\"" << std::endl;
      return fonts;
   }

   for (const auto& entry : std::filesystem::directory_iterator(basepath))
   {
      if (!entry.is_regular_file())
      {
         continue;
      }

      for (const std::string& extension : extensions)
      {
         if (entry.path().extension().string() == extension)
         {
            auto key = entry.path().filename();
            auto value = entry.path();
            fonts.add(key, value);
            break;
         }
      }
   }

   return fonts;
}
