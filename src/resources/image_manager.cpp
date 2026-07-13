#include <Engine/resources/image_manager.h>

#include <Engine/utils/path.h>
#include <Engine/utils/debug.h>
#include <Engine/singletons/runtime.h>

namespace Path = Engine::Path;
namespace Debug = Engine::Debug;

ImageManager::ImageManager()
{
   auto basepath = Path::get_executable_dir() / "graphics";

   if (!std::filesystem::exists(basepath))
   {
      Debug::print_error("[ImageManager]: Path does not exist -> \"", basepath, "\"");
      return;
   }

   if (!std::filesystem::is_directory(basepath))
   {
      Debug::print_error("[ImageManager]: Path is not a directory -> \"", basepath, "\"");
      return;
   }

   for (const auto& entry : std::filesystem::recursive_directory_iterator(basepath))
   {
      if (entry.is_regular_file()) {
         auto key = std::filesystem::relative(entry.path(), basepath).generic_string();
         auto value = entry.path();
         image_paths.emplace(key, value);
      }
   }
}

ImageManager::~ImageManager()
{
   dispose();
}

const SDL_Surface* ImageManager::load(const std::string& key)
{
   if (auto it = image_files.find(key); it != image_files.end()) {
      return it->second;
   }

   auto path = image_paths.find(key);

   if (path == image_paths.end()) {
      throw std::runtime_error("[ImageManager]: Image not found -> \"" + key + "\"");
   }

   auto* surface = IMG_Load(path->second.string().c_str());

   if (surface != nullptr) {
      auto [it, inserted] = image_files.emplace(key, surface);
      return it->second;
   }

   throw std::runtime_error("[ImageManager]: Failed to load " + path->second.string());
}

void ImageManager::on_dispose()
{
   for (auto& [_, image] : image_files) {
      if (image != nullptr) {
         SDL_DestroySurface(image);
      }
   }
}