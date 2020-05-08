#include "RPNCalculator.hpp"
#include <iostream>

using namespace std;

RPNCalculator::RPNCalculator(){
    stackHead = NULL;
}

RPNCalculator::~RPNCalculator(){
    while(!isEmpty()){
        pop();
    }
}

bool RPNCalculator::isEmpty(){
    Operand * test = stackHead;
    return(test==NULL);
}

void RPNCalculator::push(float num){
    Operand * add = new Operand;
    add->number = num;
    add->next = stackHead;
    stackHead = add;
}

void RPNCalculator::pop(){
    if(!isEmpty()){
        Operand * temp = stackHead;
        stackHead = stackHead->next;
        delete temp;
    }
    else
    {
        cout<<"Stack empty, cannot pop an item."<<endl;
    }
}

Operand* RPNCalculator::peek(){
    if(!isEmpty()) return stackHead;
    else {
        cout << "Stack empty, cannot peek." << endl;
        return NULL;
    }
}

bool RPNCalculator::compute(string symbol){
    if(symbol != "+" && symbol != "*") {                // this case not working?
        cout << "err: invalid operation" << endl;
        return false;
    }
    if(isEmpty()) {
        cout << "err: not enough operands" << endl;
        return false;
    }
    Operand * o1 = peek();
    float v1 = o1->number;
    pop();
    if(isEmpty()) {
        cout << "err: not enough operands" << endl;
        push(v1);
        return false;
    }
    Operand * o2 = peek();
    float v2 = o2->number;
    pop();
    if(symbol == "+") {
        push(v1+v2);
        return true;
    }
    if(symbol == "*") {
        push(v1*v2);
        return true;
    }
}