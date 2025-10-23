#ifndef SET_BOOL_ARRAY_H
#define SET_BOOL_ARRAY_H

#include <iostream>
#include <cstring>

const int UNIVERSAL_SIZE = 10;

class Set {
private:
    bool elements[UNIVERSAL_SIZE]; // булев массив
    char tag;
    static int object_count;
    static bool debug;
    
    void printDebug(const char* message) const {
        if (debug) {
            std::cout << message << " Set " << tag << " = [";
            show();
            std::cout << "]" << std::endl;
        }
    }

public:
    static void setDebug(bool d) { debug = d; }
    
    Set() : tag('A' + object_count++) {
        for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
            elements[i] = false;
        }
        printDebug("Конструктор по умолчанию");
    }
    
    Set(const char* str) : tag('A' + object_count++) {
        for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
            elements[i] = false;
        }
        for (int i = 0; str[i] != '\0'; ++i) {
            if (str[i] >= '0' && str[i] <= '9') {
                int pos = str[i] - '0';
                elements[pos] = true;
            }
        }
        printDebug("Конструктор из строки");
    }
    
    Set(const Set& other) : tag('A' + object_count++) {
        for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
            elements[i] = other.elements[i];
        }
        printDebug("Конструктор копирования");
    }
    
    Set(Set&& other) noexcept : tag('A' + object_count++) {
        for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
            elements[i] = other.elements[i];
            other.elements[i] = false;
        }
        printDebug("Конструктор перемещения");
    }
    
    ~Set() {
        if (debug) {
            std::cout << "Деструктор: уничтожен Set " << tag << std::endl;
        }
    }
    
    Set& operator=(const Set& other) {
        if (this != &other) {
            for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
                elements[i] = other.elements[i];
            }
            if (debug) {
                std::cout << "Оператор присваивания: Set " << tag << " = Set " << other.tag << std::endl;
            }
        }
        return *this;
    }
    
    Set& operator=(Set&& other) noexcept {
        if (this != &other) {
            for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
                elements[i] = other.elements[i];
                other.elements[i] = false;
            }
            if (debug) {
                std::cout << "Оператор присваивания перемещением: Set " << tag << std::endl;
            }
        }
        return *this;
    }
    
    Set operator|(const Set& other) const {
        if (debug) {
            std::cout << "Оператор |: объединение Set " << tag << " и Set " << other.tag << std::endl;
        }
        Set result;
        for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
            result.elements[i] = elements[i] || other.elements[i];
        }
        return result;
    }
    
    Set operator&(const Set& other) const {
        if (debug) {
            std::cout << "Оператор &: пересечение Set " << tag << " и Set " << other.tag << std::endl;
        }
        Set result;
        for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
            result.elements[i] = elements[i] && other.elements[i];
        }
        return result;
    }
    
    Set operator~() const {
        if (debug) {
            std::cout << "Оператор ~: дополнение Set " << tag << std::endl;
        }
        Set result;
        for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
            result.elements[i] = !elements[i];
        }
        return result;
    }
    
    Set& operator|=(const Set& other) {
        if (debug) {
            std::cout << "Оператор |=: Set " << tag << " |= Set " << other.tag << std::endl;
        }
        for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
            elements[i] = elements[i] || other.elements[i];
        }
        return *this;
    }
    
    Set& operator&=(const Set& other) {
        if (debug) {
            std::cout << "Оператор &=: Set " << tag << " &= Set " << other.tag << std::endl;
        }
        for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
            elements[i] = elements[i] && other.elements[i];
        }
        return *this;
    }
    
    bool operator==(const Set& other) const {
        for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
            if (elements[i] != other.elements[i]) {
                return false;
            }
        }
        return true;
    }
    
    bool operator!=(const Set& other) const {
        return !(*this == other);
    }
    
    bool contains(char c) const {
        if (c >= '0' && c <= '9') {
            return elements[c - '0'];
        }
        return false;
    }
    
    void add(char c) {
        if (c >= '0' && c <= '9') {
            elements[c - '0'] = true;
        }
    }
    
    void remove(char c) {
        if (c >= '0' && c <= '9') {
            elements[c - '0'] = false;
        }
    }
    
    void show() const {
        bool isEmpty = true;
        for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
            if (elements[i]) {
                std::cout << char('0' + i);
                isEmpty = false;
            }
        }
        if (isEmpty) {
            std::cout << "пусто";
        }
    }
    
    void Show() const {
        std::cout << "Set " << tag << " = [";
        show();
        std::cout << "]";
    }
    
    int power() const {
        int count = 0;
        for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
            if (elements[i]) {
                count++;
            }
        }
        return count;
    }
    
    void getElements(char* str) const {
        int index = 0;
        for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
            if (elements[i]) {
                str[index++] = '0' + i;
            }
        }
        str[index] = '\0';
    }
    
    unsigned int getBits() const {
        unsigned int bits = 0;
        for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
            if (elements[i]) {
                bits |= (1u << i);
            }
        }
        return bits;
    }
    
    static Set universal() {
        Set result;
        for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
            result.elements[i] = true;
        }
        return result;
    }
    
    static Set empty() {
        return Set();
    }
};

