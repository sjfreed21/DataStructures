#include <iostream>

using namespace std;

struct LLNode{
    int key;
    LLNode *next;
};

class LinkedList{
  private:
    LLNode *head;

  public:
    LinkedList(){
    	head = NULL;
    }
    void insert(int key);
    LLNode * search(int key);
    void display();
};