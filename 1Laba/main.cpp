#include <iostream>
#include <ctime>
#include <chrono>

using namespace std;

const int UNIVERSAL_SIZE = 10;

// Структура для узла списка
struct Node
{
    char digit;
    Node *next;
    Node(char d, Node *n = nullptr) : digit(d), next(n) {}
};

// Функции для работы с массивами символов
bool is_in_array(char c, const char *arr)
{
    for (int i = 0; arr[i] != '\0'; ++i)
    {
        if (arr[i] == c)
            return true;
    }
    return false;
}

void string_copy(char *dest, const char *src)
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

void compute_with_array(const char *A, const char *B, const char *C, const char *D, char *E)
{
    char temp[11] = {0};
    int index = 0;

    for (int i = 0; B[i] != '\0'; ++i)
    {
        if (is_in_array(B[i], C) && !is_in_array(B[i], temp))
        {
            temp[index++] = B[i];
        }
    }

    for (int i = 0; A[i] != '\0'; ++i)
    {
        if (!is_in_array(A[i], temp))
        {
            temp[index++] = A[i];
        }
    }

    for (int i = 0; D[i] != '\0'; ++i)
    {
        if (!is_in_array(D[i], temp))
        {
            temp[index++] = D[i];
        }
    }

    temp[index] = '\0';
    string_copy(E, temp);
}

// Функции для работы с односвязными списками
bool contains(Node *head, char c)
{
    Node *p = head;
    while (p != nullptr)
    {
        if (p->digit == c)
            return true;
        p = p->next;
    }
    return false;
}

void insert(Node *&head, char c)
{
    if (contains(head, c))
        return;
    Node *newNode = new Node(c, head);
    head = newNode;
}

void clear_list(Node *&head)
{
    Node *p = head;
    while (p != nullptr)
    {
        Node *temp = p;
        p = p->next;
        delete temp;
    }
    head = nullptr;
}

void list_to_string(Node *head, char *str)
{
    int i = 0;
    Node *p = head;
    while (p != nullptr)
    {
        str[i++] = p->digit;
        p = p->next;
    }
    str[i] = '\0';
}

void compute_with_list(const char *A, const char *B, const char *C, const char *D, Node *&E)
{
    clear_list(E);
    for (int i = 0; A[i] != '\0'; ++i)
    {
        insert(E, A[i]);
    }
    for (int i = 0; D[i] != '\0'; ++i)
    {
        insert(E, D[i]);
    }
    for (int i = 0; B[i] != '\0'; ++i)
    {
        if (is_in_array(B[i], C) && !contains(E, B[i]))
        {
            insert(E, B[i]);
        }
    }
}

// Функции для работы с битовыми массивами
void str_to_bitarr(const char *str, bool *bits)
{
    for (int i = 0; i < UNIVERSAL_SIZE; ++i)
        bits[i] = false;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            int index = str[i] - '0';
            bits[index] = true;
        }
    }
}

void bitarr_to_str(const bool *bits, char *str)
{
    int index = 0;
    for (int i = 0; i < UNIVERSAL_SIZE; ++i)
    {
        if (bits[i])
        {
            str[index++] = '0' + i;
        }
    }
    str[index] = '\0';
}

void compute_with_bitarr(const char *A, const char *B, const char *C, const char *D, bool *E)
{
    bool A_bits[UNIVERSAL_SIZE], B_bits[UNIVERSAL_SIZE], C_bits[UNIVERSAL_SIZE], D_bits[UNIVERSAL_SIZE];
    str_to_bitarr(A, A_bits);
    str_to_bitarr(B, B_bits);
    str_to_bitarr(C, C_bits);
    str_to_bitarr(D, D_bits);

    for (int i = 0; i < UNIVERSAL_SIZE; ++i)
    {
        E[i] = A_bits[i] || D_bits[i] || (B_bits[i] && C_bits[i]);
    }
}

// Функции для работы с машинным словом
void str_to_m_word(const char *str, unsigned int &w)
{
    w = 0;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            int index = str[i] - '0';
            w |= (1 << index);
        }
    }
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

void compute_with_bitset(const char *A, const char *B, const char *C, const char *D, unsigned int &wE)
{
    unsigned int wA, wB, wC, wD;
    str_to_m_word(A, wA);
    str_to_m_word(B, wB);
    str_to_m_word(C, wC);
    str_to_m_word(D, wD);
    wE = wA | wD | (wB & wC);
}

// Простой генератор случайных чисел (линейный конгруэнтный метод)
static unsigned int next_rand = 1;

int my_rand()
{
    next_rand = next_rand * 1103515245 + 12345;
    return (unsigned int)(next_rand / 65536) % 32768;
}
// замена srand из cstdlib
void my_srand(unsigned int seed)
{
    next_rand = seed;
}

