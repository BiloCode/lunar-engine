#include <Engine/utils/files.h>
#include <iostream>
#include <algorithm>

std::string Project::Files::str_trim(const std::string& value)
{
   auto is_space = [](unsigned char c) {
      return std::isspace(c);
   };
   auto start = std::find_if_not(value.begin(), value.end(), is_space);
   if (start == value.end()) return "";
   auto end = std::find_if_not(value.rbegin(), value.rend(), is_space).base();
   return std::string(start, end);
}

int Project::Files::int_cast(const std::string& value, int def_value)
{
   try {
      size_t idx;
      int result = std::stoi(value, &idx);
      if (idx != value.size()) {
         return def_value;
      }
      return result;
   }
   catch (const std::exception& e)
   {
      std::cerr << e.what() << std::endl;
      return def_value;
   }
}

bool Project::Files::bool_cast(const std::string& value, bool def_value)
{
   std::string v = value;
   std::transform(v.begin(), v.end(), v.begin(), ::tolower);
   if (v == "true" || v == "1" || v == "yes" || v == "on") return true;
   if (v == "false" || v == "0" || v == "no" || v == "off") return false;
   return def_value;
}
