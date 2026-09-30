#include "array_ops.h"

#include <iostream>
#include <limits>

void input_error() {
    std::cin.clear();
    std::cin.ignore(
        std::numeric_limits<std::streamsize>::max(),
        '\n'
    );

    std::cout << "Ошибка: введите число\n";
}

int main() {

    int* arr = nullptr;
    std::size_t size = 0;

    while (true) {

        std::cout << "\n";
        std::cout << "Введите команду из списка:\n";
        std::cout << "1. Создать массив       2. Напечатать массив\n";
        std::cout << "3. Вставить элемент     4. Удалить элемент\n";
        std::cout << "5. Изменить размер      6. Сортировать выбором\n";
        std::cout << "7. Бинарный поиск       8. Алгоритм варианта\n";
        std::cout << "0. Выход\n";

        int command;

        if (!(std::cin >> command)) {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            std::cout << "Ошибка: введите номер команды\n";
            continue;
        }

        if (command == 0) {
            break;
        }

        if (command < 0 || command > 8) {
            std::cout << "Неверная команда\n";
            continue;
        }

        switch (command) {

            case 1: {
                if (arr) {
                    array_delete(arr);
                }

                size = 0;

                long long input_size;

                std::cout << "Введите размер массива:\n";
                if (!(std::cin >> input_size)) {
                    input_error();
                    break;
                }

                if (input_size < 0) {
                    std::cout << "Размер не может быть отрицательным\n";
                    break;
                }

                if (input_size == 0) {
                    std::cout << "Создан пустой массив\n";
                    break;
                }

                size = static_cast<std::size_t>(input_size);
                arr = array_create(size);

                std::cout << "Введите " << size << " элементов:\n";

                bool input_ok = true;

                for (std::size_t i = 0; i < size; ++i) {
                    if (!(std::cin >> arr[i])) {
                        input_error();
                        input_ok = false;
                        break;
                    }
                }

                if (!input_ok) {
                    array_delete(arr);
                    size = 0;
                    break;
                }

                std::cout << "Массив успешно создан:\n";
                array_print(arr, size);
                std::cout << '\n';

                break;
            }

            case 2: {
                if (!arr || size == 0) {
                    std::cout << "Массив пуст\n";
                    break;
                }

                std::cout << "Массив:\n";
                array_print(arr, size);
                std::cout << '\n';

                break;
            }

            case 3: {
                long long input_pos;
                int value;

                std::cout << "Введите позицию (индекс) для вставки:\n";
                if (!(std::cin >> input_pos)) {
                    input_error();
                    break;
                }

                if (input_pos < 0 ||
                    static_cast<std::size_t>(input_pos) > size) {

                    std::cout << "Некорректная позиция\n";
                    break;
                }

                std::cout << "Введите значение для вставки:\n";
                if (!(std::cin >> value)) {
                    input_error();
                    break;
                }

                std::cout << "До вставки:\n";

                if (size == 0) {
                    std::cout << "Массив пуст\n";
                } else {
                    array_print(arr, size);
                    std::cout << '\n';
                }

                int* new_arr = array_insert(
                    arr,
                    size,
                    static_cast<std::size_t>(input_pos),
                    value
                );

                if (!new_arr) {
                    std::cout << "Ошибка вставки\n";
                    break;
                }

                arr = new_arr;

                std::cout << "После вставки:\n";
                array_print(arr, size);
                std::cout << '\n';

                break;
            }

            case 4: {
                if (!arr || size == 0) {
                    std::cout << "Массив пуст, удалять нечего\n";
                    break;
                }

                long long input_pos;

                std::cout << "Введите позицию (индекс) для удаления:\n";
                if (!(std::cin >> input_pos)) {
                    input_error();
                    break;
                }

                if (input_pos < 0 ||
                    static_cast<std::size_t>(input_pos) >= size) {

                    std::cout << "Некорректная позиция\n";
                    break;
                }

                std::cout << "До удаления:\n";
                array_print(arr, size);
                std::cout << '\n';

                arr = array_remove(
                    arr,
                    size,
                    static_cast<std::size_t>(input_pos)
                );

                std::cout << "После удаления:\n";

                if (size == 0) {
                    std::cout << "Массив пуст\n";
                } else {
                    array_print(arr, size);
                    std::cout << '\n';
                }

                break;
            }

            case 5: {
                long long input_size;

                std::cout << "Введите новый размер массива:\n";
                if (!(std::cin >> input_size)) {
                    input_error();
                    break;
                }

                if (input_size < 0) {
                    std::cout << "Размер не может быть отрицательным\n";
                    break;
                }

                std::size_t new_size =
                    static_cast<std::size_t>(input_size);

                std::cout << "До изменения размера:\n";

                if (size == 0) {
                    std::cout << "Массив пуст\n";
                } else {
                    array_print(arr, size);
                    std::cout << '\n';
                }

                if (new_size == 0) {
                    array_delete(arr);
                    size = 0;

                    std::cout << "Размер изменён на 0. Массив пуст\n";
                    break;
                }

                int* new_arr = array_resize(arr, size, new_size);

                if (!new_arr) {
                    std::cout << "Ошибка изменения размера\n";
                    break;
                }

                arr = new_arr;
                size = new_size;

                std::cout << "После изменения размера:\n";
                array_print(arr, size);
                std::cout << '\n';

                break;
            }

            case 6: {
                if (!arr || size == 0) {
                    std::cout << "Массив пуст\n";
                    break;
                }

                std::cout << "До сортировки:\n";
                array_print(arr, size);
                std::cout << '\n';

                array_selection_sort(arr, size);

                std::cout << "После сортировки выбором:\n";
                array_print(arr, size);
                std::cout << '\n';

                break;
            }

            case 7: {
                if (!arr || size == 0) {
                    std::cout << "Массив пуст\n";
                    break;
                }

                array_selection_sort(arr, size);

                std::cout << "Массив отсортирован для бинарного поиска:\n";
                array_print(arr, size);
                std::cout << '\n';

                int target;

                std::cout << "Введите значение для поиска:\n";
                if (!(std::cin >> target)) {
                    input_error();
                    break;
                }

                std::size_t index;

                if (array_binary_search(arr, size, target, index)) {
                    std::cout << "Элемент найден. Индекс: "
                              << index << '\n';
                } else {
                    std::cout << "Элемент не найден\n";
                }

                break;
            }

            case 8: {
                if (!arr || size == 0) {
                    std::cout << "Массив пуст\n";
                    break;
                }

                std::cout << "Исходный массив:\n";
                array_print(arr, size);
                std::cout << '\n';

                array_selection_sort(arr, size);

                std::cout << "После сортировки выбором:\n";
                array_print(arr, size);
                std::cout << '\n';

                array_reverse(arr, size);

                std::cout << "После разворота:\n";
                array_print(arr, size);
                std::cout << '\n';

                break;
            }

            default:
                break;
        }
    }

    array_delete(arr);

    return 0;
}
