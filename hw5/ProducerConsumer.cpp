#include "ProducerConsumer.hpp"
#include <iostream>

using namespace std;

ProducerConsumer::ProducerConsumer(){
    queueFront = 0;
    queueEnd = 0;
}

bool ProducerConsumer::isEmpty(){
    if(!counter) return true;
    return false;
}

bool ProducerConsumer::isFull(){
    return(counter > 19);
}

void ProducerConsumer::enqueue(string item) {
    if(isFull()) {
        cout << "Queue full, cannot add new item" << endl;
        return;
    }
    if(queueEnd > 19) queueEnd = queueEnd - 20;
    queue[queueEnd] = item;
    queueEnd++;
    counter++;
}

void ProducerConsumer::dequeue(){
    if(isEmpty()) {
        cout << "Queue empty, cannot dequeue an item" << endl;
        return;
    }
    if(queueFront > 19) queueFront = queueFront - 20;
    queue[queueFront] = "";
    queueFront++;
    counter--;
}

string ProducerConsumer::peek() {
    if(isEmpty()) {
        cout << "Queue empty, cannot peek" << endl;
        return "";
    }
    return queue[queueFront];
}

int ProducerConsumer::queueSize() {
    return(counter);
}