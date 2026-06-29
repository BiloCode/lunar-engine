#pragma once

#include <string>

namespace Engine::Integer
{
   int int_cast(const std::string& value, int fallback = 0);
   float float_cast(const std::string& value, float fallback = 0.f);
};
