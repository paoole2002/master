#include <iostream>
#include <cassert>
#include <list>
using namespace std;

struct Node{
  int mVal = -1;
  Node* mNext;
  Node(int val) : mVal(val), mNext(nullptr) {}
};

class LinkedList {
public:
  LinkedList() {}

  ~LinkedList() {
    while(mHead) {
      Node* temp = mHead->mNext;
      delete(mHead);
      mHead = temp;
    }
    cout << "Linked list erased from memory" << endl;
    assert(!mHead);
  }

  void insertLast(int val) {
    mSize++;
    if (!mHead) { // first addition
      mHead = new Node(val);
      return;
    }
    Node* temp = mHead;
    while(temp->mNext){
      temp = temp->mNext;
    }
    temp->mNext = new Node(val);
    temp = temp->mNext;
  }

  void delNode(int val) {
    if (!mHead) { return; }
    mSize--;
    Node* temp = mHead;
    Node* prev = nullptr;
    while(temp && temp->mVal != val){ prev = temp; temp = temp->mNext; }
    if (!prev){
      Node* toBeDeleted = mHead;
      mHead = mHead->mNext; // delete first node
      delete(toBeDeleted);
      return; 
    }
    if (!temp){ return; } // couldnt find node
    Node* toBeDeleted = temp;
    prev->mNext = temp->mNext;
    temp->mNext = nullptr;
    delete(toBeDeleted);
  }

  void insertFirst(int val) {
    mSize++;
    Node* node = new Node(val);
    node->mNext = mHead;
    mHead = node;
  }

  void insertAfter(int val, int newVal) {
    mSize++;
    assert(mHead); // ow no need for this function
    Node* temp = mHead;
    Node* prev = nullptr;
    while(temp && temp->mVal != val) {
      prev = temp;
      temp = temp->mNext;
    }
    if (!prev) {
      insertFirst(newVal);
    }
    Node* newNode = new Node(newVal);
    prev->mNext = newNode;
    newNode->mNext = temp;
  }

  size_t getSize() const { return mSize; }

  void printLL() {
    Node* temp = mHead;
    while(temp) {
      cout << temp->mVal << ", ";
      temp = temp->mNext;
    }
    cout << endl;
  }

private:
  Node* mHead = nullptr;
  size_t mSize = 0;
};


int main() {
  LinkedList ll;
  for(int i = 0; i < 7; i++) {
    ll.insertLast(i);
  }
  ll.delNode(0);
  ll.insertAfter(3, 17);
  ll.delNode(17);
  ll.delNode(3);
  ll.delNode(2);
  ll.delNode(1);
  ll.printLL();
  cout << "Size is: " << ll.getSize() << endl;
  list<int> mGoldList;
  return 0;
}