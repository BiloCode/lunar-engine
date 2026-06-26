#include <Engine/utils/strings.h>
#include <algorithm>
#include <cctype>

std::string Project::Strings::to_snake_case(std::string s)
{
   std::transform(s.begin(), s.end(), s.begin(),
      [](unsigned char c) { return std::tolower(c); });
   std::replace(s.begin(), s.end(), ' ', '_');
   return s;
}
