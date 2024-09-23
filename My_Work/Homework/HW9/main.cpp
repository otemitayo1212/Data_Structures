#include "bplustree.h"
#include "item.h"
#include <iostream>
#include <vector>
#include <stack> // Include the header file for stack
#include <algorithm>

using namespace std;

// Comparator struct for sorting items based on rating, price, and title
struct CompareItems {
    // currently prioritizeing ratings
    bool operator() (const Item& a, const Item& b) {
        if (a.rating != b.rating)
            return a.rating < b.rating;
        if (a.price != b.price)
            return a.price < b.price;
        return a.name < b.name;
    }
};

// Helper function to traverse the B+ tree and add items within the price range to the result vector
void traverseTree(BPlusTree& bptree, double minPrice, double maxPrice, vector<Item>& result) {
    BPlusTree::Node* root = bptree.getRoot();
    if (root == nullptr)
        return;

    // Stack for iterative traversal
    stack<BPlusTree::Node*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        BPlusTree::Node* currentNode = nodeStack.top();
        nodeStack.pop();

        if (currentNode->is_leaf) {
            for (const auto& item : currentNode->items) {
                if (item.price >= minPrice && item.price <= maxPrice) {
                    result.push_back(item);
                }
            }
        } else {
            // Traverse children and push them onto the stack
            for (size_t i = 0; i < currentNode->children.size(); ++i) {
                if (i == 0 || currentNode->items[i - 1].price > minPrice)
                    nodeStack.push(currentNode->children[i]);
                if (i == currentNode->children.size() - 1 || currentNode->items[i].price < maxPrice)
                    nodeStack.push(currentNode->children[i + 1]);
            }
        }
    }
}

// Function to perform range search and sort items
vector<Item> rangeSearchAndSort(BPlusTree& bptree, double minPrice, double maxPrice) {
    vector<Item> result;
    traverseTree(bptree, minPrice, maxPrice, result);
    // Sort the items according to the provided criteria
    sort(result.begin(), result.end(), CompareItems());
    return result;
}

int main() {

   BPlusTree bptree(13); // Degree of B+ tree is 4

    // Insert some items into the B+ tree
    bptree.insert(Item("Laptop", 999.99, 4.5));
    bptree.insert(Item("Smartphone", 799.99, 4.7));
    bptree.insert(Item("Tablet", 299.99, 4.0));
    bptree.insert(Item("Smartwatch", 199.99, 4.2));

    // Additional test cases
    bptree.insert(Item("Desktop", 1499.99, 4.6));
    bptree.insert(Item("Headphones", 99.99, 4.3));
    bptree.insert(Item("Camera", 499.99, 4.8));
    bptree.insert(Item("Printer", 299.99, 4.1));
    bptree.insert(Item("Monitor", 399.99, 4.5));
    bptree.insert(Item("Keyboard", 49.99, 4.0));
    bptree.insert(Item("Mouse", 29.99, 4.2));
    bptree.insert(Item("Speakers", 149.99, 4.4));
    bptree.insert(Item("Router", 79.99, 4.6));

    // Print the B+ tree
    cout << "B+ Tree after insertion:" << endl;
    bptree.print();

    // Define the price range
    double minPrice = 0.0;
    double maxPrice = 10000.0;

    // Perform range search and sort items
    vector<Item> result = rangeSearchAndSort(bptree, minPrice, maxPrice);

    // Display the sorted items
    cout << "Items in the price range $" << minPrice << " - $" << maxPrice << ":" << endl;
    for (const Item& item : result) {
        cout << "Name: " << item.name << ", Price: $" << item.price << ", Rating: " << item.rating << endl;
    }

    return 0;
}
