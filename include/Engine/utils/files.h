#pragma once

#include <string>
#include <vector>

namespace Engine::Files
{
   std::string str_trim(const std::string& value);
   int int_cast(const std::string& value, int def_value = 0);
   bool bool_cast(const std::string& value, bool def_value = false);
}
