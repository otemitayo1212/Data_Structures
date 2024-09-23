#include <iostream>
#include <cstdlib>
#include "BST.h"
using namespace std;

BST::BST() {
    root = nullptr; // Initialize root to nullptr
}

BST::Node* BST::CreateLeaf(int Key) {
    return new Node(Key); // Create a new node with the given key
}

void BST::AddLeaf(int Key) {
    // Call the AddLeafPrivate function
    AddLeafPrivate(Key, root);
}

void BST::AddLeafPrivate(int Key, Node* ptr) { // assuming this pointer is pointing to the current value
    if (root == nullptr) {  // If there is no node in this branch, create a leaf
        root = CreateLeaf(Key);
    } else if (Key < ptr->Key) {
        if (ptr->left != nullptr) {   // Go down to find
        AddLeafPrivate(Key, ptr->left);   
        } else{
            ptr->left = CreateLeaf(Key);
        }
    }else if (Key > ptr->Key) {
        if (ptr->right != nullptr) {   // Go down to find
        AddLeafPrivate(Key, ptr->right);   
        } else{
            ptr->right = CreateLeaf(Key);
        }
    }  else {
        cout <<"kEY" << Key  << " already exists in Tree."<< endl;
    }
}
