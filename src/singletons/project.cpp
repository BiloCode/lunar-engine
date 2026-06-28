#include <Engine/singletons/project.h>
#include <Engine/utils/path.h>
#include <Engine/utils/string.h>
#include <Engine/utils/boolean.h>
#include <Engine/utils/integer.h>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace Path = Engine::Path;
namespace String = Engine::String;
namespace Boolean = Engine::Boolean;
namespace Integer = Engine::Integer;

std::unordered_map<std::string, std::string> Project::settings = {};

void Project::load()
{
   auto basepath = Path::get_executable_dir() / "game.cfg";

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

      line = String::trim(line);

      if (auto fl = line.front(); fl == '#' )
      {
         continue;
      }

      if (auto ps = line.find("="); ps != std::string::npos)
      {
         std::string key = String::trim(line.substr(0, ps));
         std::string value = String::trim(line.substr(ps + 1));
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
      return Integer::int_cast(it->second);
   }
   return fallback;
}

template<> unsigned int Project::get_settings(const std::string& name, unsigned int fallback)
{
   if (auto it = settings.find(name); it != settings.end()) {
      return Integer::int_cast(it->second);
   }
   return fallback;
}

template<> bool Project::get_settings(const std::string& name, bool fallback)
{
   if (auto it = settings.find(name); it != settings.end()) {
      return Boolean::bool_cast(it->second);
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