// Инициализация статических членов
int Set::object_count = 0;
bool Set::debug = true;

// Структура для узла списка (для совместимости)
struct Node
{
    char digit;
    Node *next;
    Node(char d, Node *n = nullptr) : digit(d), next(n) {}
};

// Вспомогательные функции для работы со списками
bool contains(Node *head, char c) {
    Node *p = head;
    while (p != nullptr) {
        if (p->digit == c)
            return true;
        p = p->next;
    }
    return false;
}

void insert(Node *&head, char c) {
    if (contains(head, c))
        return;
    Node *newNode = new Node(c, head);
    head = newNode;
}

void clear_list(Node *&head) {
    Node *p = head;
    while (p != nullptr) {
        Node *temp = p;
        p = p->next;
        delete temp;
    }
    head = nullptr;
}

void list_to_string(Node *head, char *str) {
    int i = 0;
    Node *p = head;
    while (p != nullptr) {
        str[i++] = p->digit;
        p = p->next;
    }
    str[i] = '\0';
}

// Вспомогательная функция для копирования строк
void string_copy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Функции для преобразования представлений
void str_to_bitarr(const char *str, bool *bits) {
    for (int i = 0; i < UNIVERSAL_SIZE; ++i)
        bits[i] = false;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            int index = str[i] - '0';
            bits[index] = true;
        }
    }
}

void bitarr_to_str(const bool *bits, char *str) {
    int index = 0;
    for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
        if (bits[i]) {
            str[index++] = '0' + i;
        }
    }
    str[index] = '\0';
}

// Основные вычислительные функции
void compute_with_array(const char *A, const char *B, const char *C, const char *D, char *E) {
    Set setA(A), setB(B), setC(C), setD(D);
    Set setE = setA | setD | (setB & setC);
    setE.getElements(E);
}

void compute_with_list(const char *A, const char *B, const char *C, const char *D, Node *&E) {
    Set setA(A), setB(B), setC(C), setD(D);
    Set setE = setA | setD | (setB & setC);
    
    char temp[11];
    setE.getElements(temp);
    
    clear_list(E);
    for (int i = 0; temp[i] != '\0'; ++i) {
        insert(E, temp[i]);
    }
}

void compute_with_bitarr(const char *A, const char *B, const char *C, const char *D, bool *E) {
    Set setA(A), setB(B), setC(C), setD(D);
    Set setE = setA | setD | (setB & setC);
    
    for (int i = 0; i < UNIVERSAL_SIZE; ++i) E[i] = false;
    
    unsigned int bits = setE.getBits();
    for (int i = 0; i < UNIVERSAL_SIZE; ++i) {
        if (bits & (1u << i)) {
            E[i] = true;
        }
    }
}

void compute_with_bitset(const char *A, const char *B, const char *C, const char *D, unsigned int &wE) {
    Set setA(A), setB(B), setC(C), setD(D);
    Set setE = setA | setD | (setB & setC);
    wE = setE.getBits();
}

#endif // SET_BOOL_ARRAY_H