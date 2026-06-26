#include <Engine/resources/settings_loader.h>
#include <Engine/utils/paths.h>
#include <Engine/utils/files.h>
#include <sstream>
#include <fstream>
#include <filesystem>

namespace Paths = Project::Paths;
namespace Files = Project::Files;

SettingsLoader::SettingsLoader(const std::string& path)
{
   settings = load_settings(path).value_or(default_settings());
}

const Settings& SettingsLoader::get_settings() const
{
   return settings;
}

Settings SettingsLoader::default_settings()
{
   return Settings {
      .win_title = "Lunar Engine",
      .win_resizable = true,
      .win_fullscreen = false,
      .screen_w = 1080,
      .screen_h = 720,
      .viewport_w = 640,
      .viewport_h = 480,
      .fps = 60,
      .vsync = true,
      .show_fps = false
   };
}

std::optional<Settings> SettingsLoader::load_settings(const std::string& path)
{
   if (path.empty())
   {
      return std::nullopt;
   }

   std::string fullpath = Paths::get_executable_dir() / path;

   if (std::filesystem::exists(fullpath))
   {
      std::ifstream file(fullpath);

      if (file.is_open())
      {
         std::string line;
         Settings settings;
         Settings settings_def = default_settings();

         while (std::getline(file, line))
         {
            if (line.empty())
            {
               continue;
            }

            auto pos = line.find("=");

            if (pos == std::string::npos)
            {
               continue;
            }

            std::string key = Files::str_trim(line.substr(0, pos));
            std::string value = Files::str_trim(line.substr(pos + 1));

            if (key == "win_title") settings.win_title = value;
            else if (key == "win_resizable") settings.win_resizable = Files::bool_cast(value, settings_def.win_resizable);
            else if (key == "win_fullscreen") settings.win_fullscreen = Files::bool_cast(value, settings_def.win_fullscreen);
            else if (key == "screen_w") settings.screen_w = Files::int_cast(value, settings_def.screen_w);
            else if (key == "screen_h") settings.screen_h = Files::int_cast(value, settings_def.screen_h);
            else if (key == "viewport_w") settings.viewport_w = Files::int_cast(value, settings_def.viewport_w);
            else if (key == "viewport_h") settings.viewport_h = Files::int_cast(value, settings_def.viewport_h);
            else if (key == "fps") settings.fps = Files::int_cast(value, settings_def.fps);
            else if (key == "vsync") settings.vsync = Files::bool_cast(value, settings_def.vsync);
            else if (key == "show_fps") settings.show_fps = Files::bool_cast(value, settings_def.show_fps);
         }

         file.close();
         return settings;
      }
   }

   return std::nullopt;
}
