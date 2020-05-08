#include "hash.hpp"
#include <iostream>

Hash::Hash(int inSize) {
    
    // Create new table of nodes
    table = new HashNode * [inSize];

    // Initialize all values to null (clear old memory that could cause errors)
    for(int i = 0; i < inSize; i++) table[i] = NULL;

    // Initialize table private variables
    size = inSize;
    collisions = 0;
}

void Hash::insert(int key, int type){

    // Compute hash
    int hash = key % size;

    // Create new node
    HashNode * add = new HashNode;
    add->key = key;
    add->next = NULL;

    // Initialize collision checker - ensures collision is only incremented once per insert
    bool coll = false;

    // Switch based on collision resolution
    switch (type) {

        // Open addressing, linear probing
        case 1: {
            while(table[hash]) {
                if(!coll) {
                    coll = true;
                    collisions++;
                }
                hash++;
                hash = hash % size;
            }
            table[hash] = add;
            return;
        }

        // Open addressing, quadratic probing
        case 2: {
            int count = 1;
            while(table[hash]) {
                if(!coll) {
                    coll = true;
                    collisions++;
                }
                hash += count * count;
                count++;
                hash = hash % size;
            }
            table[hash] = add;
            return;
        }

        // Chaining
        case 3: {
            HashNode * curr = table[hash];
            if(curr) {
                while(curr->next) curr = curr->next;
                curr->next = add;
            }
            else table[hash] = add;
            return;
        }
    }
}

HashNode * Hash::search(int key){

    // Compute hash
    int hash = key % size;

    // If value at hash exists, select it
    if(table[hash]) {
        HashNode * tmp = table[hash];
        while(tmp) {

            // Find correct address of key
            if(tmp->key == key) return tmp;
            tmp = tmp->next;
            collisions++;
        }
    }
    return NULL;
}

int Hash::getCollisionsReset(){

    // Returns the number of collisions and then resets it for the next usage
    int temp = collisions;
    collisions = 0;
    return temp;
}

void Hash::printHash(){
    HashNode * curr;

    // Print from index 0 to max if a value is stored
    for(int i = 0; i < size; i++) {
        curr = table[i];
        while(curr) {
            cout << curr->key << endl;
            curr = curr->next;
        }
    }
}