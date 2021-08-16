#include "Wii/io.h"
#include "Array.h"

template<typename T>
Array<T>::Array() {}

// template<typename T>
// void Array<T>::operator=(const Array<T>& arr) {

// }

// template<typename T>
// Array<T>::Array(const Array<T>& arr) {}

template<typename T>
Array<T>::~Array() {
    if (buf != nullptr) {
        free(buf);
    }
}

template<typename T>
void Array<T>::Load(DataStream& stream) {
    stream >> size;
    buf = (T*)malloc(size * sizeof(T));
    for (size_t i = 0; i < size; i++) {
        T val;
        stream >> val;
        buf[i] = val;
    }
}

template<typename T>
T& Array<T>::operator[](size_t index) {
    #ifdef DEBUG_MODE
    if (index >= size) {
        PrintFmt("Attempt to index %d out of size of %d", index, size);
        Error("Out of array bounds");
        exit(0);
    }
    #endif
    return buf[index];
}

template<typename T>
Array<T>& Array<T>::operator<<(const T& val) {
    size += 1;
    buf = (T*)realloc(buf, size * sizeof(T));
    buf[size - 1] = val;
    return *this;
}

template<typename T>
Array<T>& Array<T>::operator>>(T& val) {
    size -= 1;
    val = buf[size];
    buf = (T*)realloc(buf, size * sizeof(T));
    return *this;
}