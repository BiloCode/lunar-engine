#pragma once

#include <SFML/Graphics.hpp>

template<typename T>
class Vector
{
   static_assert(
      std::is_same_v<T, int> ||
      std::is_same_v<T, float>,
      "Vector<T>: T must be int or float."
   );

public:
   Vector() = default;
   Vector(T x, T y);
   template<typename U> Vector(const Vector<U>& vector);
   T get_x() const;
   T get_y() const;
   void set_x(T value);
   void set_y(T value);

private:
   sf::Vector2<T> sf_vector;
};

#include "vector.tpp"
