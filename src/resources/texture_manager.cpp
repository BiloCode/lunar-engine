#include <Engine/resources/texture_manager.h>

const sf::Texture& TextureManager::get(const std::string& key)
{
   if (auto it = textures.find(key); it != textures.end()) {
      return it->second;
   }

   auto path = paths.find(key);

   if (path == paths.end()) {
      throw std::runtime_error("[Texture]: Texture not found: " + key);
   }

   sf::Texture texture;

   if (texture.loadFromFile(path->second)) {
      texture.setSmooth(false);
      texture.setRepeated(false);
      auto [it, _] = textures.emplace(key, std::move(texture));
      return it->second;
   }

   throw std::runtime_error("[Texture]: Failed to load " + path->second.string());
}

void TextureManager::add(const std::string& key, std::filesystem::path value)
{
   paths.emplace(key, value);
}

void TextureManager::remove(const std::string& key)
{
   paths.erase(key);
   if (textures.find(key) != textures.end()) {
      textures.erase(key);
   }
}
