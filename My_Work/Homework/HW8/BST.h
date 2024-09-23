class BST {
private:
    class Node {
    public:
        int Key;
        Node* left;
        Node* right;

        Node(int key) : Key(key), left(nullptr), right(nullptr) {}
    };

    Node* root;
    void AddLeafPrivate (int Key , Node* Ptr);

public:
    BST();
    Node* CreateLeaf(int Key);
    void AddLeaf (int Key);
};
