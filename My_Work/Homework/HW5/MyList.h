#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <list>
#include <string>
#include<fstream>
#include "MyList.h"

#include <iostream>



template <typename T>
class MyList {
public:
    class Node {
public:
    T data;
    Node* next;

    Node(const T& data) : data(data), next(nullptr) {}
};

    Node* head;
    Node* tail; // Add tail pointer to track the last node
    size_t size;

public:
    MyList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }


    void push_front(const T& data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        ++size;
    }

    void push_back(const T& data) {
        Node* newNode = new Node(data);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
    }

    void pop_front() {
        if (head == nullptr)
            return;
        Node* temp = head;
        head = head->next;
        delete temp;
        --size;
        if (head == nullptr)
            tail = nullptr;
    }

    void pop_back() {
        if (head == nullptr)
            return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
            --size;
            return;
        }
        Node* current = head;
        while (current->next != tail) {
            current = current->next;
        }
        delete tail;
        tail = current;
        tail->next = nullptr;
        --size;
    }

    size_t getSize() const {
        return size;
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

#endif // MYLIST_H

