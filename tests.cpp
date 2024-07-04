#include <iostream>
#include <cassert>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "ArraySequence.h"
#include "ListSequence.h"

#ifndef TESTS_H
#define TESTS_H

void testMutableArraySequence() {
    MutableArraySequence<int> seq;

    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    assert(seq.GetLength() == 3);
    assert(seq.Get(0) == 1);
    assert(seq.Get(1) == 2);
    assert(seq.Get(2) == 3);
    seq.Clear();

    seq.Prepend(0);
    assert(seq.GetLength() == 1);
    assert(seq.Get(0) == 0);
    seq.Clear();

    seq.Append(1);
    seq.Append(2);
    seq.InsertAt(4, 1);
    assert(seq.GetLength() == 3);
    assert(seq.Get(1) == 4);
    seq.Clear();

    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    seq.Append(4);
    Sequence<int>* subseq = seq.GetSubsequence(1, 3);
    assert(subseq->GetLength() == 2);
    assert(subseq->Get(0) == 2);
    assert(subseq->Get(1) == 3);
    delete subseq;
    seq.Clear();

    std::cout << "MutableArraySequence tests passed." << std::endl;
}

void testImmutableArraySequence() {
    ImmutableArraySequence<int> seq;

    Sequence<int>* seq1 = seq.Append(1);
    Sequence<int>* seq2 = seq1->Append(2);
    Sequence<int>* seq3 = seq2->Append(3);

    assert(seq.GetLength() == 0);
    assert(seq1->GetLength() == 1);
    assert(seq2->GetLength() == 2);
    assert(seq3->GetLength() == 3);

    assert(seq3->Get(0) == 1);
    assert(seq3->Get(1) == 2);
    assert(seq3->Get(2) == 3);

    Sequence<int>* seq4 = seq3->Prepend(0);
    assert(seq4->GetLength() == 4);
    assert(seq4->Get(0) == 0);

    Sequence<int>* seq5 = seq4->InsertAt(4, 2);
    assert(seq5->GetLength() == 5);
    assert(seq5->Get(2) == 4);

    Sequence<int>* subseq = seq5->GetSubsequence(1, 3);
    assert(subseq->GetLength() == 3);
    assert(subseq->Get(0) == 1);
    assert(subseq->Get(1) == 4);
    assert(subseq->Get(2) == 2);

    delete seq1;
    delete seq2;
    delete seq3;
    delete seq4;
    delete seq5;
    delete subseq;

    std::cout << "ImmutableArraySequence tests passed." << std::endl;
}

void testMutableListSequence() {
    MutableListSequence<int> seq;

    seq.Append(1);
    seq.Append(2);
    seq.Append(3);
    assert(seq.GetLength() == 3);
    assert(seq.Get(0) == 1);
    assert(seq.Get(1) == 2);
    assert(seq.Get(2) == 3);

    seq.Prepend(0);
    assert(seq.GetLength() == 4);
    assert(seq.Get(0) == 0);

    seq.InsertAt(4, 2);
    assert(seq.GetLength() == 5);
    assert(seq.Get(2) == 4);

    Sequence<int>* subseq = seq.GetSubsequence(1, 3);
    assert(subseq->GetLength() == 3);
    assert(subseq->Get(0) == 1);
    assert(subseq->Get(1) == 4);
    assert(subseq->Get(2) == 2);
    delete subseq;

    std::cout << "MutableListSequence tests passed." << std::endl;
}

void testImmutableListSequence() {
    ImmutableListSequence<int> seq;

    Sequence<int>* seq1 = seq.Append(1);
    Sequence<int>* seq2 = seq1->Append(2);
    Sequence<int>* seq3 = seq2->Append(3);

    assert(seq.GetLength() == 0);
    assert(seq1->GetLength() == 1);
    assert(seq2->GetLength() == 2);
    assert(seq3->GetLength() == 3);

    assert(seq3->Get(0) == 1);
    assert(seq3->Get(1) == 2);
    assert(seq3->Get(2) == 3);

    Sequence<int>* seq4 = seq3->Prepend(0);
    assert(seq4->GetLength() == 4);
    assert(seq4->Get(0) == 0);

    Sequence<int>* seq5 = seq4->InsertAt(4, 2);
    assert(seq5->GetLength() == 5);
    assert(seq5->Get(2) == 4);

    Sequence<int>* subseq = seq5->GetSubsequence(1, 3);
    assert(subseq->GetLength() == 3);
    assert(subseq->Get(0) == 1);
    assert(subseq->Get(1) == 4);
    assert(subseq->Get(2) == 2);

    delete seq1;
    delete seq2;
    delete seq3;
    delete seq4;
    delete seq5;
    delete subseq;

    std::cout << "ImmutableListSequence tests passed." << std::endl;
}

void runAllTests() {
    testMutableArraySequence();
    testImmutableArraySequence();
    testMutableListSequence();
    testImmutableListSequence();
    std::cout << "All tests passed successfully!" << std::endl;
}

#endif // TESTS_H