#include <Engine/utils/string.h>
#include <algorithm>
#include <cctype>

std::string Engine::String::trim(const std::string& value)
{
   auto is_space = [](unsigned char c) {
      return std::isspace(c);
   };
   auto start = std::find_if_not(value.begin(), value.end(), is_space);
   if (start == value.end()) return "";
   auto end = std::find_if_not(value.rbegin(), value.rend(), is_space).base();
   return std::string(start, end);
}

std::string Engine::String::snake_case(std::string s)
{
   std::transform(s.begin(), s.end(), s.begin(),
      [](unsigned char c) { return std::tolower(c); });
   std::replace(s.begin(), s.end(), ' ', '_');
   return s;
}
