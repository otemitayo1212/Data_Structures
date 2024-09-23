#include "bplustree.h"

// Node Constructor
Node::Node(bool isLeaf) : isLeaf(isLeaf) {}

// Node Destructor

 Node::~Node() {
    for (Node* child : children)
        delete child;
    for (Item* item : items)
        delete item;
}

// Constructor definition
Item::Item(const std::string& t, double ar, int rn, const std::string& tu, double p)
    : title(t), average_rating(ar), rating_number(rn), thumb_url(tu), price(p) {}

// B+ Tree Constructor
BPlusTree::BPlusTree(int order) : root(nullptr), order(order) {}

// B+ Tree Destructor
BPlusTree::~BPlusTree() {
    delete root;
}

// Function to search for an item by name
Item* BPlusTree::search(double price) {
    return searchHelper(root, price);
}

Node* BPlusTree::getRoot() {
    return root;
}
// Helper function for searching
Item* BPlusTree::searchHelper(Node* node, double price) {
    if (node == nullptr)
        return nullptr;

    int i = 0;
    while (i < node->items.size() && price > node->items[i]->price)
        i++;

    if (i < node->items.size() && price == node->items[i]->price)
        return node->items[i];
    else if (node->isLeaf)
        return nullptr;
    else
        return searchHelper(node->children[i], price);
}

// Function to insert an item
void BPlusTree::insert(Item* item) {
    if (root == nullptr) {
        root = new Node(true);
        root->items.push_back(item);
        return;
    }

    insertNonFull(root, item);

    // Split root if necessary
    if (root->keys.size() == order) {
        Node* newRoot = new Node(false);
        newRoot->children.push_back(root);
        splitChild(newRoot, 0);
        root = newRoot;
    }
}

// Helper function to split a child
void BPlusTree::splitChild(Node* parent, int index) {
    Node* child = parent->children[index];
    Node* newChild = new Node(child->isLeaf);
    int mid = child->keys.size() / 2;

    // Move keys to new child
    newChild->keys.assign(child->keys.begin() + mid, child->keys.end());
    child->keys.erase(child->keys.begin() + mid);

    // Move children to new child (if not leaf)
    if (!child->isLeaf) {
        newChild->children.assign(child->children.begin() + mid, child->children.end());
        child->children.erase(child->children.begin() + mid);
    }

    // Move items to new child
    newChild->items.assign(child->items.begin() + mid, child->items.end());
    child->items.erase(child->items.begin() + mid);

    // Insert newChild into parent
    parent->keys.insert(parent->keys.begin() + index, newChild->keys[0]);
    parent->children.insert(parent->children.begin() + index + 1, newChild);

    // Update keys in child
    child->keys.resize(mid);
}

// Helper function to insert into a non-full node
void BPlusTree::insertNonFull(Node* node, Item* item) {
    int i = node->items.size() - 1;

    if (node->isLeaf) {
        node->items.push_back(item);
        sort(node->items.begin(), node->items.end(), [](const Item* a, const Item* b) {
            return a->price < b->price;
        });
    } else {
        while (i >= 0 && item->price < node->items[i]->price)
            i--;

        i++;

        if (node->children[i]->keys.size() == order) {
            splitChild(node, i);

            if (item->price > node->items[i]->price)
                i++;
        }

        insertNonFull(node->children[i], item);
    }
}
// Function to print the whole tree
void BPlusTree::printTree() {
    printHelper(root);
}

// Helper function to print the tree
void BPlusTree::printHelper(Node* node) {
    if (node == nullptr)
        return;

    for (int i = 0; i < node->items.size(); i++) {
        cout << "Name: " << node->items[i]->price << ", Price: " << node->items[i]->price << ", Rating: " << node->items[i]->average_rating << endl;
    }

    if (!node->isLeaf) {
        for (int i = 0; i < node->children.size(); i++) {
            printHelper(node->children[i]);
        }
    }
}