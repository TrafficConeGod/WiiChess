#pragma once
#include "Wii/type.h"

template<typename T>
class Vector2 {
    public:
        T x;
        T y;

        Vector2();
        Vector2(T x, T y);

        void operator=(const Vector2<T>& vec);
        Vector2(const Vector2<T>& vec);

        template<typename C>
        operator Vector2<C>();

        friend Vector2<T> operator+(const Vector2<T>& vec, const Vector2<T>& vec2) {
            return Vector2<T>(vec.x + vec2.x, vec.y + vec2.y);
        }

        Vector2<T> operator+=(const Vector2<T>& val) {
            *this = *this + val;
            return *this;
        }

        friend Vector2<T> operator-(const Vector2<T>& vec, const Vector2<T>& vec2) {
            return Vector2<T>(vec.x - vec2.x, vec.y - vec2.y);
        }

        Vector2<T> operator-=(const Vector2<T>& val) {
            *this = *this - val;
            return *this;
        }

        friend Vector2<T> operator*(const Vector2<T>& vec, T scalar) {
            return Vector2<T>(vec.x * scalar, vec.y * scalar);
        }

        friend Vector2<T> operator*(const Vector2<T>& vec, const Vector2<T>& vec2) {
            return Vector2<T>(vec.x * vec2.x, vec.y * vec2.y);
        }

        template<typename C>
        Vector2<T> operator*=(const C& val) {
            *this = *this * val;
            return *this;
        }
    
        friend Vector2<T> operator/(const Vector2<T>& vec, T scalar) {
            return Vector2<T>(vec.x / scalar, vec.y / scalar);
        }

        friend Vector2<T> operator/(const Vector2<T>& vec, const Vector2<T>& vec2) {
            return Vector2<T>(vec.x / vec2.x, vec.y / vec2.y);
        }

        template<typename C>
        Vector2<T>& operator/=(const C& val) {
            *this = *this / val;
            return *this;
        }

        friend bool operator==(const Vector2<T>& vec, const Vector2<T>& vec2) {
            return vec.x == vec2.x && vec.y == vec2.y;
        }
};

typedef Vector2<int> Vector2i;
typedef Vector2<uint> Vector2u;
typedef Vector2<float> Vector2f;

#include "Vector2.inl"