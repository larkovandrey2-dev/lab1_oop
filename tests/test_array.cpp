#include "array_ops.h"

#include <gtest/gtest.h>

TEST(Array, Create) {
    int* arr = array_create(3);

    ASSERT_NE(arr, nullptr);

    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);

    array_delete(arr);
    EXPECT_EQ(arr, nullptr);
}

TEST(Array, ResizeUp) {
    int* arr = array_create(3);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    arr = array_resize(arr, 3, 5);

    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
    EXPECT_EQ(arr[3], 0);
    EXPECT_EQ(arr[4], 0);

    array_delete(arr);
}

TEST(Array, ResizeDown) {
    int* arr = array_create(5);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;

    arr = array_resize(arr, 5, 3);

    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);

    array_delete(arr);
}

TEST(Array, Insert) {
    std::size_t size = 3;
    int* arr = array_create(size);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    arr = array_insert(arr, size, 1, 99);

    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(size, 4u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 99);
    EXPECT_EQ(arr[2], 20);
    EXPECT_EQ(arr[3], 30);

    array_delete(arr);
}

TEST(Array, Delete) {
    std::size_t size = 4;
    int* arr = array_create(size);
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;

    arr = array_remove(arr, size, 1);

    ASSERT_NE(arr, nullptr);
    EXPECT_EQ(size, 3u);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 30);
    EXPECT_EQ(arr[2], 40);

    array_delete(arr);
}

TEST(Array, DeleteLast) {
    std::size_t size = 1;
    int* arr = array_create(size);
    arr[0] = 42;

    arr = array_remove(arr, size, 0);

    EXPECT_EQ(arr, nullptr);
    EXPECT_EQ(size, 0u);
}

TEST(Array, Sort) {
    int arr[] = {3, 1, 4, 1, 5};

    array_selection_sort(arr, 5);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 1);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
    EXPECT_EQ(arr[4], 5);
}

TEST(Array, Search) {
    const int arr[] = {1, 3, 5, 7, 9};
    std::size_t index = 0;

    bool found = array_binary_search(arr, 5, 7, index);

    EXPECT_TRUE(found);
    EXPECT_EQ(index, 3u);
}

TEST(Array, SearchNo) {
    const int arr[] = {1, 3, 5, 7, 9};
    std::size_t index = 0;

    bool found = array_binary_search(arr, 5, 4, index);

    EXPECT_FALSE(found);
}

TEST(Array, Reverse) {
    int arr[] = {1, 2, 3, 4, 5};
    int* empty_arr = array_create(0);

    array_reverse(arr, 5);
    array_reverse(empty_arr, 0);

    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 4);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 2);
    EXPECT_EQ(arr[4], 1);

    array_delete(empty_arr);
}
