#include <iostream>
#include <cmath>

template<typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;
};

template<typename T>
void PushBack(Node<T>*& head, Node<T>* newNode) {
    if (head == nullptr) {
        head = newNode;
    } else {
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

template<typename T>
void PrintList(Node<T>* head) {
    Node<T>* temp = head;
    while (temp != nullptr) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

int main() {
    // Part 1: test Node<int> class.
    // Initialize an empty linked list, consisting of Node<int> nodes.
    Node<int>* headA = nullptr;

    // Create nodes and add them to the end of the list using PushBack
    for (int i = 1; i <= 5; ++i) {
        Node<int>* newNode = new Node<int>;
        // data of Node<int> is an int type.
        newNode->data = i;
        newNode->next = nullptr;
        newNode->prev = nullptr;

        // Add the node to the end of the list
        PushBack(headA, newNode);
    }

    // Print the linked list to verify the nodes
    std::cout << "Linked List of Node<int> nodes: ";
    PrintList(headA);

    // Clean up memory (free nodes)
    Node<int>* currentA = headA;
    while (currentA != nullptr) {
        Node<int>* next = currentA->next;
        delete currentA;
        currentA = next;
    }

    // Part 2: test Node<double> class.
    // Initialize an empty linked list, consisting of Node<double> nodes.
    Node<double>* headB = nullptr;

    // Create nodes and add them to the end of the list using PushBack
    for (int i = 1; i <= 5; ++i) {
        Node<double>* newNode = new Node<double>;
        // data of Node<double> is a double type.
        newNode->data = sqrt(i);
        newNode->next = nullptr;
        newNode->prev = nullptr;

        // Add the node to the end of the list
        PushBack(headB, newNode);
    }

    // Print the linked list to verify the nodes
    std::cout << "Linked List of Node<double> nodes: ";
    PrintList(headB);

    // Clean up memory (free nodes)
    Node<double>* currentB = headB;
    while (currentB != nullptr) {
        Node<double>* next = currentB->next;
        delete currentB;
        currentB = next;
    }

    return 0;
}

