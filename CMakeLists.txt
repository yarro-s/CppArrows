cmake_minimum_required(VERSION 3.6)
project(CppArrows)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3 -Wall -pedantic -std=c++14")

set(SOURCE_DIR lib/cpp_arrows)
set(RELEASE_DIR release/${PROJECT_NAME})
include_directories(lib tests/lib ${SOURCE_DIR} ${RELEASE_DIR} tests release)

set(SOURCE_FILES lib/cpp_arrows/arrow_base.h tests/tests_main.cpp
        tests/arrow_base/make_apply_test.cpp tests/arrow_base/compose_test.cpp
        tests/lib/arrow_base_test_helpers.h tests/arrow_base/partial_application_test.cpp
        tests/arrow_base/make_arrow_base.h lib/cpp_arrows/arrow.h lib/cpp_arrows/make_arrow.h
        tests/arrow/make_arrow_test.cpp tests/arrow_test_helpers.h tests/arrow/apply_and_convert_test.cpp
        tests/arrow/arrow_composition_test.cpp tests/arrow/partial_apply_test.cpp tests/examples/basic_usage.cpp tests/examples/getting_started_example.cpp)


set(LIB_RELEASE_NAME cpp_arrows1.hpp)

execute_process(COMMAND "cat ${SOURCE_DIR}/* > ${RELEASE_DIR}/${LIB_RELEASE_NAME}")

add_executable(CppArrows ${SOURCE_FILES})