#ifndef BPLUSTREE_H
#define BPLUSTREE_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "item.h" // Include the header file for the Item class

using namespace std;

class BPlusTree {

public:
    // Forward declaration of the Node class
    class Node;
    
private:
    int degree;
    Node* root;

public:
    // Define the Node class as a nested class within BPlusTree
    class Node {
    public:
        vector<Item> items;
        vector<Node*> children;
        bool is_leaf;

        Node(bool leaf);
    };

    BPlusTree(int degree);
    void print() const;
    void printNode(Node* node) const;
    void insert(Item item);
    Node* getRoot();
    void insertHelper(Node* node, Item item);
    void splitLeafNode(Node* node);
    void insertParentNode(Node* node, Item item, Node* child);
    void splitParentNode(Node* node);
    Node* findParent(Node* currentNode, Node* childNode);
};

#endif
