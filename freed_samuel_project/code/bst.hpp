#include <iostream>

using namespace std;

struct BSTNode {
    int key;
    BSTNode * left;
    BSTNode * right;
};

class BST{
    private:
        BSTNode * root;
    
    public:
        BST() {
            root = NULL;
        }
        void insert(int key);
        BSTNode * search(int key);
        void display();
};