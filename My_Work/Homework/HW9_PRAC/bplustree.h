#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Item {
    std::string title;
    double average_rating;
    int rating_number;
    std::string thumb_url;
    double price;

    Item(const std::string& t, double ar, int rn, const std::string& tu, double p);
};

// Node structure for B+ tree
struct Node {
    vector<double> keys;
    vector<Node*> children;
    bool isLeaf;
    vector<Item*> items;

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

    // Function to search for an item by name
    Item* search(double price);

    // Function to insert an item
    void insert(Item* item);

    void printTree();

    Node* getRoot();


private:
    // Helper function for searching
    Item* searchHelper(Node* node, double price);

    // Helper function to split a child
    void splitChild(Node* parent, int index);

    // Helper function to insert into a non-full node
    void insertNonFull(Node* node, Item* item);
    
     void printHelper(Node* node);

};

#endif // BPLUSTREE_H
