#include <iostream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;

/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}

void deleteTree(TreeNode * root) {
    if(!root) return;
    deleteTree(root->leftChild);
    deleteTree(root->rightChild);
    LLMovieNode * del = root->head;
    LLMovieNode * temp;
    while(del) {
        temp = del->next;
        delete del;
        del = temp;
    }
    delete root;
    return;
}

MovieTree::~MovieTree()
{
    deleteTree(root);
}

void printHelper(TreeNode * t) {
    if(!t) return;
    printHelper(t->leftChild);
    cout << "Movies starting with letter: " << t->titleChar << endl;
    LLMovieNode * m = t->head;
    while(m) {
        cout << " >> " << m->title << " " << m->rating << endl;
        m = m->next;  
    }
    printHelper(t->rightChild);
}

void MovieTree::printMovieInventory()
{
    printHelper(root);
}

TreeNode * addTreeNode(TreeNode * root, TreeNode * node) {
    if(!root) return node;
    node->parent = root;
    if(root->titleChar < node->titleChar) {
        root->rightChild = addTreeNode(root->rightChild,node);
        return root;
    }
    if(root->titleChar > node->titleChar) {
        root->leftChild = addTreeNode(root->leftChild,node);
        return root;
    }
    return NULL;
}

void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
    TreeNode * add = searchChar(title[0]);
    LLMovieNode * n = new LLMovieNode(ranking,title,year,rating);
    if(!root) {
        add = new TreeNode;
        add->titleChar = title[0];
        root = add;
        add->head = n;
        return;
    }
    if(!add) {
        add = new TreeNode;
        add->titleChar = title[0];
        addTreeNode(root,add);
        add->head = n;
        return;
    }
    LLMovieNode * scan = add->head;
    LLMovieNode * scan2 = scan->next;
    if(title < scan->title) {
        n->next = scan;
        add->head = n;
        return;
    }
    while(scan2) {
        if(title < scan2->title) {
            n->next = scan2;
            scan->next = n;
            return;
        }
        scan = scan->next;
        scan2 = scan2->next;
    }
    n->next = NULL;
    scan->next = n;
    return;
}


void removeMovie(TreeNode *del, string title) {
    if (del->head->title == title) {
        LLMovieNode *old = del->head;
        if (!old->next) {
            del->head = NULL;
            delete old;
            return;
        }
        del->head = old->next;
        delete old;
        return;
    }
    else if (!del->head->next) {
        if (del->head->title == title) {
            delete del->head;
            del->head = NULL;
            return;
        }
        cout << "Movie: " << title << " not found, cannot delete." << endl;
        return;
    }
    else {
        LLMovieNode *curr, *prev;
        prev = del->head;
        curr = prev->next;
        while (curr && curr->title != title) {
            prev = curr;
            curr = curr->next;
        }
        if (!curr) {
            cout << "Movie: " << title << " not found, cannot delete." << endl;
            return;
        }
        prev->next = curr->next;
        delete curr;
        return;
    }
    return;
}

void adjustNode (TreeNode *curr) {
    if (!curr->leftChild && !curr->rightChild) {
        if (curr->parent->leftChild == curr) {
            curr->parent->leftChild = NULL;
            return;
        }
        curr->parent->rightChild = NULL;
        return;
    }
    else if (!curr->leftChild) {
        if (curr->parent->leftChild == curr) {
            curr->parent->leftChild = curr->rightChild;
            curr->rightChild->parent = curr->parent;
            return;
        }
        curr->parent->rightChild = curr->rightChild;
        curr->rightChild->parent = curr->parent;
        return;
    }
    else if (!curr->rightChild) {
        if (curr->parent->leftChild == curr) {
            curr->parent->leftChild = curr->leftChild;
            curr->leftChild->parent = curr->parent;
            return;
        }
        curr->parent->rightChild = curr->leftChild;
        curr->leftChild->parent = curr->parent;
        return;
    }
    TreeNode *del = curr->rightChild;
    while (del->leftChild) del = del->leftChild;
    adjustNode(del);
    del->leftChild = curr->leftChild;
    del->rightChild = curr->rightChild;
    del->parent = curr->parent;
    if (curr->parent->leftChild == curr) {
        curr->parent->leftChild = del;
        return;
    }
    curr->parent->rightChild = del;
    return;
}

TreeNode* deleteRoot(TreeNode *curr) {
    if (!curr->leftChild && !curr->rightChild) return NULL;
    else if (!curr->leftChild) {
        curr->rightChild->parent = curr->parent;
        return curr->rightChild;
    }
    else if (!curr->rightChild) {
        curr->leftChild->parent = curr->parent;
        return curr->leftChild;
    }
    TreeNode *del = curr->rightChild;
    while (del->leftChild) del = del->leftChild;
    adjustNode(del);
    del->leftChild = curr->leftChild;
    del->leftChild->parent = del;
    del->rightChild = curr->rightChild;
    del->rightChild->parent = del;
    del->parent = NULL;
    return del;
}

void MovieTree::deleteMovie(std::string title)
{
    TreeNode *del = searchChar(title.at(0));
    if (!del || !root) {
        cout << "Movie: " << title << " not found, cannot delete." << endl;
        return;
    }
    removeMovie(del, title);
    if (!del->head) {
        if (del == root) {
            root = deleteRoot(del);
            delete del;
            return;
        }
        adjustNode(del);
        delete del;
        return;
    }
}

// Based on help from https://stackoverflow.com/a/4607618

void MovieTree::leftRotation(TreeNode * curr) {
    TreeNode * x = curr;
    TreeNode * y = curr->rightChild;
    x->rightChild = y->leftChild;
    if(y->leftChild) {
        y->leftChild->parent = x;
    }
    y->parent = x->parent;
    if(!x->parent) root = y;
    else if(x == x->parent->leftChild) x->parent->leftChild = y;
    else x->parent->rightChild = y;
    y->leftChild = x;
    x->parent = y;
}

//------ Given Methods--------//
void _grader_inorderTraversal(TreeNode * root)
{
	if (root == NULL) {
		return;
	}

	_grader_inorderTraversal(root->leftChild);
	cout << root->titleChar << " ";
	_grader_inorderTraversal(root->rightChild);
}


void MovieTree::inorderTraversal() {
	_grader_inorderTraversal(root);
	cout << endl;
}



TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}

TreeNode* MovieTree::searchChar(char key)
{
    return searchCharHelper(root, key);
}
