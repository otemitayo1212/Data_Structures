#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Define a class to represent an item
class Item {
public:
    string name;
    double price;
    double rating;

    Item(string n, double p, double r) : name(n), price(p), rating(r) {}
};

// Define a class to represent a B+ tree node
class Node {
public:
    vector<Item> items;
    vector<Node*> children;
    bool is_leaf;

    Node(bool leaf) : is_leaf(leaf) {}
};

class BPlusTree {
private:
    int degree; // Degree of B+ tree
    Node* root; // Pointer to the root of the B+ tree

public:
    BPlusTree(int degree) : degree(degree), root(nullptr) {}

    // Function to insert an item into the B+ tree
    void insert(Item item) {
        if (root == nullptr) {
            root = new Node(true);
            root->items.push_back(item);
        } else {
            insertHelper(root, item);
        }
    }

    // Helper function to recursively insert an item into the B+ tree
    void insertHelper(Node* node, Item item) {
        if (node->is_leaf) {
            // Insert item into leaf node
            node->items.push_back(item);
            // Sort items based on price or any other criteria
            // Here, we're sorting based on price
            sort(node->items.begin(), node->items.end(), [](const Item& a, const Item& b) {
                return a.price < b.price;
            });

            // Split the leaf node if it exceeds the degree
            if (node->items.size() > degree) {
                splitLeafNode(node);
            }
        } else {
            // Find appropriate child node to insert into
            int i = 0;
            while (i < node->items.size() && item.price > node->items[i].price) {
                i++;
            }
            insertHelper(node->children[i], item);
        }
    }

    // Function to split a leaf node when it exceeds the degree
    void splitLeafNode(Node* node) {
        Node* newNode = new Node(true);
        int mid = node->items.size() / 2;
        for (int i = mid; i < node->items.size(); i++) {
            newNode->items.push_back(node->items[i]);
        }
        node->items.erase(node->items.begin() + mid, node->items.end());

        // Adjust pointers
        newNode->children.push_back(node->children.back());
        node->children.back() = newNode;

        // Split the parent node if necessary
        if (node == root) {
            Node* newRoot = new Node(false);
            newRoot->items.push_back(newNode->items[0]);
            newRoot->children.push_back(node);
            newRoot->children.push_back(newNode);
            root = newRoot;
        } else {
            insertParentNode(node, newNode->items[0], newNode);
        }
    }

    // Helper function to insert a new parent node
    void insertParentNode(Node* node, Item item, Node* child) {
        Node* parent = findParent(root, node);
        parent->items.push_back(item);
        sort(parent->items.begin(), parent->items.end(), [](const Item& a, const Item& b) {
            return a.price < b.price;
        });

        // Adjust pointers
        int i = 0;
        while (i < parent->children.size() && parent->children[i] != node) {
            i++;
        }
        parent->children.insert(parent->children.begin() + i + 1, child);

        // Split the parent node if necessary
        if (parent->items.size() > degree) {
            splitParentNode(parent);
        }
    }

    // Function to split a parent node when it exceeds the degree
    void splitParentNode(Node* node) {
        Node* newNode = new Node(false);
        int mid = node->items.size() / 2;
        for (int i = mid + 1; i < node->items.size(); i++) {
            newNode->items.push_back(node->items[i]);
        }
        node->items.erase(node->items.begin() + mid, node->items.end());

        // Adjust pointers
        for (int i = mid + 1; i < node->children.size(); i++) {
            newNode->children.push_back(node->children[i]);
        }
        node->children.erase(node->children.begin() + mid + 1, node->children.end());

        // Split the parent recursively if necessary
        if (node == root) {
            Node* newRoot = new Node(false);
            newRoot->items.push_back(node->items.back());
            newRoot->children.push_back(node);
            newRoot->children.push_back(newNode);
            root = newRoot;
        } else {
            insertParentNode(node, node->items.back(), newNode);
        }
    }

    // Helper function to find the parent of a given node
    Node* findParent(Node* currentNode, Node* childNode) {
        if (currentNode->is_leaf || currentNode->children[0]->is_leaf) {
            return nullptr;
        }
        for (auto child : currentNode->children) {
            if (child == childNode) {
                return currentNode;
            }
            Node* result = findParent(child, childNode);
            if (result != nullptr) {
                return result;
            }
        }
        return nullptr;
    }
};

int main() {
    BPlusTree bptree(3); // Degree of B+ tree is 3

    // Insert some items into the B+ tree
    bptree.insert(Item("Laptop", 999.99, 4.5));
    bptree.insert(Item("Smartphone", 799.99, 4.7));
    bptree.insert(Item("Tablet", 299.99, 4.0));
    bptree.insert(Item("Smartwatch", 199.99, 4.2));

    return 0;
}
