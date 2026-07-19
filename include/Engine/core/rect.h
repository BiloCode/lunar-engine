#pragma once

#include <type_traits>

template<typename T>
class Rect
{
   static_assert(
      std::is_same_v<T, int> ||
      std::is_same_v<T, float>,
      "Rect<T>: T must be int or float."
   );

public:
   Rect();
   Rect(T x, T y, T width, T height);
   T x;
   T y;
   T width;
   T height;
};

#include "rect.tpp"