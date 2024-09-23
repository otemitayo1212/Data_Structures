#include <iostream>

// Node structure for linked list
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Hash table implementation using separate chaining
class HashTable {
private:
    static const int TABLE_SIZE = 10; // Choose a suitable size
    Node* table[TABLE_SIZE];

    // Hash function to map values to indices
    int hash(int key) {
        return key % TABLE_SIZE;
    }

public:
    HashTable() {
        // Initialize all slots with nullptr
        for (int i = 0; i < TABLE_SIZE; ++i)
            table[i] = nullptr;
    }

    // Insert a value into the hash table
    void insert(int key) {
        int index = hash(key);
        Node* newNode = new Node(key);
        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            Node* current = table[index];
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;  // place it in the nodes
        }
    }

    // Check if a value exists in the hash table
    bool contains(int key) {
        int index = hash(key);
        Node* current = table[index];
        while (current != nullptr) {
            if (current->data == key)
                return true;
            current = current->next;
        }
        return false;
    }
};

bool isGood(int n) {
    HashTable seen;
    while (n != 1 && !seen.contains(n)) {
        seen.insert(n);
        int sum = 0;
        while (n > 0) {
            int digit = n % 10;
            sum += digit * digit;
            n /= 10;
        }
        n = sum;
    }
    return n == 1;
}

int main() {
    // Test cases
    // 2, 4, 5, 6, 17, 18, 20 are not good numbers.
    // 1, 7, 10, 13, 19, 23, 28, 68 are good numbers.

    int testCases[] = {2,4,5,6,17,18,20,1,7,10,13,19,23,28,68};

    for (int n : testCases) {
        if (isGood(n)) {
            std::cout << n << " is a good number." << std::endl;
        } else {
            std::cout << n << " is not a good number." << std::endl;
        }
    }

    return 0;
}
