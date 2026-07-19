#include <Engine/utils/string.h>

#include <cctype>
#include <sstream>
#include <algorithm>

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

std::string Engine::String::format_object(std::initializer_list<std::pair<std::string, std::string>> fields)
{
   return format_object("", fields);
}

std::string Engine::String::format_object(const std::string& prefix, std::initializer_list<std::pair<std::string, std::string>> fields)
{
   std::ostringstream stream;
   stream << prefix << "{ ";
   for (auto it = fields.begin(); it != fields.end(); ++it) {
      if (it != fields.begin()) {
         stream << ", ";
      }
      stream << it->first << ": " << it->second;
   }
   stream << " }";
   return stream.str();
}
