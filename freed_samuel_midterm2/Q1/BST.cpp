#include <iostream>
#include "BST.hpp"
using namespace std;
#define COUNT 10

/*
PUBLIC METHODS:
*/

// Constructor definitions:
// Default:
BST::BST(){
    root = nullptr;
}

void BST::addNode(int data){
    root = addNodeHelper(root, data);
    cout<<data<<" has been added"<<endl;
}

void BST::print2DUtil(int space)
{
    print2DUtilHelper(root, space);
}

/*
PRIVATE METHODS:
*/


//  TODO:
//  Write a function decrementLeaves that goes through a Binary Search Tree 
//  and subtracts 1 from each of the leaf nodes. Feel free to implement an 
//  additional helper function.
void decrementLeaves(Node* root){
    // Base case in case nullptr is ever received
    if(!root) return;
    // Checking if leaf node - by definition, leaf nodes must have no children,
    // meaning both child pointers are nullptr
    if(!root->left && !root->right) {
        // Decrement
        root->key--;
        // Case where right node is < parent, which is the only possible malfunction with the right node.
        // Assuming the addNode function is operating correctly, decrementing a left child
        // will always result in a valid BST since the left child should always be less than
        // the parent.
        if(root->key < root->parent->key && root == root->parent->right) {       
            // Adjustment of parent's pointer to avoid segfault                     
            root->parent->right = nullptr;
            // Deletion of offending node
            delete root;
        }
        return;
    }
    // If current node has any children, recursive call starting from each child (pre-order)
    else {
        decrementLeaves(root->left);
        decrementLeaves(root->right);
    }
}

// I had just finished this when I was informed that this was not required.
// I would love any feedback on it regardless!
void leftCheck(Node * root){
    // Base case
    if(!root) return;
    // Checking if leaf
    if(!root->left && !root->right) {
        Node * scan = root->parent->parent;
        // If the left node of any right child is less than any of its grandparents, it must be deleted.
        while(scan) {
            if(root->key < scan->key) {
                root->parent->left = nullptr;
                delete root;
                break;
            }
            scan = scan->parent;
        }
        return;
    }
    else {
        leftCheck(root->left);
        leftCheck(root->right);
    }
}

void BST::decrement(){
    decrementLeaves(root);
    leftCheck(root->right);
}  


//   This function will add the data in the tree rooted at currNode.
//   Call this function from insert().


Node* BST:: addNodeHelper(Node* currNode, int data){
    if(currNode == nullptr){
       return createNode(data);      
    }
    else if(currNode->key < data){
        currNode->right = addNodeHelper(currNode->right,data);
        currNode->right->parent = currNode;
    }
    else if(currNode->key > data){
        currNode->left = addNodeHelper(currNode->left,data);
        currNode->left->parent = currNode;
    }
    return currNode;
}


// Create a new node, setting key value to  input data
// and all pointers to null.
Node* BST:: createNode(int data){
    Node* newNode = new Node;
    newNode->key = data;
    newNode->parent = nullptr;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* BST::getRoot(){
    return root;
}


/*
   Prints a binary tree in a 2D fashion.
Note: The image of the tree is left rotated by 90 degrees.
*/
void BST::print2DUtilHelper(Node *currNode, int space){
    // Base case
    if (currNode == nullptr)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtilHelper(currNode->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", currNode->key);

    // Process left child
    print2DUtilHelper(currNode->left, space);
}





