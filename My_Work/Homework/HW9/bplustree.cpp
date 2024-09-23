#include "bplustree.h"

// Define the constructor for the Node class
BPlusTree::Node::Node(bool leaf) : is_leaf(leaf) {}

// Define the constructor for the BPlusTree class
BPlusTree::BPlusTree(int degree) : degree(degree), root(nullptr) {}

// Function to print the B+ tree
void BPlusTree::print() const {
    printNode(root);
}

// Helper function to recursively print nodes of the B+ tree
void BPlusTree::printNode(Node* node) const {
    if (node == nullptr)
        return;

    if (node->is_leaf) {
        for (const auto& item : node->items) {
            std::cout << "(" << item.name << ", " << item.price << ", " << item.rating << ") ";
        }
        std::cout << std::endl;
    } else {
        for (int i = 0; i < node->items.size(); ++i) {
            printNode(node->children[i]);
            std::cout << "(" << node->items[i].name << ", " << node->items[i].price << ", " << node->items[i].rating << ") ";
        }
        printNode(node->children.back());
        std::cout << std::endl;
    }
}

// Function to insert an item into the B+ tree
void BPlusTree::insert(Item item) {
    if (root == nullptr) {
        root = new Node(true);
        root->items.push_back(item);
    } else {
        insertHelper(root, item);
    }
}

BPlusTree::Node* BPlusTree::getRoot() {
    return root;
}



void BPlusTree::insertHelper(Node* node, Item item) {
    // Implementation of insertHelper function
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

void BPlusTree::splitLeafNode(Node* node) {
    // Implementation of splitLeafNode function
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

void BPlusTree::insertParentNode(Node* node, Item item, Node* child) {
    // Implementation of insertParentNode function
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

void BPlusTree::splitParentNode(Node* node) {
    // Implementation of splitParentNode function
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
BPlusTree::Node* BPlusTree::findParent(Node* currentNode, Node* childNode) {
    // Implementation of findParent function
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



