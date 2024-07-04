#pragma once

#include <stdexcept>

template<class T>
class DynamicArray {
private:
    T* data;
    int size;

public:

    //2. Определение - Template, следовательно тип может быть произвольный, мы можем подставить тип у которого нет конструктора по умолчанию, new вызывает конструктор по умолчанию, использование malloc будет предпочтительнее;
    DynamicArray() : data(nullptr), size(0) {}

    DynamicArray(T* items, int count) {
        size = count;
        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = items[i];
        }
    }

    DynamicArray(int size) {
        if (size < 0) {
            throw std::invalid_argument("Size cannot be negative");
        }
        this->size = size;
        data = (T*)malloc(sizeof(T) * size);
    }

    DynamicArray(const DynamicArray<T>& dynamicArray) {
        size = dynamicArray.size;
        data = (T*)malloc(sizeof(T) * size);
        for (int i = 0; i < size; i++) {
            data[i] = dynamicArray.data[i];
        }
    }

    ~DynamicArray() {
        delete[] data;
    }

    DynamicArray<T>* GetSubsequence(int startIndex, int endIndex) {
        if (data == nullptr) {
            throw std::logic_error("Source array is null");
        }

        int size = GetSize();

        if (startIndex < 0 || startIndex >= size ||
            endIndex < 0 || endIndex >= size ||
            startIndex > endIndex) {
            throw std::out_of_range("Invalid index range");
        }

        int subSize = endIndex - startIndex + 1;
        T* subData = new T[subSize];

        for (int i = 0; i < subSize; i++) {
            subData[i] = Get(startIndex + i);
        }

        DynamicArray<T>* subSequence = new DynamicArray<T>(subData, subSize);
        delete[] subData;

        return subSequence;
    }

    DynamicArray<T>* Concat(DynamicArray<T>* list) {
        int newSize = size + list->GetSize();
        DynamicArray<T>* result = new DynamicArray<T>(newSize);

        for (int i = 0; i < size; i++) {
            result->Set(i, data[i]);
        }

        for (int i = 0; i < list->GetSize(); i++) {
            result->Set(size + i, list->Get(i));
        }

        return result;
    }

    T Get(int index) const {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }

        return data[index];
    }

    T GetFirst() const {
        if (size == 0) {
            throw std::out_of_range("Array is empty");
        }

        return data[0];
    }

    T GetLast() const {
        if (size == 0) {
            throw std::out_of_range("Array is empty");
        }

        return data[size - 1];
    }


    int GetSize() const {
        return size;
    }

    void Set(int index, T value) {
        if (index < 0){
            throw std::out_of_range("");
        }

        Resize(index + 1);
        data[index] = value;
    }

    void Resize(int newSize) {
        if (newSize < 0) {
            throw std::invalid_argument("New size cannot be negative");
        }

        if (newSize > size) {
            T* oldData = data;
            data = new T[newSize];

            for (int i = 0; i < size; i++) {
                data[i] = oldData[i];
            }

            delete[] oldData;
        }

        size = newSize;
    }



    DynamicArray& operator=(const DynamicArray& other) {
        if (&other != this) {
            size = other.size;
            delete[] data;
            data = new T[size];

            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }

        return *this;
    }

    T operator[](int i) const {
        return data[i];
    }

    T & operator[](int i) {
        return data[i];
    }



};
