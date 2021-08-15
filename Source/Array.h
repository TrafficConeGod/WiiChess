#pragma once
#include "Wii/io.h"

template<typename T>
class Array {
    public:
        T* buf = nullptr;
        size_t size = 0;

        Array();
        void operator=(const Array<T>& arr);
        Array(const Array<T>& arr);
        ~Array();

        T& operator[](size_t index);

        Array& operator<<(const T& val);
        Array& operator>>(T& val);
};

#include "Array.inl"