#pragma once

#include <type_traits>

template<typename T>
class Vector
{
   static_assert(
      std::is_same_v<T, int> ||
      std::is_same_v<T, float>,
      "Vector<T>: T must be int or float."
   );

public:
   Vector();
   Vector(T x, T y);
   template<typename U> Vector(const Vector<U>& vector);
   T x;
   T y;
};

#include "vector.tpp"
