#ifndef LAB2_ARRAYSEQUENCE_H
#define LAB2_ARRAYSEQUENCE_H
#include "DynamicArray.h"
#include "Sequence.h"
#include <stdexcept>


template <class T> class ArraySequence : public Sequence<T> {

protected:
    DynamicArray<T> *items;
    int size;
    int capacity;

public:
    ArraySequence() {
        this->items = new DynamicArray<T>;
        if (this->items == nullptr) {
            throw std::bad_alloc();
        }
        size = 0;
        capacity = 1;
    }

    ArraySequence(T *items, int count) {
        this->items = new DynamicArray<T>(items, count);
        if (this->items == nullptr) {
            throw std::bad_alloc();
        }
        size = count;
        capacity = this->items->GetSize();
    }

    virtual void Clear() {
        delete this->items;
        this->items = new DynamicArray<T>;
        this->size = 0;
        this->capacity = 1;
    }

    ArraySequence(int size) {
        this->items = new DynamicArray<T>(size);
        if (this->items == nullptr) {
            throw std::bad_alloc();
        }
        this->size = size;
        capacity = size;
    }

    ArraySequence(const ArraySequence<T> &other) {
        this->items = new DynamicArray<T>(*other.items);
        if (this->items == nullptr) {
            throw std::bad_alloc();
        }
        size = other.size;
        capacity = other.capacity;
    }

    Sequence<T> *Set(int index, T value) = 0;

    Sequence<T> *Append(T item) = 0;

    Sequence<T> *Prepend(T item) = 0;

    Sequence<T> *InsertAt(T item, int index) = 0;

    virtual ~ArraySequence() {
        if (this->items != nullptr)
            delete this->items;
    }


    int GetLength() const {
        return size;
    }

    T Get(int index) const{
        if (index < 0 || index > size) {
            throw std::out_of_range("Invalid index");
        }
        return this->items->Get(index);
    }

    T GetLast() const {
        if (size == 0) {
            throw std::out_of_range("Sequence is empty");
        }
        return this->items->Get(size - 1);
    }

    T GetFirst() const {
        if (size == 0) {
            throw std::out_of_range("Sequence is empty");
        }
        return this->items->Get(0);
    }

    void set_items(DynamicArray<T>* item) {
        if (this->items != nullptr) {
            delete this->items;
        }
        this->items = item;
        this->size = item->GetSize();
        this->capacity = item->GetSize();
    }

    virtual ArraySequence<T> *GetCopy() const = 0;

    Sequence<T> *GetSubsequence(int startIndex, int endIndex) = 0;

    T operator[](int i) const {
        return (*this -> items)[i];
    }

    T & operator[](int i) {
        return (*this -> items)[i];
    }


    Sequence<T> *Concat(Sequence<T> *list) {
        ArraySequence<T> *other = dynamic_cast<ArraySequence<T> *>(list);
        if (other == nullptr) {
            throw std::invalid_argument("Invalid sequence type");
        }
        int newSize = size + other->size;
        if (newSize > capacity) {
            while (newSize > capacity) {
                capacity *= 2;
            }
            items->Resize(capacity);
        }
        for (int i = 0; i < other->size; i++) {
            items->Set(size + i, other->items->Get(i));
        }
        size = newSize;
        return this;
    }


};

template <class T>
class MutableArraySequence: public ArraySequence<T> {
public:
    MutableArraySequence() : ArraySequence<T>() {}

    MutableArraySequence(T *items, int count) : ArraySequence<T>(items, count) {}

    MutableArraySequence(int size) : ArraySequence<T>(size) {}

    MutableArraySequence(const ArraySequence<T> &other) : ArraySequence<T>(other) {}


    ArraySequence<T> *Set(int index, T value) {
        if (index < 0 || index >= this -> size) {
            throw std::out_of_range("Invalid index");
        }
        this->items->Set(index, value);
        return this;
    }

    ArraySequence<T> *GetSubsequence(int startIndex, int endIndex) {
        if (startIndex < 0 || startIndex >= this -> size || endIndex < 0 || endIndex >= this-> size || startIndex > endIndex) {
            throw std::out_of_range("Invalid index range");
        }


        ArraySequence<T> *subArray = new MutableArraySequence<T>;

        for (int i = startIndex; i < endIndex; i++) {
            subArray ->Append((*this -> items)[i]);
        }
//        ArraySequence<T> *result = new MutableArraySequence<T>(subArray->Get_data(), endIndex - startIndex + 1);
        return subArray;
    }

    void Clear() override {
        ArraySequence<T>::Clear();
    }

    ArraySequence<T> *Append(T item) {
        if (this -> size >= this ->capacity) {
            this -> items->Resize(this ->capacity * 2);
            this -> capacity *= 2;
        }
        this -> items->Set(this -> size, item);
        this -> size++;
        return this;
    }

    ArraySequence<T> *Prepend(T item) {
        if (this->size >= this->capacity) {
            this->items->Resize(this->capacity * 2);
            this->capacity *= 2;
        }
        for (int i = this->size; i > 0; i--) {
            (*this)[i] = (*this)[i - 1];
        }
        (*this)[0] = item;
        this->size++;
        return this;
    }

