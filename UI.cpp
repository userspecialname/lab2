#include "UI.h"
#include <iostream>
#include <string>
#include "Sequence.h"
#include "ListSequence.h"
#include "ArraySequence.h"
#include "tests.h"

using namespace std;

void displayUI() {
    cout << endl << "________________________________________________________________________________" << endl;
    cout << "1. Выберите тип данных." << endl;
    cout << "2. Выберите структуру данных." << endl;
    cout << "3. Тесты программы." << endl;
    cout << "4. Выйти." << endl;
    cout << "________________________________________________________________________________" << endl;
}

void structure_UI() {
    cout << endl << "________________________________________________________________________________" << endl;
    cout << "1. Mutable Array Sequence." << endl;
    cout << "2. Immutable Array Sequence." << endl;
    cout << "3. Mutable List Sequence." << endl;
    cout << "4. Immutable List Sequence." << endl;
    cout << "5. Назад." << endl;
    cout << "________________________________________________________________________________" << endl;
}

void operations_UI() {
    cout << endl << "________________________________________________________________________________" << endl;
    cout << "________________________________Создание объекта________________________________" << endl;
    cout << "1. Копировать элементы из массива." << endl;
    cout << "2. Создать последовательность заданной длины." << endl;
    cout << "3. Получить элемент по индексу." << endl;
    cout << "4. Получить первый элемент." << endl;
    cout << "5. Получить последний элемент." << endl;
    cout << "6. Получить подпоследовательность." << endl;
    cout << "7. Получить длину последовательности." << endl;
    cout << "____________________________________Операции____________________________________" << endl;
    cout << "8. Задать элемент по индексу." << endl;
    cout << "9. Добавить элемент в конец." << endl;
    cout << "10. Добавить элемент в начало." << endl;
    cout << "11. Вставить элемент в заданную позицию." << endl;
    cout << "12. Конкатенация двух последовательностей." << endl;
    cout << "13. Вывести последовательность." << endl;
    cout << "14. Выйти." << endl;
    cout << "________________________________________________________________________________" << endl;
}

void T_UI(){
    cout << endl << "________________________________________________________________________________" << endl;
    cout << "_________________________________Тесты структур_________________________________" << endl;
    cout << "1. Mutable Array Sequence." << endl;
    cout << "2. Immutable Array Sequence." << endl;
    cout << "3. Mutable List Sequence." << endl;
    cout << "4. Immutable List Sequence." << endl;
    cout << "5. Выйти." << endl;
    cout << "________________________________________________________________________________" << endl;
}

int input(int min, int max) {
    int answer;
    cin >> answer;
    while (answer < min || answer > max) {
        cout << "Ошибка. Введите число от " << min << " до " << max << endl;
        cin >> answer;
    }
    return answer;
}

template<typename T>
void performOperation(Sequence<T>*& sequence, Sequence<T>*& concat, int operation) {
    switch (operation) {
        case 1: {
            int size;
            cout << "Введите размер массива: ";
            cin >> size;
            T* temp = new T[size];
            cout << "Введите элементы массива: ";
            for (int i = 0; i < size; i++)
                cin >> temp[i];
            delete sequence;
            sequence = new MutableArraySequence<T>(temp, size);
            delete[] temp;
            break;
        }
        case 2: {
            int size;
            cout << "Введите размер последовательности: ";
            cin >> size;
            delete sequence;
            sequence = new MutableArraySequence<T>(size);
            break;
        }
        case 3: {
            int index;
            cout << "Введите индекс: ";
            cin >> index;
            cout << sequence->Get(index) << endl;
            break;
        }
        case 4:
            cout << sequence->GetFirst() << endl;
            break;
        case 5:
            cout << sequence->GetLast() << endl;
            break;
        case 6: {
            int start, end;
            cout << "Введите начальный и конечный индексы: ";
            cin >> start >> end;
            Sequence<T>* subseq = sequence->GetSubsequence(start, end);
            Print(subseq);
            delete subseq;
            break;
        }
        case 7:
            cout << "Длина последовательности: " << sequence->GetLength() << endl;
            break;

        case 8: {
            int index;
            T value;
            cout << "Введите индекс и значение: ";
            cin >> index >> value;

            MutableArraySequence<T>* mutableArraySeq = dynamic_cast<MutableArraySequence<T>*>(sequence);
            MutableListSequence<T>* mutableListSeq = dynamic_cast<MutableListSequence<T>*>(sequence);

            if (mutableArraySeq) {
                (*mutableArraySeq)[index] = value;
            } else if (mutableListSeq) {
                (*mutableListSeq)[index] = value;
            } else {
                sequence = sequence->Set(index, value);
            }
            break;
        }
        case 9: {
            T item;
            cout << "Введите элемент: ";
            cin >> item;
            sequence = static_cast<Sequence<T>*>(sequence->Append(item));
            break;
        }
        case 10: {
            T item;
            cout << "Введите элемент: ";
            cin >> item;
            sequence = static_cast<Sequence<T>*>(sequence->Prepend(item));
            break;
        }
        case 11: {
            int index;
            T item;
            cout << "Введите индекс и элемент: ";
            cin >> index >> item;
            sequence = static_cast<Sequence<T>*>(sequence->InsertAt(item, index));
            break;
        }
        case 12: {
            int size;
            cout << "Введите размер второй последовательности: ";
            cin >> size;
            T* temp = new T[size];
            cout << "Введите элементы второй последовательности: ";
            for (int i = 0; i < size; i++)
                cin >> temp[i];
            delete concat;
            concat = new MutableArraySequence<T>(temp, size);
            delete[] temp;
            sequence = static_cast<Sequence<T>*>(sequence->Concat(concat));
            break;
        }
        case 13:
            Print(sequence);
            break;
    }
}

