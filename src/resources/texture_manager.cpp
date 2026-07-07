#include <Engine/resources/texture_manager.h>

const SDL_Texture* TextureManager::get(const std::string& key)
{
   if (auto it = texture.find(key); it != texture.end()) {
      return it->second;
   }

   auto path = texture_paths.find(key);

   if (path == texture_paths.end()) {
      throw std::runtime_error("[Texture]: Texture not found: " + key);
   }

   /*sf::Texture texture;

   if (texture.loadFromFile(path->second)) {
      texture.setSmooth(false);
      texture.setRepeated(false);
      auto [it, _] = texture.emplace(key, std::move(texture));
      return it->second;
   }*/

   throw std::runtime_error("[Texture]: Failed to load " + path->second.string());
}

void TextureManager::add(const std::string& key, std::filesystem::path value)
{
   texture_paths.emplace(key, value);
}

void TextureManager::remove(const std::string& key)
{
   texture_paths.erase(key);
   if (texture.find(key) != texture.end()) {
      texture.erase(key);
   }
}
