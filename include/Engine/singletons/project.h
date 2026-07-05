#pragma once

#include <string>
#include <unordered_map>

class Project
{
public:
   static void load();
   template<typename T> static T get_settings(const std::string& name, T fallback);

private:
   inline static std::unordered_map<std::string, std::string> settings = {};
};
