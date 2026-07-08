#include <Engine/resources/texture_manager.h>
#include <Engine/singletons/runtime.h>
#include <Engine/utils/path.h>

namespace Path = Engine::Path;

TextureManager::TextureManager()
{
   auto basepath = Path::get_executable_dir() / "graphics";

   if (!std::filesystem::exists(basepath))
   {
      std::cerr << "[TextureManager]: Path does not exist -> \"" << basepath << "\"" << std::endl;
      return;
   }

   if (!std::filesystem::is_directory(basepath))
   {
      std::cerr << "[TextureManager]: Path is not a directory -> \"" << basepath << "\"" << std::endl;
      return;
   }

   for (const auto& entry : std::filesystem::recursive_directory_iterator(basepath))
   {
      if (entry.is_regular_file()) {
         auto key = std::filesystem::relative(entry.path(), basepath).string();
         auto value = entry.path();
         texture_paths.emplace(key, value);
      }
   }
}

TextureManager::~TextureManager()
{
   for (auto& [_, texture] : texture_files) {
      if (texture != nullptr) {
         SDL_DestroyTexture(texture);
      }
   }
}

const SDL_Texture* TextureManager::get(const std::string& key)
{
   if (auto it = texture_files.find(key); it != texture_files.end()) {
      return it->second;
   }

   auto path = texture_paths.find(key);

   if (path == texture_paths.end()) {
      throw std::runtime_error("[Texture]: Texture not found -> \"" + key + "\"");
   }

   SDL_Texture* texture = IMG_LoadTexture(Runtime::get_renderer(), path->second.string().c_str());

   if (texture != NULL) {
      auto [it, inserted] = texture_files.emplace(key, texture);
      return it->second;
   }

   throw std::runtime_error("[Texture]: Failed to load " + path->second.string());
}
