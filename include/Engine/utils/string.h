#pragma once

#include <string>

namespace Engine::String
{
   std::string trim(const std::string& value);
   std::string snake_case(std::string s);
   std::string format_object(std::initializer_list<std::pair<std::string, std::string>> fields);
}
