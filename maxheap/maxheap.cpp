/*
0  1   2  3  4  5  6
-1 100 75 95 60 65 90
bst lookalike:
        100
    75      95
  60  65   90
you will notice left and right child is stored at 2*1 and 2*i+1 respectively
*/

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

// maxheap is basically a vector representation of a binary search tree with max value at the root node unlike how a bst will have left right nodes
// note: we use 1-based indexing here by fixing the starting value as -1
// the goal is to be able to find the size by always accessing the last index in the array
class MaxHeap
{
private:
  // keeps track of the size of the vector
  int _size = 0;
  // store your priority queue elements
  vector<int> store;

  int parent(int i) { return i >> 1; }      // i / 2 through bitwise operation
  int left(int i) { return i << 1; }        // i * 2
  int right(int i) { return (i << 1) + 1; } // i * 2 + 1

public:
  // Constructor
  MaxHeap() : store{-1} {} // Add -1 to the vector after creation
  bool isEmpty() const { return _size == 0; }
  int getMax() const { return store[1]; }
  void insertItem(int val);
  // shift up until it reaches the right place
  void shiftUp(int i);
  // remove the topmost value
  int extractMax();
  // shift down until it reaches the right place
  void shiftDown(int i);
};

void MaxHeap::shiftUp(int i)
{
  if (i > _size)
    return;
  if (i == 1)
    return;

  if (store[i] > store[parent(i)])
    std::swap(store[parent(i)], store[i]);

  shiftUp(parent(i));
}

void MaxHeap::insertItem(int val)
{
  if (_size + 1 >= store.size())
    store.push_back(0);

  store[++_size] = val;
  shiftUp(_size);
  return;
}

void MaxHeap::shiftDown(int i)
{
  if (i > _size)
    return;

  int swapId = i;
  if (left(i) <= _size && store[i] < store[left(i)])
    swapId = left(i);

  if (right(i) <= _size && store[swapId] < store[right(i)])
    swapId = right(i);

  if (swapId != i)
  {
    std::swap(store[i], store[swapId]);
    shiftDown(swapId);
  }

  return;
}

int MaxHeap::extractMax()
{
  if (_size == 0)
    return -1;

  int maxNum = store[1];
  std::swap(store[1], store[_size--]);

  if (_size > 0)
    shiftDown(1);

  return maxNum;
}

int main()
{
  MaxHeap *priorityQueue = new MaxHeap();

  if (priorityQueue->isEmpty())
    cout << "It is an empty priority queue" << endl;
  else
    cout << "We have a problem with the isEmpty() function" << endl;

  priorityQueue->insertItem(10);
  priorityQueue->insertItem(120);
  priorityQueue->insertItem(34);
  priorityQueue->insertItem(41);
  priorityQueue->insertItem(5);

  cout << priorityQueue->getMax() << endl;
  priorityQueue->extractMax();
  cout << priorityQueue->getMax() << endl;

  if (priorityQueue->isEmpty())
    cout << "This is wrong answer, shouldnt be empty" << endl;
  else
    cout << "It is correct! it is not empty" << endl;

  return 0;
}