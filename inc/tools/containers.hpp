#pragma once
#include <list>


// This class is intended to encapsulate dynamic memory management.
// The most important thing it does it deleting[] the dynamic array and thus preventing memory leaks.
// It should be used like this:
// > ArrayKeeper<float> foo(42);
// > float* bar = foo.getArray();
// [ do smth with items of bar ]
// ???
// Profit! When foo is destroyed, bar is automatically deleted
template <typename T>
class ArrayKeeper {
private:
    T* array;
public:
    ArrayKeeper(int size);
    ~ArrayKeeper();
    T* getArray();
};

template <typename T>
ArrayKeeper<T>::ArrayKeeper(int size) {
    array = new T[size];
}

template <typename T>
ArrayKeeper<T>::~ArrayKeeper() {
    delete[] array;
}

template <typename T>
T* ArrayKeeper<T>::getArray() {
    return array;
}


// A 2-dimmensional equivalent of ArrayKeeper
template <typename T>
class Array2DKeeper {
private:
    T** array;
    int size1, size2;
public:
    Array2DKeeper(int size1, int size2)
    {
        array = new T*[size1];
        for(int i=0;i<size1;i++) array[i] = new T[size2];
        this->size1 = size1;
        this->size2 = size2;
    }

    ~Array2DKeeper();
    T** getArray2D();
};

template <typename T>
Array2DKeeper<T>::~Array2DKeeper() {
        for(int i=0;i<size1;i++) delete[] array[i];
        delete[] array;
}

template <typename T>
T** Array2DKeeper<T>::getArray2D() {
    return array;
}

template <typename A, typename B>
struct pair { // nuff said
public:
    A a;
    B b;
    pair(){}
    pair(A _a, B _b) {
        a = _a;
        b = _b;
    }

    pair<float, float> scale(float len) {
        float length = hypot(a, b);
        if (length == 0) return pair<float, float>(0, 0);
        else return pair<float, float>(a * len / length, b * len / length);
    }
};