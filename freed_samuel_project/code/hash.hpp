#include <iostream>

using namespace std;

struct HashNode {
    int key;
    HashNode * next;
};

class Hash {
    private:
        HashNode * * table;
        int size;
        int collisions;
    public:
        Hash(int inSize);
        void insert(int key, int type);
        HashNode * search(int key);
        int getCollisionsReset();
        void printHash();
};