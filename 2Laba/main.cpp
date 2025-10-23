#include <iostream>
#include <ctime>
#include <chrono>

// Для работы с массивом символов:
#include "set_array.h"

// Для работы со связным списком:
// #include "set_list.h"

// Для работы с булевым массивом:
//#include "set_bool_array.h"

// Для работы с битовым представлением:
// #include "set_bitset.h"

using namespace std;

static unsigned int next_rand = 1;

// Очистка экрана перед каждым вариантом работы
void screen_cleaner(){cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";}

int my_rand() {
    next_rand = next_rand * 1103515245 + 12345;
    return (unsigned int)(next_rand / 65536) % 32768;
}

void my_srand(unsigned int seed) {
    next_rand = seed;
}

void swap_chars(char &a, char &b) {
    char temp = a;
    a = b;
    b = temp;
}

void m_word_to_str(unsigned int w, char *str)
{
    int index = 0;
    for (int i = 0; i < 16; ++i)
    {
        if (w & (1 << i))
        {
            str[index++] = '0' + i;
        }
    }
    str[index] = '\0';
}

// Генерация случайного множества цифр
void rand_set(char *str, int size) {
    char universal[] = "0123456789";
    int n = 10;
    for (int i = 0; i < n - 1; ++i) {
        int j = my_rand() % (n - i);
        swap_chars(universal[i], universal[i + j]);
    }
    for (int i = 0; i < size; ++i) {
        str[i] = universal[i];
    }
    str[size] = '\0';
}

// Функция для замера времени выполнения
void measure_time(const int count_of_tests) {
    // Отключаем отладочный вывод для замера времени
    Set::setDebug(false);
    
    char A_str[11], B_str[11], C_str[11], D_str[11];

    for (int set_size = 1; set_size < 10; ++set_size) {
        rand_set(A_str, set_size);
        rand_set(B_str, set_size);
        rand_set(C_str, set_size);
        rand_set(D_str, set_size);

        cout << "Set size = " << set_size << endl;
        cout << "Generated sets:\n";
        cout << "A: " << A_str << " B: " << B_str << " C: " << C_str << " D: " << D_str << endl;

        char E_array[11];
        Node *E_list = nullptr;
        bool E_bitarray[10];
        unsigned int E_bitset = 0;
        char E_str_from_list[11], E_str_from_bitarray[11], E_str_from_bitset[11];

        // Замер времени для массива символов
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i != count_of_tests; ++i) {
            compute_with_array(A_str, B_str, C_str, D_str, E_array);
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "Array time: " << duration.count() << " seconds\n";

        // Замер времени для списка
        start = chrono::high_resolution_clock::now();
        for (int i = 0; i != count_of_tests; ++i) {
            compute_with_list(A_str, B_str, C_str, D_str, E_list);
        }
        end = chrono::high_resolution_clock::now();
        duration = end - start;
        cout << "List time: " << duration.count() << " seconds\n";
        list_to_string(E_list, E_str_from_list);
        clear_list(E_list);

        // Замер времени для битового массива
        start = chrono::high_resolution_clock::now();
        for (int i = 0; i != count_of_tests; ++i) {
            compute_with_bitarr(A_str, B_str, C_str, D_str, E_bitarray);
        }
        end = chrono::high_resolution_clock::now();
        duration = end - start;
        cout << "BitArray time: " << duration.count() << " seconds\n";
        bitarr_to_str(E_bitarray, E_str_from_bitarray);

        // Замер времени для битовой маски
        start = chrono::high_resolution_clock::now();
        for (int i = 0; i != count_of_tests; ++i) {
            compute_with_bitset(A_str, B_str, C_str, D_str, E_bitset);
        }
        end = chrono::high_resolution_clock::now();
        duration = end - start;
        cout << "Bitset time: " << duration.count() << " seconds\n";
        m_word_to_str(E_bitset, E_str_from_bitset);

        // Вывод результатов
        cout << "Results:\n";
        cout << "Array: " << E_array << endl;
        cout << "List: " << E_str_from_list << endl;
        cout << "BitArray: " << E_str_from_bitarray << endl;
        cout << "Bitset: " << E_str_from_bitset << endl;
        cout << endl;
    }
    
    // Включаем отладочный вывод обратно
    Set::setDebug(true);
}

int main() {
    my_srand(time(0));

    char E_array[11];
    Node *E_list = nullptr;
    bool E_bitarray[10];
    unsigned int E_bitset = 0;
    char E_str_from_list[11], E_str_from_bitarray[11], E_str_from_bitset[11];
    int choice = 0;

    do
    {
        do {
        cout << "Enter your choice how to run the program:\n1 - run program with constant data\n2 - run program with console data\n3 - run program with random data (10 tests)\n4 - exit" << endl;
        cin >> choice;
    } while (choice != 1 && choice != 2 && choice != 3);

    if (choice == 1) {
        screen_cleaner();
        // Константные данные
        const char *A = "013";
        const char *B = "123"; 
        const char *C = "234";
        const char *D = "345";

        cout << "Constant test with tracing:\n";
        cout << "A: " << A << "\nB: " << B << "\nC: " << C << "\nD: " << D << endl;

        compute_with_array(A, B, C, D, E_array);
        compute_with_list(A, B, C, D, E_list);
        compute_with_bitarr(A, B, C, D, E_bitarray);
        compute_with_bitset(A, B, C, D, E_bitset);

        list_to_string(E_list, E_str_from_list);
        bitarr_to_str(E_bitarray, E_str_from_bitarray);
        m_word_to_str(E_bitset, E_str_from_bitset);

        cout << "Results:\n";
        cout << "Array: " << E_array << endl;
        cout << "List: " << E_str_from_list << endl;
        cout << "BitArray: " << E_str_from_bitarray << endl;
        cout << "Bitset: " << E_str_from_bitset << endl;

        clear_list(E_list);
    }
    else if (choice == 2) {
        screen_cleaner();
        // Тест с вводом с клавиатуры
        char A_input[80], B_input[80], C_input[80], D_input[80];
        cout << "\nEnter sets of digits (without spaces):\n";
        cin.ignore();
        cout << "A: ";
        cin.getline(A_input, 80);
        cout << "B: ";
        cin.getline(B_input, 80);
        cout << "C: ";
        cin.getline(C_input, 80);
        cout << "D: ";
        cin.getline(D_input, 80);

        compute_with_array(A_input, B_input, C_input, D_input, E_array);
        compute_with_list(A_input, B_input, C_input, D_input, E_list);
        compute_with_bitarr(A_input, B_input, C_input, D_input, E_bitarray);
        compute_with_bitset(A_input, B_input, C_input, D_input, E_bitset);

        list_to_string(E_list, E_str_from_list);
        bitarr_to_str(E_bitarray, E_str_from_bitarray);
        m_word_to_str(E_bitset, E_str_from_bitset);

        cout << "Input test:\n";
        cout << "Array: " << E_array << endl;
        cout << "List: " << E_str_from_list << endl;
        cout << "BitArray: " << E_str_from_bitarray << endl;
        cout << "Bitset: " << E_str_from_bitset << endl;

        clear_list(E_list);
    }
    else if (choice == 3) {
        screen_cleaner();
        // Замер времени на случайных данных
        int count_of_tests;
        do
        {
            cout << "Enter the number of tests for each set: ";
            cin >> count_of_tests;

        } while (count_of_tests <= 0);
        
        cout << "\nTime measurement with random sets:\n";
        measure_time(count_of_tests);
    }
       
    } while (choice != 4);

    return 0;
}