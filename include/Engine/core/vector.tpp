#include "vector.h"

template<typename T>
Vector<T>::Vector() : x(0), y(0)
{
}

template<typename T>
Vector<T>::Vector(T x, T y) : x(x), y(y)
{
}

template <typename T>
template <typename U>
Vector<T>::Vector(const Vector<U>& vector)
{
   static_assert(
      std::is_same_v<U, int> ||
      std::is_same_v<U, float>,
      "Vector<U>: U must be int or float."
   );

   x = static_cast<T>(vector.x);
   y = static_cast<T>(vector.y);
}