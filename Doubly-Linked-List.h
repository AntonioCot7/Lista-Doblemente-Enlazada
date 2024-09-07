#ifndef LISTA_DOBLEMENTE_ENLAZADA_DOUBLY_LINKED_LIST_H
#define LISTA_DOBLEMENTE_ENLAZADA_DOUBLY_LINKED_LIST_H

#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

template <typename T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;
    int list_size;

public:
    List() : head(nullptr), tail(nullptr), list_size(0) {}

    ~List() {
        clear();
    }

    T front() {
        if (head) return head->data;
        throw std::out_of_range("The list is empty");
    }

    T back() {
        if (tail) return tail->data;
        throw std::out_of_range("The list is empty");
    }

    void push_front(T val) {
        Node<T>* new_node = new Node<T>(val);
        if (!head) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        ++list_size;
    }

    void push_back(T val) {
        Node<T>* new_node = new Node<T>(val);
        if (!tail) {
            head = tail = new_node;
        } else {
            new_node->prev = tail;
            tail->next = new_node;
            tail = new_node;
        }
        ++list_size;
    }

    void pop_front() {
        if (!head) throw std::out_of_range("The list is empty");
        Node<T>* temp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        --list_size;
    }

    void pop_back() {
        if (!tail) throw std::out_of_range("The list is empty");
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        --list_size;
    }

    void insert(int pos, T val) {
        if (pos < 0 || pos > list_size) throw std::out_of_range("The list is empty");
        if (pos == 0) {
            push_front(val);
            return;
        }
        if (pos == list_size) {
            push_back(val);
            return;
        }

        Node<T>* new_node = new Node<T>(val);
        Node<T>* temp = head;

        for (int i = 0; i < pos - 1; ++i) {
            temp = temp->next;
        }

        new_node->next = temp->next;
        new_node->prev = temp;
        temp->next->prev = new_node;
        temp->next = new_node;

        ++list_size;
    }

    void remove(int pos) {
        if (pos < 0 || pos >= list_size) throw std::out_of_range("Invalid position");
        if (pos == 0) {
            pop_front();
            return;
        }
        if (pos == list_size - 1) {
            pop_back();
            return;
        }

        Node<T>* temp = head;
        for (int i = 0; i < pos; ++i) {
            temp = temp->next;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;

        --list_size;
    }

    T operator[](int pos) {
        if (pos < 0 || pos >= list_size) throw std::out_of_range("Invalid position");

        Node<T>* temp = head;
        for (int i = 0; i < pos; ++i) {
            temp = temp->next;
        }
        return temp->data;
    }

    bool empty() {
        return list_size == 0;
    }

    int size() {
        return list_size;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void reverse() {
        Node<T>* current = head;
        Node<T>* temp = nullptr;
        while (current) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        if (temp) {
            head = temp->prev;
        }
    }
};

#endif //LISTA_DOBLEMENTE_ENLAZADA_DOUBLY_LINKED_LIST_H
