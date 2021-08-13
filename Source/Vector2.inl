#include "Vector2.h"

template<typename T>
Vector2<T>::Vector2() : x{0}, y{0} {}

template<typename T>
Vector2<T>::Vector2(T _x, T _y) : x{_x}, y{_y} {}

template<typename T>
void Vector2<T>::operator=(const Vector2<T>& vec) {
    x = vec.x;
    y = vec.y;
}

template<typename T>
Vector2<T>::Vector2(const Vector2<T>& vec) {
    *this = vec;
}

template<typename T>
template<typename C>
Vector2<T>::operator Vector2<C>() {
    return Vector2<C>(x, y);
}