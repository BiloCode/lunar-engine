#pragma once

#include <SDL3/SDL.h>
#include <map>
#include <string>
#include <filesystem>

class TextureManager
{
public:
   const SDL_Texture* get(const std::string& key);
   void add(const std::string& key, std::filesystem::path value);
   void remove(const std::string& key);

private:
   std::map<std::string, SDL_Texture*> texture;
   std::map<std::string, std::filesystem::path> texture_paths;
};
