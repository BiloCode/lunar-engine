#include <Engine/utils/boolean.h>
#include <algorithm>

bool Engine::Boolean::bool_cast(const std::string& value, bool fallback)
{
   std::string v = value;
   std::transform(v.begin(), v.end(), v.begin(), ::tolower);
   if (v == "true" || v == "1" || v == "yes" || v == "on") return true;
   if (v == "false" || v == "0" || v == "no" || v == "off") return false;
   return fallback;
}
