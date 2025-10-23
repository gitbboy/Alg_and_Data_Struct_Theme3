#ifndef SET_LIST_H
#define SET_LIST_H

#include <iostream>
#include <cstring>

const int UNIVERSAL_SIZE = 10;

// Структура для узла списка (для внутреннего представления множества)
struct ListNode {
    char digit;
    ListNode* next;
    ListNode(char d, ListNode* n = nullptr) : digit(d), next(n) {}
};

// Структура для узла внешнего списка (для совместимости с main.cpp)
struct Node
{
    char digit;
    Node *next;
    Node(char d, Node *n = nullptr) : digit(d), next(n) {}
};

class Set {
private:
    ListNode* head;
    char tag;
    static int object_count;
    static bool debug;
    
    void clearList() {
        ListNode* current = head;
        while (current != nullptr) {
            ListNode* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }
    
    void sortList() {
        if (!head || !head->next) return;
        
        bool swapped;
        do {
            swapped = false;
            ListNode* current = head;
            ListNode* prev = nullptr;
            
            while (current && current->next) {
                if (current->digit > current->next->digit) {
                    // Меняем узлы местами
                    ListNode* next = current->next;
                    current->next = next->next;
                    next->next = current;
                    
                    if (prev) {
                        prev->next = next;
                    } else {
                        head = next;
                    }
                    
                    prev = next;
                    swapped = true;
                } else {
                    prev = current;
                    current = current->next;
                }
            }
        } while (swapped);
    }
    
    // Вспомогательная функция для проверки наличия элемента во внутреннем списке
    bool listContains(char c) const {
        ListNode* current = head;
        while (current != nullptr) {
            if (current->digit == c) {
                return true;
            }
            current = current->next;
        }
        return false;
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
    
    Set() : head(nullptr), tag('A' + object_count++) {
        printDebug("Конструктор по умолчанию");
    }
    
    Set(const char* str) : head(nullptr), tag('A' + object_count++) {
        for (int i = 0; str[i] != '\0'; ++i) {
            if (str[i] >= '0' && str[i] <= '9') {
                add(str[i]);
            }
        }
        sortList();
        printDebug("Конструктор из строки");
    }
    
    Set(const Set& other) : head(nullptr), tag('A' + object_count++) {
        ListNode* current = other.head;
        while (current != nullptr) {
            add(current->digit);
            current = current->next;
        }
        printDebug("Конструктор копирования");
    }
    
    Set(Set&& other) noexcept : head(other.head), tag('A' + object_count++) {
        other.head = nullptr;
        printDebug("Конструктор перемещения");
    }
    
    ~Set() {
        clearList();
        if (debug) {
            std::cout << "Деструктор: уничтожен Set " << tag << std::endl;
        }
    }
    
    Set& operator=(const Set& other) {
        if (this != &other) {
            clearList();
            ListNode* current = other.head;
            while (current != nullptr) {
                add(current->digit);
                current = current->next;
            }
            if (debug) {
                std::cout << "Оператор присваивания: Set " << tag << " = Set " << other.tag << std::endl;
            }
        }
        return *this;
    }
    
    Set& operator=(Set&& other) noexcept {
        if (this != &other) {
            clearList();
            head = other.head;
            other.head = nullptr;
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
        Set result(*this);
        
        ListNode* current = other.head;
        while (current != nullptr) {
            result.add(current->digit);
            current = current->next;
        }
        
        result.sortList();
        return result;
    }
    
    Set operator&(const Set& other) const {
        if (debug) {
            std::cout << "Оператор &: пересечение Set " << tag << " и Set " << other.tag << std::endl;
        }
        Set result;
        
        ListNode* current = head;
        while (current != nullptr) {
            if (other.contains(current->digit)) {
                result.add(current->digit);
            }
            current = current->next;
        }
        
        result.sortList();
        return result;
    }
    
    Set operator~() const {
        if (debug) {
            std::cout << "Оператор ~: дополнение Set " << tag << std::endl;
        }
        Set result;
        
        for (char c = '0'; c <= '9'; ++c) {
            if (!contains(c)) {
                result.add(c);
            }
        }
        
        return result;
    }
    
    Set& operator|=(const Set& other) {
        if (debug) {
            std::cout << "Оператор |=: Set " << tag << " |= Set " << other.tag << std::endl;
        }
        
        ListNode* current = other.head;
        while (current != nullptr) {
            add(current->digit);
            current = current->next;
        }
        
        sortList();
        return *this;
    }
    
    Set& operator&=(const Set& other) {
        if (debug) {
            std::cout << "Оператор &=: Set " << tag << " &= Set " << other.tag << std::endl;
        }
        
        ListNode* current = head;
        ListNode* prev = nullptr;
        
        while (current != nullptr) {
            if (!other.contains(current->digit)) {
                // Удаляем узел
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                ListNode* toDelete = current;
                current = current->next;
                delete toDelete;
            } else {
                prev = current;
                current = current->next;
            }
        }
        
        return *this;
    }
    
    bool operator==(const Set& other) const {
        ListNode* curr1 = head;
        ListNode* curr2 = other.head;
        
        while (curr1 != nullptr && curr2 != nullptr) {
            if (curr1->digit != curr2->digit) {
                return false;
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        
        return curr1 == nullptr && curr2 == nullptr;
    }
    
    bool operator!=(const Set& other) const {
        return !(*this == other);
    }
    
    bool contains(char c) const {
        return listContains(c);
    }
    
    void add(char c) {
        if (c >= '0' && c <= '9' && !listContains(c)) {
            head = new ListNode(c, head);
        }
    }
    
    void remove(char c) {
        ListNode* current = head;
        ListNode* prev = nullptr;
        
        while (current != nullptr) {
            if (current->digit == c) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }
    
    void show() const {
        if (head == nullptr) {
            std::cout << "пусто";
            return;
        }
        
        // Создаем временный массив для сортированного вывода
        char temp[UNIVERSAL_SIZE + 1];
        int index = 0;
        
        ListNode* current = head;
        while (current != nullptr) {
            temp[index++] = current->digit;
            current = current->next;
        }
        temp[index] = '\0';
        
        // Сортируем для вывода
        for (int i = 0; i < index - 1; ++i) {
            for (int j = 0; j < index - i - 1; ++j) {
                if (temp[j] > temp[j + 1]) {
                    char t = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = t;
                }
            }
        }
        
        std::cout << temp;
    }
    
    void Show() const {
        std::cout << "Set " << tag << " = [";
        show();
        std::cout << "]";
    }
    
    int power() const {
        int count = 0;
        ListNode* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
    
    void getElements(char* str) const {
        int index = 0;
        
        // Сначала собираем все элементы
        ListNode* current = head;
        while (current != nullptr) {
            str[index++] = current->digit;
            current = current->next;
        }
        str[index] = '\0';
        
        // Сортируем результат
        for (int i = 0; i < index - 1; ++i) {
            for (int j = 0; j < index - i - 1; ++j) {
                if (str[j] > str[j + 1]) {
                    char temp = str[j];
                    str[j] = str[j + 1];
                    str[j + 1] = temp;
                }
            }
        }
    }
    
    unsigned int getBits() const {
        unsigned int bits = 0;
        ListNode* current = head;
        while (current != nullptr) {
            int pos = current->digit - '0';
            bits |= (1u << pos);
            current = current->next;
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

int Set::object_count = 0;
bool Set::debug = true;

// Вспомогательные функции для работы с внешними списками (Node)
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

#endif // SET_LIST_H