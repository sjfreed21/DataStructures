#include "ProducerConsumer.hpp"
#include <iostream>

// you may include more libraries as needed

using namespace std;

/*
 * Purpose: displays a menu with options
 * @param none
 * @return none
 */
void menu()
{
	cout << "*----------------------------------------*" << endl;
	cout << "Choose an option:" << endl;
    cout << "1. Producer (Produce items into the queue)" << endl;
	cout << "2. Consumer (Consume items from the queue)" << endl;
	cout << "3. Return the queue size and exit" << endl;
	cout << "*----------------------------------------*" << endl;
}
// Use getline for reading
int main(int argc, char const *argv[])
{
	ProducerConsumer queue;
	while(true) {
		int opt = 0, num = 0, item = 0;
		string name;
		menu();
		cin >> opt;
		getchar();
		switch (opt) {
			case 1:
				cout << "Enter the number of items to be produced:" << endl;
				cin >> item;
				getchar();
				for(int i = 0; i < item; i++) {
					cout << "Item" << i+1 << ":" << endl;
					getline(cin,name);
					queue.enqueue(name);
				}
				break;
			case 2:
				cout << "Enter the number of items to be consumed:" << endl;
				cin >> num;
				getchar();
				for(int i = 0; i < num; i++) {
				    if(queue.isEmpty()) {
					    cout<< "No more items to consume from queue" << endl;
					    break;
				    }
				    else {
			    	    cout << "Consumed: " << queue.peek() << endl;
				        queue.dequeue();
				    }
				}
				break;
			case 3:
				cout << "Number of items in the queue:" << queue.queueSize() << endl;
				return 0;
			default: break;
		}
	}
}
