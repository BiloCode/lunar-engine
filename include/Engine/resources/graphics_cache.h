#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <filesystem>

class GraphicsCache
{
public:
   const sf::Texture& operator[](const std::string& key);
   void add(const std::string& key, std::filesystem::path value);
   void remove(const std::string& key);

private:
   std::map<std::string, sf::Texture> textures;
   std::map<std::string, std::filesystem::path> paths;
};
