#include "vector.h"

template<typename T>
Vector<T>::Vector(T x, T y) : sf_vector(x, y)
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

   sf_vector = sf::Vector2(
      static_cast<T>(vector.get_x()),
      static_cast<T>(vector.get_y())
   );
}

template <typename T>
T Vector<T>::get_x() const
{
   return sf_vector.x;
}

template <typename T>
T Vector<T>::get_y() const
{
   return sf_vector.y;
}

template <typename T>
void Vector<T>::set_x(T value)
{
   sf_vector.x = value;
}

template <typename T>
void Vector<T>::set_y(T value)
{
   sf_vector.y = value;
}
