#include <Engine/resources/font_manager.h>

#include <iostream>
#include <Engine/utils/path.h>

namespace Path = Engine::Path;

FontManager::FontManager()
{
   if (!TTF_Init()) {
      throw std::runtime_error(SDL_GetError());
   }

   std::string basepath = (Path::get_executable_dir() / "fonts").string();
   std::string extensions[3] = { ".ttf", ".otf", ".cff" };

   if (!std::filesystem::exists(basepath))
   {
      std::cerr << "[FontManager]: Path does not exist -> \"" << basepath << "\"" << std::endl;
      return;
   }

   if (!std::filesystem::is_directory(basepath))
   {
      std::cerr << "[FontManager]: Path is not a directory -> \"" << basepath << "\"" << std::endl;
      return;
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
            auto key = std::filesystem::relative(entry.path(), basepath).string();
            auto value = entry.path();
            font_paths.emplace(key, value);
            break;
         }
      }
   }
}

FontManager::~FontManager()
{
   dispose();
}

const TTF_Font* FontManager::get(const std::string& key)
{
   if (auto it = font_files.find(key); it != font_files.end()) {
   return it->second;
   }

   auto path = font_paths.find(key);

   if (path == font_paths.end()) {
      throw std::runtime_error("[Fonts]: Font not found -> \"" + key + "\"");
   }

   TTF_Font* font = TTF_OpenFont(path->second.string().c_str(), 16);

   if (font != nullptr) {
      auto [it, inserted] = font_files.emplace(key, font);
      return it->second;
   }

   throw std::runtime_error("[Fonts]: Failed to load " + path->second.string());
}

void FontManager::on_dispose()
{
   for (auto& [_, font] : font_files) {
      if (font != nullptr) {
         TTF_CloseFont(font);
      }
   }

   TTF_Quit();
}