#ifndef SET_ARRAY_H
#define SET_ARRAY_H

#include <iostream>
#include <cstring>

const int UNIVERSAL_SIZE = 10;

class Set {
private:
    char elements[UNIVERSAL_SIZE + 1]; // массив для хранения элементов + терминатор
    char tag;
    static int object_count;
    static bool debug;
    
    void sortElements() {
        // Сортировка пузырьком
        int len = strlen(elements);
        for (int i = 0; i < len - 1; ++i) {
            for (int j = 0; j < len - i - 1; ++j) {
                if (elements[j] > elements[j + 1]) {
                    char temp = elements[j];
                    elements[j] = elements[j + 1];
                    elements[j + 1] = temp;
                }
            }
        }
    }
    
    void removeDuplicates() {
        int len = strlen(elements);
        int newIndex = 0;
        for (int i = 0; i < len; ++i) {
            bool found = false;
            for (int j = 0; j < newIndex; ++j) {
                if (elements[j] == elements[i]) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                elements[newIndex++] = elements[i];
            }
        }
        elements[newIndex] = '\0';
    }
    
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
        elements[0] = '\0';
        printDebug("Конструктор по умолчанию");
    }
    
    Set(const char* str) : tag('A' + object_count++) {
        elements[0] = '\0';
        for (int i = 0; str[i] != '\0'; ++i) {
            if (str[i] >= '0' && str[i] <= '9') {
                add(str[i]);
            }
        }
        sortElements();
        printDebug("Конструктор из строки");
    }
    
    Set(const Set& other) : tag('A' + object_count++) {
        strcpy(elements, other.elements);
        printDebug("Конструктор копирования");
    }
    
    Set(Set&& other) noexcept : tag('A' + object_count++) {
        strcpy(elements, other.elements);
        other.elements[0] = '\0';
        printDebug("Конструктор перемещения");
    }
    
    ~Set() {
        if (debug) {
            std::cout << "Деструктор: уничтожен Set " << tag << std::endl;
        }
    }
    
    Set& operator=(const Set& other) {
        if (this != &other) {
            strcpy(elements, other.elements);
            if (debug) {
                std::cout << "Оператор присваивания: Set " << tag << " = Set " << other.tag << std::endl;
            }
        }
        return *this;
    }
    
    Set& operator=(Set&& other) noexcept {
        if (this != &other) {
            strcpy(elements, other.elements);
            other.elements[0] = '\0';
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
        strcpy(result.elements, elements);
        
        for (int i = 0; other.elements[i] != '\0'; ++i) {
            result.add(other.elements[i]);
        }
        
        result.sortElements();
        return result;
    }
    
    Set operator&(const Set& other) const {
        if (debug) {
            std::cout << "Оператор &: пересечение Set " << tag << " и Set " << other.tag << std::endl;
        }
        Set result;
        
        for (int i = 0; elements[i] != '\0'; ++i) {
            for (int j = 0; other.elements[j] != '\0'; ++j) {
                if (elements[i] == other.elements[j]) {
                    result.add(elements[i]);
                    break;
                }
            }
        }
        
        result.sortElements();
        return result;
    }
    
    Set operator~() const {
        if (debug) {
            std::cout << "Оператор ~: дополнение Set " << tag << std::endl;
        }
        Set result;
        
        for (char c = '0'; c <= '9'; ++c) {
            bool found = false;
            for (int i = 0; elements[i] != '\0'; ++i) {
                if (elements[i] == c) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                result.add(c);
            }
        }
        
        return result;
    }
    
    Set& operator|=(const Set& other) {
        if (debug) {
            std::cout << "Оператор |=: Set " << tag << " |= Set " << other.tag << std::endl;
        }
        
        for (int i = 0; other.elements[i] != '\0'; ++i) {
            add(other.elements[i]);
        }
        
        sortElements();
        return *this;
    }
    
    Set& operator&=(const Set& other) {
        if (debug) {
            std::cout << "Оператор &=: Set " << tag << " &= Set " << other.tag << std::endl;
        }
        
        char temp[UNIVERSAL_SIZE + 1];
        temp[0] = '\0';
        int index = 0;
        
        for (int i = 0; elements[i] != '\0'; ++i) {
            for (int j = 0; other.elements[j] != '\0'; ++j) {
                if (elements[i] == other.elements[j]) {
                    temp[index++] = elements[i];
                    break;
                }
            }
        }
        temp[index] = '\0';
        strcpy(elements, temp);
        
        return *this;
    }
    
    bool operator==(const Set& other) const {
        return strcmp(elements, other.elements) == 0;
    }
    
    bool operator!=(const Set& other) const {
        return strcmp(elements, other.elements) != 0;
    }
    
    bool contains(char c) const {
        for (int i = 0; elements[i] != '\0'; ++i) {
            if (elements[i] == c) {
                return true;
            }
        }
        return false;
    }
    
    void add(char c) {
        if (c >= '0' && c <= '9' && !contains(c)) {
            int len = strlen(elements);
            elements[len] = c;
            elements[len + 1] = '\0';
        }
    }
    
    void remove(char c) {
        int len = strlen(elements);
        int newIndex = 0;
        for (int i = 0; i < len; ++i) {
            if (elements[i] != c) {
                elements[newIndex++] = elements[i];
            }
        }
        elements[newIndex] = '\0';
    }
    
    void show() const {
        if (elements[0] == '\0') {
            std::cout << "пусто";
        } else {
            std::cout << elements;
        }
    }
    
    void Show() const {
        std::cout << "Set " << tag << " = [";
        show();
        std::cout << "]";
    }
    
    int power() const {
        return strlen(elements);
    }
    
    void getElements(char* str) const {
        strcpy(str, elements);
    }
    
    unsigned int getBits() const {
        unsigned int bits = 0;
        for (int i = 0; elements[i] != '\0'; ++i) {
            int pos = elements[i] - '0';
            bits |= (1u << pos);
        }
        return bits;
    }
    
    static Set universal() {
        Set result;
        for (char c = '0'; c <= '9'; ++c) {
            result.add(c);
        }
        return result;
    }
    
    static Set empty() {
        return Set();
    }
};

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

int Set::object_count = 0;
bool Set::debug = true;

#endif // SET_ARRAY_H