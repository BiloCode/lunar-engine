#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <map>
#include <string>
#include <filesystem>
#include <iostream>

class TextureManager
{
public:
   TextureManager();
   const SDL_Texture* get(const std::string& key);

private:
   std::map<std::string, SDL_Texture*> texture_files;
   std::map<std::string, std::filesystem::path> texture_paths;
};
