#pragma once

#include <SDL3_image/SDL_image.h>
#include <map>
#include <string>
#include <filesystem>
#include <Engine/interfaces/disposable.h>

class TextureManager : public Disposable
{
public:
   TextureManager();
   ~TextureManager();
   TextureManager(const TextureManager&) = delete;
   TextureManager& operator=(const TextureManager&) = delete;
   const SDL_Texture* get(const std::string& key);

protected:
   void on_dispose() override;

private:
   std::map<std::string, SDL_Texture*> texture_files;
   std::map<std::string, std::filesystem::path> texture_paths;
};
