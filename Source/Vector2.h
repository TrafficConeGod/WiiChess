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

        friend Vector2<T> operator*(const Vector2<T>& vec, T scalar) {
            return Vector2<T>(vec.x * scalar, vec.y * scalar);
        }
};

typedef Vector2<int> Vector2i;
typedef Vector2<uint> Vector2u;
typedef Vector2<float> Vector2f;

#include "Vector2.inl"