void swap_chars(char &a, char &b)
{
    char temp = a;
    a = b;
    b = temp;
}

// Генерация случайного множества цифр
void rand_set(char *str, int size)
{
    char universal[] = "0123456789";
    int n = 10;
    for (int i = 0; i < n - 1; ++i)
    {
        int j = my_rand() % (n - i);
        swap_chars(universal[i], universal[i + j]);
    }
    for (int i = 0; i < size; ++i)
    {
        str[i] = universal[i];
    }
    str[size] = '\0';
}

// Функция для замера времени выполнения
void measure_time()
{

    // int set_size = 3;
    char A_str[11], B_str[11], C_str[11], D_str[11];

    for (int set_size = 1; set_size != 10; ++set_size)
    {

        rand_set(A_str, set_size);
        rand_set(B_str, set_size);
        rand_set(C_str, set_size);
        rand_set(D_str, set_size);

        cout << "Set size = " << set_size << endl;
        cout << "Generated sets:\n";
        cout << "A: " << A_str << "\nB: " << B_str << "\nC: " << C_str << "\nD: " << D_str << endl;

        // Можно изменить кол-во повторений = домножить на 10^n степени скорость работы
        const int repetitions = 1000000;

        char E_array[11];
        Node *E_list = nullptr;
        bool E_bitarray[UNIVERSAL_SIZE];
        unsigned int E_bitset = 0;
        char E_str_from_list[11], E_str_from_bitarray[11], E_str_from_bitset[11];

        // Замер времени для массива символов
        auto start = chrono::high_resolution_clock::now();
        for (int i = 0; i < repetitions; ++i)
        {
            compute_with_array(A_str, B_str, C_str, D_str, E_array);
        }
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;

        cout << "Array time: " << duration.count() << " seconds\n";

        // Замер времени для списка
        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < repetitions; ++i)
        {
            compute_with_list(A_str, B_str, C_str, D_str, E_list);
        }
        end = chrono::high_resolution_clock::now();
        duration = end - start;
        cout << "List time: " << duration.count() << " seconds\n";
        list_to_string(E_list, E_str_from_list);
        clear_list(E_list);

        // Замер времени для битового массива
        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < repetitions; ++i)
        {
            compute_with_bitarr(A_str, B_str, C_str, D_str, E_bitarray);
        }
        end = chrono::high_resolution_clock::now();
        duration = end - start;
        cout << "BitArray time: " << duration.count() << " seconds\n";
        bitarr_to_str(E_bitarray, E_str_from_bitarray);

        // Замер времени для битовой маски
        start = chrono::high_resolution_clock::now();
        for (int i = 0; i < repetitions; ++i)
        {
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
}

int main()
{
    my_srand(time(0));

    char E_array[11];
    Node *E_list = nullptr;
    bool E_bitarray[UNIVERSAL_SIZE];
    unsigned int E_bitset = 0;
    char E_str_from_list[11], E_str_from_bitarray[11], E_str_from_bitset[11];
    int choice = 0;

    do
    {
        cout << "Enter you'r choice how to run the programm:\n1 - run programm with constant data\n2 - run programm with console data\n3 - run programm with random data (10 test)" << endl;
        cin >> choice;
    } while (choice != 1 && choice != 2 && choice != 3);

    if (choice == 1)
    {
        // Константные данные
        const char *A = "0";
        const char *B = "1";
        const char *C = "3";
        const char *D = "4";

        compute_with_array(A, B, C, D, E_array);
        compute_with_list(A, B, C, D, E_list);
        compute_with_bitarr(A, B, C, D, E_bitarray);
        compute_with_bitset(A, B, C, D, E_bitset);

        list_to_string(E_list, E_str_from_list);
        bitarr_to_str(E_bitarray, E_str_from_bitarray);
        m_word_to_str(E_bitset, E_str_from_bitset);

        cout << "Constant test:\n";
        cout << "A: " << A << "\nB: " << B << "\nC: " << C << "\nD: " << D << endl;
        cout << "Array: " << E_array << endl;
        cout << "List: " << E_str_from_list << endl;
        cout << "BitArray: " << E_str_from_bitarray << endl;
        cout << "Bitset: " << E_str_from_bitset << endl;

        clear_list(E_list);
    }
    else if (choice == 2)
    {

        // Тест с вводом с клавиатуры
        char A_input[80], B_input[80], C_input[80], D_input[80];
        cout << "\nEnter sets of digits (without spaces):\n";
        getchar();
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
    else if (choice == 3)
    {
        // Замер времени на случайных данных
        cout << "\nTime measurement with random sets:\n";
        measure_time();
    }

    return 0;
}