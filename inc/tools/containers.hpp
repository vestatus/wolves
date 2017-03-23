#pragma once

template <typename T>
class ArrayKeeper {
private:
    T* array;
public:
    ArrayKeeper(int size);
    ~ArrayKeeper();
    T* getArray();
};

#pragma once

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