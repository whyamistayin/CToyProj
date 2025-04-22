cmake_minimum_required(VERSION 3.29)
project(SemesterProject)

set(CMAKE_CXX_STANDARD 23)

set(SOURCE_FILES
        Node_Class.h
        myArray_class.h
)

set(TEST_FILES
        Node_test.cpp
        myArray_test.cpp
)

set(GTEST_SOURCE_FILES
        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc
        MolecularArray.h
        MolecularArray_tests.cpp
)

add_executable(SemesterProjectTests ${SOURCE_FILES} ${TEST_FILES} ${GTEST_SOURCE_FILES})
target_include_directories(SemesterProjectTests PRIVATE GoogleTest)
target_compile_features(SemesterProjectTests PRIVATE cxx_std_23)