void runTests(int testType) {
    switch (testType) {
        case 1:
            testMutableArraySequence();
            break;
        case 2:
            testImmutableArraySequence();
            break;
        case 3:
            testMutableListSequence();
            break;
        case 4:
            testImmutableListSequence();
            break;
    }
}

void your_choice() {
    Sequence<int>* sequence_int = nullptr;
    Sequence<double>* sequence_double = nullptr;
    Sequence<string>* sequence_string = nullptr;

    Sequence<int>* concat_int = nullptr;
    Sequence<double>* concat_double = nullptr;
    Sequence<string>* concat_string = nullptr;

    int type = 0, choice_type_struct, choice_struct;

    while (true) {
        displayUI();
        choice_type_struct = input(1, 4);

        if (choice_type_struct == 1) {
            cout << endl << "________________________________________________________________________________" << endl;
            cout << "1. Целые числа." << endl;
            cout << "2. Вещественные числа." << endl;
            cout << "3. Строки." << endl;
            cout << "________________________________________________________________________________" << endl;

            type = input(1, 3);

        } else if (choice_type_struct == 2) {
            structure_UI();
            choice_struct = input(1, 5);

            if (choice_struct != 5) {
                if (type == 1) {
                    switch(choice_struct) {
                        case 1: sequence_int = new MutableArraySequence<int>(); break;
                        case 2: sequence_int = new ImmutableArraySequence<int>(); break;
                        case 3: sequence_int = new MutableListSequence<int>(); break;
                        case 4: sequence_int = new ImmutableListSequence<int>(); break;
                    }
                    concat_int = sequence_int->GetCopy();
                } else if (type == 2) {
                    switch(choice_struct) {
                        case 1: sequence_double = new MutableArraySequence<double>(); break;
                        case 2: sequence_double = new ImmutableArraySequence<double>(); break;
                        case 3: sequence_double = new MutableListSequence<double>(); break;
                        case 4: sequence_double = new ImmutableListSequence<double>(); break;
                    }
                    concat_double = sequence_double->GetCopy();
                } else if (type == 3) {
                    switch(choice_struct) {
                        case 1: sequence_string = new MutableArraySequence<string>(); break;
                        case 2: sequence_string = new ImmutableArraySequence<string>(); break;
                        case 3: sequence_string = new MutableListSequence<string>(); break;
                        case 4: sequence_string = new ImmutableListSequence<string>(); break;
                    }
                    concat_string = sequence_string->GetCopy();
                }

                while (true) {
                    operations_UI();
                    int operation = input(1, 14);

                    if (operation == 14) break;

                    if (type == 1) {
                        performOperation(sequence_int, concat_int, operation);
                    } else if (type == 2) {
                        performOperation(sequence_double, concat_double, operation);
                    } else if (type == 3) {
                        performOperation(sequence_string, concat_string, operation);
                    }
                }
            }
        } else if (choice_type_struct == 3) {
            while (true) {
                T_UI();
                int tests = input(1, 5);
                if (tests == 5) break;
                runTests(tests);
            }
        } else if (choice_type_struct == 4) {
            break;
        }
    }

    // Clean up
    delete sequence_int;
    delete sequence_double;
    delete sequence_string;
    delete concat_int;
    delete concat_double;
    delete concat_string;
}

