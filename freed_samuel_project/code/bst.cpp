#include "bst.hpp"

using namespace std;

BSTNode * insertHelper(BSTNode * root, BSTNode * add){
    
    // Replacement of leaf with new node
    if(!root) return add;

    // Move to the right
    if(root->key < add->key) {
        root->right = insertHelper(root->right,add);
        return root;
    }

    // Move to the left
    if(root->key > add->key) {
        root->left = insertHelper(root->left,add);
        return root;
    }

    // Base case
    return NULL;
}

void BST::insert(int key){
   
    // Create new node
    BSTNode * add = new BSTNode;
    add->key = key;
    add->left = NULL;
    add->right = NULL;

    // Use insertHelper to add node in proper location
    root = insertHelper(root, add);
}

BSTNode * searchHelper(BSTNode * root, int key){

    // Base case
    if(!root) return NULL;

    // If found, return address
    if(root->key == key) return root;

    // Else recursive call right and left
    if(root->key < key) return searchHelper(root->right,key);
    if(root->key > key) return searchHelper(root->left,key);

    // Base case
    return NULL;
}

BSTNode * BST::search(int key){

    // Call searchHelper to start at root
    return searchHelper(root,key);
}

void displayHelper(BSTNode * node){

    // Inorder recursive print
    if(node) {
        displayHelper(node->left);
        cout << " " << node->key;
        displayHelper(node->right);
    }
}

void BST::display(){

    // Call displayHelper to start at root
    displayHelper(root);
    cout << endl;
}