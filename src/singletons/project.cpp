#include <Engine/singletons/project.h>
#include <Engine/utils/files.h>
#include <Engine/utils/paths.h>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace Files = Engine::Files;
namespace Paths = Engine::Paths;

std::unordered_map<std::string, std::string> Project::settings = {};

void Project::load()
{
   auto basepath = Paths::get_executable_dir() / "game.cfg";

   if (!std::filesystem::exists(basepath))
   {
      std::cerr << "[Project]: Settings not found (game.cfg)" << "\n";
      return;
   }

   std::ifstream file(basepath);

   if (!file.is_open())
   {
      return;
   }

   std::string line;

   while(std::getline(file, line))
   {
      if (line.empty())
      {
         continue;
      }

      line = Files::str_trim(line);

      if (auto fl = line.front(); fl == '#' )
      {
         continue;
      }

      if (auto ps = line.find("="); ps != std::string::npos)
      {
         std::string key = Files::str_trim(line.substr(0, ps));
         std::string value = Files::str_trim(line.substr(ps + 1));
         settings.emplace(key, value);
      }
   }

   file.close();
}

template<typename T> T Project::get_settings(const std::string&, T fallback)
{
   static_assert(sizeof(T) == 0, "Unsupported setting type.");
}

template<> int Project::get_settings(const std::string& name, int fallback)
{
   if (auto it = settings.find(name); it != settings.end()) {
      return Files::int_cast(it->second);
   }
   return fallback;
}

template<> unsigned int Project::get_settings(const std::string& name, unsigned int fallback)
{
   if (auto it = settings.find(name); it != settings.end()) {
      return Files::int_cast(it->second);
   }
   return fallback;
}

template<> bool Project::get_settings(const std::string& name, bool fallback)
{
   if (auto it = settings.find(name); it != settings.end()) {
      return Files::bool_cast(it->second);
   }
   return fallback;
}

template<> std::string Project::get_settings(const std::string& name, std::string fallback)
{
   if (auto it = settings.find(name); it != settings.end()) {
      return it->second;
   }
   return fallback;
}
