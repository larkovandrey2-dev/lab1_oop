cmake_minimum_required(VERSION 3.16)

project(lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(array_ops
    src/array_ops.cpp
)

target_include_directories(array_ops
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(array_ops
    PRIVATE
    -Wall
    -Wextra
    -pedantic
)

add_executable(lab1
    main.cpp
)

target_link_libraries(lab1
    PRIVATE
    array_ops
)

target_compile_options(lab1
    PRIVATE
    -Wall
    -Wextra
    -pedantic
)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(lab1_tests
    tests/test_array.cpp
)

target_link_libraries(lab1_tests
    PRIVATE
    array_ops
    GTest::gtest_main
)

target_compile_options(lab1_tests
    PRIVATE
    -Wall
    -Wextra
    -pedantic
)

include(GoogleTest)

gtest_discover_tests(lab1_tests)