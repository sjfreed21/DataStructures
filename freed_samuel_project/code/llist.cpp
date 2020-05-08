#include "llist.hpp"

using namespace std;

void LinkedList::insert(int key){

    // First element creation & insertion
    if(!head) {
        head = new LLNode;
        head->key = key;
        head->next = NULL;
    }

    // Later element creation & insertion
    else {
        LLNode * add = new LLNode;
        add->key = key;
        add->next = head;
        head = add;
    }
}

LLNode * LinkedList::search(int key){

    // Uses scanning pointer until the key matches
    LLNode * ptr = head;
    while (ptr && ptr->key != key) ptr = ptr->next;
    return ptr;
}

void LinkedList::display(){

    // Uses scanning pointer until the end of the list
    LLNode* temp = head;
    while(temp){
        cout<< temp->key <<" -> ";
        temp = temp->next;
    }
}