#pragma once

#include "settings.h"
#include <vector>
#include <optional>

class SettingsLoader
{
public:
   SettingsLoader(const std::string& path);
   ~SettingsLoader() = default;
   const Settings& get_settings() const;

private:
   Settings settings;
   Settings default_settings();
   std::optional<Settings> load_settings(const std::string& path);
};
