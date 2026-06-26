#include <Engine/resources/graphics_cache.h>

const sf::Texture& GraphicsCache::operator[](const std::string& key)
{
   if (auto it = textures.find(key); it != textures.end()) {
      return it->second;
   }

   auto path = paths.find(key);

   if (path == paths.end()) {
      throw std::runtime_error("[Graphics]: Texture not found: " + key);
   }

   sf::Texture texture;

   if (texture.loadFromFile(path->second)) {
      texture.setSmooth(false);
      texture.setRepeated(false);
      auto [it, _] = textures.emplace(key, std::move(texture));
      return it->second;
   }

   throw std::runtime_error("[Graphics]: Failed to load " + path->second.string());
}

void GraphicsCache::add(const std::string& key, std::filesystem::path value)
{
   paths.emplace(key, value);
}

void GraphicsCache::remove(const std::string& key)
{
   paths.erase(key);
   if (textures.find(key) != textures.end()) {
      textures.erase(key);
   }
}
