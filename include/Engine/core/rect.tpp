#include "rect.h"

template<typename T>
Rect<T>::Rect() : x(0), y(0), width(0), height(0)
{
}

template<typename T>
Rect<T>::Rect(T x, T y, T width, T height) : x(x), y(y), width(width), height(height)
{
}