#include "MinHeap.hpp"
#include <limits.h>
using namespace std;

/*
Swaps two integer values
*/
void swap(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

/*
Constructor for our MinHeap implementation
*/
MinHeap::MinHeap(int cap)
{
  currentSize = 0;
  capacity = cap;
  heapArr = new int[capacity];
}

/*
Finds the parent of a node, given its index.
*/
int MinHeap::parent(int index)
{
  return (index-1)/2;
}

/*
Returns the left child of a node.
*/
int MinHeap::leftChild(int index)
{
  return ((2*index) + 1);
}

/*
Returns the right child of a node.
*/
int MinHeap::rightChild(int index)
{
  return ((2*index) + 2);
}

/*
Returns the smallest element from the heap.
*/
int MinHeap::getMin()
{
  return heapArr[0];
}

/*
When an element is removed/deleted. This method make sures the array
satisfies the heap property.
*/
// TODO Complete the heapify function
void MinHeap::heapify(int i)
{
  int l = leftChild(i);
  int r = rightChild(i);
  int smallest = i;

  if(l < currentSize && heapArr[l] < heapArr[i] && heapArr[l] < heapArr[r]) {
    smallest = l;
  }
  else if(r < currentSize && heapArr[r] < heapArr[i]) {
    smallest = r;
  }

  if(smallest != i) {
    swap(heapArr[i], heapArr[smallest]);
    heapify(smallest);
  }
}

/*
Inserts an element into the heap by maintaining the heap property.
*/
void MinHeap::insertElement(int value)
{
  if(currentSize == capacity)
  {
    cout<<"Maximum heap size reached. Cannot insert anymore"<<endl;
    return;
  }

  currentSize = currentSize + 1;
  int index = currentSize - 1;
  heapArr[index] = value;

  while (index != 0 && heapArr[parent(index)] > heapArr[index])
    {
       swap(&heapArr[index], &heapArr[parent(index)]);
       index = parent(index);
    }
}

/*
Prints the elements in the heap
*/
void MinHeap::print()
{
  int iter = 0;
  while(iter < currentSize)
  {
    cout<<heapArr[iter]<<" ";
    iter = iter + 1;
  }
  cout<<endl;
}

// SILVER TODO: Method to remove minimum element (or root) from min heap
int MinHeap::extractMin()
{
  if (currentSize <= 0)
      return INT_MAX;

  if (currentSize == 1)
  {
      currentSize--;
      return heapArr[0];
  }
  //TODO complete the function
  int temp = heapArr[0];
  heapArr[0] = heapArr[currentSize - 1];
  heapify(0);
  currentSize--;
  return temp;
}

// GOLD TODO: This function deletes a key
void MinHeap::deleteKey(int key)
{
  if(currentSize <= 0) return;
  int index = -1;
  for(int i = 0; i < currentSize; i++) {
    if(heapArr[i] == key) {
      index = i;
      break;
    }
  }
  if(index == -1) return;
  heapArr[index] = INT_MIN;
  while (index != 0 && heapArr[parent(index)] > heapArr[index])
  {
      swap(heapArr[index], heapArr[parent(index)]);
      index = parent(index);
  }
  extractMin();
}
