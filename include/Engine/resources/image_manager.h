#pragma once

#include <SDL3_image/SDL_image.h>
#include <map>
#include <string>
#include <filesystem>
#include <Engine/interfaces/disposable.h>

class ImageManager : public Disposable
{
public:
   ImageManager();
   ImageManager(const ImageManager&) = delete;
   ImageManager& operator=(const ImageManager&) = delete;
   ~ImageManager();
   const SDL_Surface* load(const std::string& key);

protected:
   void on_dispose() override;

private:
   std::map<std::string, SDL_Surface*> image_files;
   std::map<std::string, std::filesystem::path> image_paths;
};
