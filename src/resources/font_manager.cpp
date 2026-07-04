#include <Engine/resources/font_manager.h>

const sf::Font& FontManager::back()
{
   return get(paths.end()->first);
}

const sf::Font& FontManager::front()
{
   return get(paths.begin()->first);
}

const sf::Font& FontManager::get(const std::string& key)
{
   if (auto it = fonts.find(key); it != fonts.end()) {
      return it->second;
   }

   auto path = paths.find(key);

   if (path == paths.end()) {
      throw std::runtime_error("[Fonts]: Missing font resource '" + key + "'");
   }

   sf::Font font;

   if (!font.openFromFile(path->second)) {
      throw std::runtime_error("[Fonts]: Failed to load " + path->second.string());
   }

   auto [it, inserted] = fonts.emplace(key, std::move(font));
   return it->second;
}

void FontManager::add(const std::string& key, std::filesystem::path value)
{
   auto [it, inserted] = paths.emplace(key, value);

   if (!inserted) {
      throw std::runtime_error("[Fonts]: Duplicate key '" + key + "'");
   }
}
