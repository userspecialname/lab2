#ifndef LAB2_LISTSEQUENCE_H
#define LAB2_LISTSEQUENCE_H
#include "Sequence.h"
#include "LinkedList.h"
#include <stdexcept>


template <class T> class ListSequence : public Sequence<T>{

protected:
    LinkedList<T> *items;

public:

    ListSequence() {
        this->items = new LinkedList<T>;
    }

    ListSequence(T* items, int count) {
        this->items = new LinkedList<T>(items, count);
    }

    ListSequence(int count){
        this -> items = new LinkedList<T>(count);
    }

    virtual ~ListSequence() {
        this -> items -> Clear();
    }

    int GetLength() {
        return this->items->GetLength();
    }

//    ListSequence<T>* GetCopy(){
//        return new ListSequence<T>(*this);
//    }

    virtual void Clear() {
        delete this->items;
        this->items = new LinkedList<T>;
    }


    virtual ListSequence<T>* GetCopy() const = 0;

    Sequence<T>* Append(T item) = 0;


    Sequence<T>* Set(int index, T value) = 0;

    Sequence<T>* Prepend(T item) = 0;


    Sequence<T>* InsertAt(T item, int index) = 0;


    ListSequence(const ListSequence<T> & other) { // Конструктор копирования
        this -> items = new LinkedList<T>(*other.items);

    }

    T Get(int index) const {
        return this->items->Get(index);
    }

    T GetLast() const {
        return this->items->GetLast();
    }

    T GetFirst() const {
        return this->items->GetFirst();
    }

    void set_items(LinkedList<T>* item) {
        this -> items = item;
    }


    Sequence<T>* Concat(Sequence<T>* list) = 0;

    virtual ListSequence<T>* GetSubsequence(int startIndex, int endIndex) = 0;


};

template <class T> class MutableListSequence : public ListSequence<T>{


public:

    MutableListSequence() {
        this->items = new LinkedList<T>;
    }

    MutableListSequence(T* items, int count) {
        this->items = new LinkedList<T>(items, count);
    }

    MutableListSequence(int count){
        this -> items = new LinkedList<T>(count);
    }

    virtual ~MutableListSequence() {
        this -> items -> Clear();
    }



    ListSequence<T>* GetCopy() const{
        return new MutableListSequence<T>(*this);
    }


    Sequence<T>* Append(T item) {
        this->items->Append(item);
        return this;
    }

    T& operator[](int index) {
        if (index < 0 || index >= this->GetLength()) {
            throw std::out_of_range("Index out of range");
        }
        return this->items->Get(index);
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= this->GetLength()) {
            throw std::out_of_range("Index out of range");
        }
        return this->items->Get(index);
    }


    Sequence<T>* Prepend(T item) {
        LinkedList<T>* newItems = new LinkedList<T>();
        newItems->Append(item);

        for (int i = 0; i < this->GetLength(); i++) {
            newItems->Append(this->Get(i));
        }

        delete this->items;
        this->items = newItems;
        return this;
    }


    Sequence<T>* InsertAt(T item, int index) {
        this->items->InsertAt(item, index);
        return this;
    }

    MutableListSequence(const ListSequence<T> & other) { // Конструктор копирования
        this -> items = new LinkedList<T>(*other.items);

    }

    T Get(int index) const {
        return this->items->Get(index);
    }

    T GetLast() const{
        return this->items->GetLast();
    }

    void Clear() override {
        ListSequence<T>::Clear();
    }

    T GetFirst() const {
        return this->items->GetFirst();
    }

    int GetLength() const {
        return this->items->GetLength();
    }


    Sequence<T>* Set(int index, T value){
        this->items->Set(index, value);
        return this;
    }



    ListSequence<T>* GetSubsequence(int startIndex, int endIndex) {
        LinkedList<T>* subList = this->items->GetSubsequence(startIndex, endIndex);
        ListSequence<T>* subSequence = new MutableListSequence<T>;
        subSequence->set_items(subList);
        return subSequence;
    }

    ListSequence<T>* Concat(Sequence<T>* list){

        ListSequence<T>* seq = new MutableListSequence<T>;
        MutableListSequence<T>* other = static_cast<MutableListSequence<T>*>(list);
        seq->set_items(this->items->Concat(other -> items));
        return seq;
    }


};