    ArraySequence<T> *InsertAt(T item, int index) {
        if (index < 0 || index > this -> size) {
            throw std::out_of_range("Invalid index");
        }
        if (this -> size >= this -> capacity) {
            this -> items->Resize(this -> capacity * 2);
            this -> capacity *= 2;
        }
        for (int i = this -> size; i > index; i--) {
            this -> items->Set(i, this -> items->Get(i - 1));
        }
        this -> items->Set(index, item);
        this -> size++;
        return this;
    }

    ArraySequence<T> *Concat(Sequence<T> *list) {
        ArraySequence<T> *other = dynamic_cast<ArraySequence<T> *>(list);
        if (other == nullptr) {
            throw std::invalid_argument("Invalid sequence type");
        }
        int newSize = this -> size + other-> GetLength();
        if (newSize > this -> capacity) {
            while (newSize >this ->  capacity) {
                this -> capacity *= 2;
            }
            this -> items->Resize(this -> capacity);
        }
        for (int i = 0; i < other-> GetLength(); i++) {
            this -> items->Set(this -> size + i, (*other)[i]);
        }
        this -> size = newSize;
        return this;
    }

    ArraySequence<T>* GetCopy() const {
        return new MutableArraySequence<T>(*this);
    }

    T operator[](int i) const {
        return (*this -> items)[i];
    }

    T & operator[](int i) {
        return (*this -> items)[i];
    }


};



template <class T>
class ImmutableArraySequence: public ArraySequence<T> {
public:
    ImmutableArraySequence() : ArraySequence<T>() {}

    ImmutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}

    ImmutableArraySequence(int size) : ArraySequence<T>(size) {}

    ImmutableArraySequence(const ArraySequence<T>& other) : ArraySequence<T>(other) {}

    ArraySequence<T>* GetSubsequence(int startIndex, int endIndex) override {
        if (startIndex < 0 || startIndex >= this->GetLength() || endIndex < 0 || endIndex >= this->GetLength() || startIndex > endIndex) {
            throw std::out_of_range("Invalid index range");
        }
        T* subItems = new T[endIndex - startIndex + 1];
        for (int i = startIndex; i <= endIndex; i++) {
            subItems[i - startIndex] = this->Get(i);
        }
        ArraySequence<T>* result = new ImmutableArraySequence<T>(subItems, endIndex - startIndex + 1);
        delete[] subItems;
        return result;
    }

    ArraySequence<T>* Set(int index, T value) override {
        if (index < 0 || index >= this->GetLength()) {
            throw std::out_of_range("Invalid index");
        }
        ArraySequence<T>* copy = this->GetCopy();
        DynamicArray<T>* newItems = new DynamicArray<T>(*(this->items));
        newItems->Set(index, value);
        copy->set_items(newItems);
        return copy;
    }

    void Clear() override {
        ArraySequence<T>::Clear();
    }

    ArraySequence<T>* Append(T item) override {

        ArraySequence<T>* copy = this->GetCopy();
        DynamicArray<T>* newItems = new DynamicArray<T>(this->GetLength() + 1);

        for (int i = 0; i < this->GetLength(); i++) {
            newItems->Set(i, this->Get(i));
        }
        newItems->Set(this->GetLength(), item);

        copy->set_items(newItems);

        return copy;
    }

    ArraySequence<T>* Prepend(T item) override {
        ArraySequence<T>* copy = this->GetCopy();
        DynamicArray<T>* newItems = new DynamicArray<T>(this->GetLength() + 1);

        (*newItems)[0] = item;
        for (int i = 0; i < this->GetLength(); i++) {
            (*newItems)[i + 1] = (*this)[i];
        }

        copy->set_items(newItems);
        return copy;
    }


    ArraySequence<T>* InsertAt(T item, int index) override {
        if (index < 0 || index > this->GetLength()) {
            throw std::out_of_range("Invalid index");
        }
        ArraySequence<T>* copy = this->GetCopy();
        DynamicArray<T>* newItems = new DynamicArray<T>(this->GetLength() + 1);
        for (int i = 0; i < index; i++) {
            newItems->Set(i, this->Get(i));
        }
        newItems->Set(index, item);
        for (int i = index; i < this->GetLength(); i++) {
            newItems->Set(i + 1, this->Get(i));
        }
        copy->set_items(newItems);
        return copy;
    }


    ArraySequence<T>* GetCopy() const {
        return new ImmutableArraySequence<T>(*this);
    }

    ArraySequence<T>* Concat(Sequence<T>* list) override {
        ArraySequence<T>* other = dynamic_cast<ArraySequence<T>*>(list);
        if (other == nullptr) {
            throw std::invalid_argument("Invalid sequence type");
        }

        ArraySequence<T>* copy = this->GetCopy();
        DynamicArray<T>* newItems = new DynamicArray<T>(this->GetLength() + other->GetLength());

        // Copy items from this sequence
        for (int i = 0; i < this->GetLength(); i++) {
            newItems->Set(i, this->Get(i));
        }

        // Copy items from the other sequence
        for (int i = 0; i < other->GetLength(); i++) {
            newItems->Set(this->GetLength() + i, other->Get(i));
        }

        copy->set_items(newItems);
        return copy;
    }

    T operator[](int i) const {
        return (*this -> items)[i];
    }

    T & operator[](int i) {
        return (*this -> items)[i];
    }


};


#endif // LAB2_ARRAYSEQUENCE_H