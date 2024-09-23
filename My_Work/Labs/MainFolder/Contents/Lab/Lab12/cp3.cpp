#include <iostream>
#include <vector>

// Node structure for linked list
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// Hash table implementation using separate chaining
class HashTable {
private:
    static const int TABLE_SIZE = 4; // Choose a suitable size
    Node* table[TABLE_SIZE];

    // Hash function to map values to indices
    int hash(int key) {
        return abs(key % TABLE_SIZE);
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
            current->next = newNode;
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

int longestConsecutive(std::vector<int>& nums) {
    HashTable table;
    // Insert all elements into the hash table
    // find the value - 1 if the value - 1 is in the 
    // Iterate through the hash table and find the longest consecutive sequence
    std::vector< int> maxs ;

    for (int num : nums) { 
        table.insert(num);
    }
    

    int max_length = 1;
    for (int num : nums){
        if (!table.contains(num - 1)){
            // max_length += 2;
            while (table.contains(num + 1)){
                max_length++;
                num++;
            }
            maxs.push_back(max_length);
            max_length = 1;
        }
    }
    // get the maximum in the vector
   max_length = *std::max_element(maxs.begin(), maxs.end());
    return max_length;
}

int main() {
    //std::vector<int> nums = {100, 4, 200, 1, 3, 2};
    //std::vector<int> nums = {0,3,7,2,5,8,4,6,0,1};
    //std::vector<int> nums = {100, 4, 200, 1, 3, 2, 5, 6};
	// std::vector<int> nums = {0,3,7,2,5,8,4,6,0,1};
	std::vector<int> nums = {100, 4, 200, 201, 202, 203, 205, 204, 1, 3, 2};
	//std::vector<int> nums = {-3,0,1,2,3,-2,-1,-5};
    int size = nums.size();
    std::cout << "For vector {";
    for(int i=0; i<size-1; i++) {
        std::cout << nums[i] << ",";
    }
    std::cout << nums[size-1] << "}:" << std::endl;
    int length = longestConsecutive(nums);
    std::cout << "The length of the longest consecutive sequence is: " << length << std::endl;
    return 0;
}
