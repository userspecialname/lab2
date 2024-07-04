cmake_minimum_required(VERSION 3.28)
project(laboratory2)

set(CMAKE_CXX_STANDARD 17)

add_executable(laboratory2 main.cpp
        ArraySequence.h
        DynamicArray.h
        LinkedList.h
        ListSequence.h
        Sequence.h

        ArraySequence.h
        UI.h
        UI.cpp
        tests.h
        tests.cpp)
