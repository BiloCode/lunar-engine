#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <vector>
#include <filesystem>

class FontsCache
{
public:
   const sf::Font& back();
   const sf::Font& front();
   const sf::Font& get(const std::string& key);
   void add(const std::string& key, std::filesystem::path value);

private:
   std::map<std::string, sf::Font> fonts;
   std::map<std::string, std::filesystem::path> paths;
};