template <class T> class ImmutableListSequence : public ListSequence<T>{

public:

    ImmutableListSequence() {
        this->items = new LinkedList<T>;
    }

    ImmutableListSequence(T* items, int count) {
        this->items = new LinkedList<T>(items, count);
    }

    ImmutableListSequence(int count){
        this -> items = new LinkedList<T>(count);
    }

    virtual ~ImmutableListSequence() {
        this -> items -> Clear();
    }

    int GetLength() {
        return this->items->GetLength();
    }


    ListSequence<T>* GetCopy() const{
        return new ImmutableListSequence<T>(*this);
    }

    void Clear() override {
        ListSequence<T>::Clear();
    }

    Sequence<T>* Append(T item) {
        ListSequence<T>* copy = GetCopy();
        LinkedList<T>* newItems = new LinkedList<T>();

        // Copy all existing elements
        for (int i = 0; i < copy->GetLength(); i++) {
            newItems->Append(copy->Get(i));
        }

        // Append the new item
        newItems->Append(item);

        copy->set_items(newItems);
        return copy;
    }


    Sequence<T>* Set(int index, T value) {
        ListSequence<T>* copy = GetCopy();
        LinkedList<T>* newItems = new LinkedList<T>();

        // Copy all elements to the new LinkedList
        for (int i = 0; i < copy->GetLength(); i++) {
            if (i == index) {
                newItems->Append(value);
            } else {
                newItems->Append(copy->Get(i));
            }
        }

        copy->set_items(newItems);
        return copy;
    }

    Sequence<T>* Prepend(T item) {
        ListSequence<T>* copy = GetCopy();
        LinkedList<T>* newItems = new LinkedList<T>();

        newItems->Append(item);

        for (int i = 0; i < copy->GetLength(); i++) {
            newItems->Append(copy->Get(i));
        }

        copy->set_items(newItems);
        return copy;
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= this->GetLength()) {
            throw std::out_of_range("Index out of range");
        }
        return this->items->Get(index);
    }




    Sequence<T>* InsertAt(T item, int index) {
        if (index < 0 || index > this->GetLength()) {
            throw std::out_of_range("Index out of range");
        }

        ListSequence<T>* copy = GetCopy();
        LinkedList<T>* newItems = new LinkedList<T>();

        for (int i = 0; i < copy->GetLength(); i++) {
            if (i == index) {
                newItems->Append(item);
            }
            newItems->Append(copy->Get(i));
        }

        // If inserting at the end
        if (index == copy->GetLength()) {
            newItems->Append(item);
        }

        copy->set_items(newItems);
        return copy;
    }

    ImmutableListSequence(const ListSequence<T> & other) { // Конструктор копирования
        this -> items = new LinkedList<T>(*other.items);

    }

    T Get(int index) const{
        return this->items->Get(index);
    }

    T GetLast() const {
        return this->items->GetLast();
    }

    T GetFirst() const {
        return this->items->GetFirst();
    }

    int GetLength() const {
        return this->items->GetLength();
    }



    Sequence<T>* Concat(Sequence<T>* list) {
        ListSequence<T>* copy = GetCopy();
        ListSequence<T>* other = dynamic_cast<ListSequence<T>*>(list);

        if (!other) {
            throw std::invalid_argument("Cannot concatenate with a non-ListSequence");
        }

        LinkedList<T>* newItems = new LinkedList<T>();

        // Copy elements from the first sequence
        for (int i = 0; i < copy->GetLength(); i++) {
            newItems->Append(copy->Get(i));
        }

        // Copy elements from the second sequence
        for (int i = 0; i < other->GetLength(); i++) {
            newItems->Append(other->Get(i));
        }

        ListSequence<T>* result = new ImmutableListSequence<T>();
        result->set_items(newItems);

        return result;
    }

    ListSequence<T>* GetSubsequence(int startIndex, int endIndex) {
        LinkedList<T>* subList = this->items->GetSubsequence(startIndex, endIndex);
        ListSequence<T>* subSequence = new ImmutableListSequence<T>;
        subSequence->set_items(subList);
        return subSequence;
    }


};

template<typename T>
void Print(const Sequence<T>* sequence) {
    if (!sequence) {
        std::cout << "The sequence is null." << std::endl;
        return;
    }

    int length = sequence->GetLength();

    std::cout << "[";
    for (int i = 0; i < length; ++i) {
        std::cout << sequence->Get(i);
        if (i < length - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "]" << std::endl;
}

#endif //LAB2_LISTSEQUENCE_H
