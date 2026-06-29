#include <Engine/utils/integer.h>
#include <iostream>

int Engine::Integer::int_cast(const std::string& value, int fallback)
{
   try {
      size_t idx;
      int result = std::stoi(value, &idx);
      if (idx != value.size()) {
         return fallback;
      }
      return result;
   }
   catch (const std::exception& e)
   {
      std::cerr << e.what() << std::endl;
      return fallback;
   }
}

float Engine::Integer::float_cast(const std::string& value, float fallback)
{
   try {
      size_t idx;
      float result = std::stof(value, &idx);
      if (idx != value.size()) {
         return fallback;
      }
      return result;
   }
   catch (const std::exception& e)
   {
      std::cerr << e.what() << std::endl;
      return fallback;
   }
}
