#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Object representing a data entry in the B+ tree
struct Entry {
    int key; // The key for sorting
    // Other data associated with the key

    Entry(int key) : key(key) {}
};

// Node structure for B+ tree
struct Node {
    vector<Entry*> keys;
    vector<Node*> children;
    bool isLeaf;

    // Constructor
    Node(bool isLeaf);

    // Destructor
    ~Node();
};

// B+ Tree class
class BPlusTree {
private:
    Node* root;
    int order; // Order of B+ tree

public:
    // Constructor
    BPlusTree(int order);

    // Destructor
    ~BPlusTree();

    // Function to search for a key
    bool search(int key);

    // Function to insert an item
    void insert(Entry* item);

    // Function to print the whole tree
    void printTree();
    // Function to get the root
    Node* getRoot();

private:
    // Helper function for searching
    bool searchHelper(Node* node, int key);

    // Helper function to split a child
    void splitChild(Node* parent, int index);

    // Helper function to insert into a non-full node
    void insertNonFull(Node* node, Entry* item);

    // Helper function to print the tree
    void printHelper(Node* node);
};

// Node Constructor
Node::Node(bool isLeaf) : isLeaf(isLeaf) {}

// Node Destructor
Node::~Node() {
    for (auto child : children)
        delete child;
}

// B+ Tree Constructor
BPlusTree::BPlusTree(int order) : root(nullptr), order(order) {}

// B+ Tree Destructor
BPlusTree::~BPlusTree() {
    delete root;
}

// Function to search for a key
bool BPlusTree::search(int key) {
    return searchHelper(root, key);
}

Node* BPlusTree::getRoot() {
    return root;
}

// Helper function for searching
bool BPlusTree::searchHelper(Node* node, int key) {
    if (node == nullptr)
        return false;

    int i = 0;
    while (i < node->keys.size() && key > node->keys[i]->key)
        i++;

    if (i < node->keys.size() && key == node->keys[i]->key)
        return true;
    else if (node->isLeaf)
        return false;
    else
        return searchHelper(node->children[i], key);
}

// Function to insert an item
void BPlusTree::insert(Entry* item) {
    if (root == nullptr) {
        root = new Node(true);
        root->keys.push_back(item);
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
    for (int i = mid; i < child->keys.size(); ++i) {
        newChild->keys.push_back(child->keys[i]);
    }
    child->keys.erase(child->keys.begin() + mid, child->keys.end());

    // Move children to new child (if not leaf)
    if (!child->isLeaf) {
        for (int i = mid; i < child->children.size(); ++i) {
            newChild->children.push_back(child->children[i]);
        }
        child->children.erase(child->children.begin() + mid, child->children.end());
    }

    // Insert newChild into parent
    parent->keys.insert(parent->keys.begin() + index, newChild->keys[0]);
    parent->children.insert(parent->children.begin() + index + 1, newChild);

    // Update keys in child
    child->keys.resize(mid);
}

// Helper function to insert into a non-full node
void BPlusTree::insertNonFull(Node* node, Entry* item) {
    int i = node->keys.size() - 1;

    if (node->isLeaf) {
        node->keys.push_back(item);
        sort(node->keys.begin(), node->keys.end(), [](Entry* a, Entry* b) { return a->key < b->key; });
    } else {
        while (i >= 0 && item->key < node->keys[i]->key)
            i--;

        i++;

        if (node->children[i]->keys.size() == order) {
            splitChild(node, i);

            if (item->key > node->keys[i]->key)
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

    for (int i = 0; i < node->keys.size(); i++) {
        cout << node->keys[i]->key << " ";
    }
    cout << endl;

    if (!node->isLeaf) {
        for (int i = 0; i < node->children.size(); i++) {
            printHelper(node->children[i]);
        }
    }
}
void rangeSearchHelper(Node* node, int minPrice, int maxPrice, vector<Entry*>& itemsInRange) {
    if (node == nullptr)
        return;

    // Traverse through the keys of the current node
    for (int i = 0; i < node->keys.size(); i++) {
        int key = node->keys[i]->key;
        if (key >= minPrice && key <= maxPrice) {
            itemsInRange.push_back(node->keys[i]);
        }
    }

    // If not a leaf node, recursively call rangeSearchHelper for children
    if (!node->isLeaf) {
        for (int i = 0; i < node->children.size(); i++) {
            rangeSearchHelper(node->children[i], minPrice, maxPrice, itemsInRange);
        }
    }
}
// Function to perform range search in the B+ tree
vector<Entry*> rangeSearch(BPlusTree& bPlusTree, int minPrice, int maxPrice) {
    vector<Entry*> itemsInRange;
    Node* current = bPlusTree.getRoot();
    
    // Recursive function to perform range search
    rangeSearchHelper(current, minPrice, maxPrice, itemsInRange);
    
    return itemsInRange;
}


int main() {
    BPlusTree bPlusTree(4); // Creating a BPlusTree object with order 4

    // Creating and inserting some items
    Entry* item1 = new Entry(10);
    Entry* item2 = new Entry(5);
    Entry* item3 = new Entry(20);
    Entry* item4 = new Entry(15);
    Entry* item5 = new Entry(25);
    Entry* item6 = new Entry(30);
    Entry* item7 = new Entry(50);

    // Inserting items into the tree
    bPlusTree.insert(item1);
    bPlusTree.insert(item2);
    bPlusTree.insert(item3);
    bPlusTree.insert(item4);
    bPlusTree.insert(item5);
    bPlusTree.insert(item6);
    bPlusTree.insert(item7);

    // Printing the tree
    cout << "B+ Tree:" << endl;
    bPlusTree.printTree();

    // Perform range search
    int minPrice = 10;
    int maxPrice = 30;
    vector<Entry*> itemsInRange = rangeSearch(bPlusTree, minPrice, maxPrice);

    // Print items within the range
    cout << "Items within the range [" << minPrice << ", " << maxPrice << "]:" << endl;
    for (Entry* entry : itemsInRange) {
        cout << entry->key << " ";
    }
    cout << endl;

    // Freeing memory
    delete item1;
    delete item2;
    delete item3;
    delete item4;
    delete item5;
    delete item6;
    delete item7;

    return 0;
}
