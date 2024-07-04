#pragma once

using namespace std;

template <class T> class Sequence {
public:
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;

    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;

    virtual int GetLength() const = 0;

    virtual Sequence<T>* Set(int index, T data) = 0;

    virtual Sequence<T>* Append(T item) = 0;
    virtual Sequence<T>* Prepend(T item) = 0;

    virtual Sequence<T>* InsertAt(T item, int index) = 0;

    virtual Sequence <T>* Concat(Sequence <T>* list) = 0;

    virtual Sequence<T>* GetCopy() const = 0;

};





