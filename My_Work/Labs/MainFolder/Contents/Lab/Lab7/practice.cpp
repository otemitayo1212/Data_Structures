#include<iostream>

template < class T>
class Node {
    public:
    T value;
    Node<T>* Next;
    


    Node(T val) : value(val), Next(nullptr) {}
};

template < class T>
Node<T>* mergeSort(Node<T>* head_A, Node<T>* head_B) {
    Node<T>* sorted = nullptr;
    Node<T>* tail = nullptr;
    Node<T>* current_A = head_A;
    Node<T>* current_B = head_B;

    while (current_A != nullptr && current_B != nullptr) {
        if (current_A->value <= current_B->value) {
            if (sorted == nullptr) {
                sorted = current_A;
                tail = current_A;
            } else {
                tail->Next = current_A;
                tail = current_A;
            }
            current_A = current_A->Next;
        } else {
            if (sorted == nullptr) {
                sorted = current_B;
                tail = current_B;
            } else {
                tail->Next = current_B;
                tail = current_B;
            }
            current_B = current_B->Next;
        }
    }

    while (current_A != nullptr) {
    tail->Next = current_A;
    tail = current_A;
    current_A = current_A->Next;

}

while (current_B != nullptr) {
    tail->Next = current_B;
    tail = current_B;
    current_B = current_B->Next;
}
    return sorted;

}

template < class T>
void printList(Node<T>* head) {
    Node<T>* current = head;
    while (current != nullptr) {
        std::cout << current->value << " ";
        current = current->Next;
    }
    std::cout << std::endl;
}
template<typename T>
void PushBack(Node<T>*& head, Node<T>* newNode) {

    if (head == nullptr){
        head  = newNode;
    }else {
         Node<T>* current = nullptr;
         while (current -> Next != nullptr){
            current = current -> Next;
         }
         current-> Next = newNode;


    }
}
int main() {
    // Create two sorted linked lists
    Node<int>* head_A = new Node<int>(1);
    head_A->Next = new Node<int>(3);
    head_A->Next->  Next = new Node<int>(5);

    Node<int>* head_B = new Node<int>(2);
    head_B->Next = new Node<int>(4);
    head_B->Next->Next = new Node<int>(6);

    std::cout << "Original list A: ";
    printList(head_A);

    std::cout << "Original list B: ";
    printList(head_B);

    // Merge the lists
    Node<int>* mergedList = mergeSort(head_A, head_B);

    std::cout << "Merged and sorted list: ";
    printList(mergedList);

    // Clean up memory
    Node<int>* temp;
    while (mergedList != nullptr) {
        temp = mergedList;
        mergedList = mergedList->Next;
        delete temp;
    }

    return 0;
}

