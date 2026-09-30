#include "array_ops.h"
#include <iostream>
int* array_create(std::size_t size){
    int* arr = new int[size];
    if (arr) return arr;
    return nullptr;
}

void array_delete(int*& arr){
    delete[] arr;
    arr = nullptr;
}
int* array_resize(int* arr, std::size_t size, std::size_t new_size){
    if (new_size == 0){
        array_delete(arr);
        return nullptr;
    }
    int* new_arr = new int[new_size]{};
    if (!new_arr) return nullptr;
    std::size_t elems_for_copy;
    if (size >= new_size) elems_for_copy = new_size;
    else elems_for_copy = size;
    for (std::size_t i = 0; i < elems_for_copy; ++i){
        new_arr[i] = arr[i];
    }
    array_delete(arr);
    return new_arr;
}

int* array_insert(int* arr, std::size_t& size, std::size_t pos, int value){
    if (pos > size) return nullptr;
    int* new_arr = array_resize(arr,size,size+1);
    if (!new_arr) return nullptr;
    arr = new_arr;
    for (std::size_t i = size; i > pos; --i){
        arr[i] = arr[i-1];
    }
    arr[pos] = value;
    ++size;
    return arr;
}

int* array_remove(int* arr, std::size_t& size, std::size_t pos){
    if (!arr) return nullptr;
    if (pos >= size) return nullptr;
    if (size == 1) {
        array_delete(arr);
        size = 0;
        return nullptr;
    }
    for (std::size_t i = pos; i < size-1; ++i){
        arr[i] = arr[i+1];
    }
    int* new_arr = array_resize(arr,size,size-1);
    if (!new_arr) return nullptr;
    arr = new_arr;
    --size;
    return arr;
}
void array_print(const int* arr, std::size_t size){
    if (!arr || size == 0) return;
    std::cout << arr[0];
    for (std::size_t i = 1; i < size; ++i){
        std::cout << " " << arr[i];
    }
}

void array_selection_sort(int* arr, std::size_t size) {
    if (!arr || size < 2) return;
    for (std::size_t i = 0; i < size - 1; ++i){
        std::size_t min_index = i;
        for (std::size_t j = i + 1; j < size; ++j){
            if (arr[j] < arr[min_index]) min_index = j;
        }
        if (min_index != i){
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}

bool array_binary_search(const int* arr, std::size_t size, int target, std::size_t&
out_index){
    if (!arr || size == 0) return false;
    std::size_t left = 0;
    std::size_t right = size;
    while (left < right){
        std::size_t mid = left + (right - left) / 2;
        if (arr[mid] == target){
            out_index = mid;
            return true;
        }
        else if (target > arr[mid]){
            left = mid + 1;
        }
        else right = mid;
    }
    return false;
}

void array_reverse(int* arr, std::size_t size){
    if (!arr || size < 2) return;
    int* left = arr;
    int* right = arr + size - 1;
    while (left < right){
        int temp = *left;
        *left = *right;
        *right = temp;
        ++left;
        --right;
    }
}
