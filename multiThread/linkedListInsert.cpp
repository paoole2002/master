#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

struct Node {
  Node(int val) : mVal(val) {}
  int mVal = 0;
  Node* mNext = nullptr;
  mutex mLock;
};

struct LinkedList {
  Node* mHead = nullptr;
  void insert(int val) {
    Node* node = new Node(val);
    if (!mHead) { mHead = node; return; }
    Node* temp = mHead;
    while (temp->mNext) { temp = temp->mNext; }
    temp->mNext = node;
  }

  void print() {
    Node* temp = mHead;
    while(temp) {
      cout << temp->mVal << ",";
      temp = temp->mNext;
    }
    cout << '\n';
  }
};

static void sortedInsert(LinkedList* ll, int value) {
  Node* node = new Node(value);
  Node* prev = ll->mHead;
  Node* cur = prev->mNext;

  while (cur) {
    if (cur->mVal > value) {
      prev->mNext = node;
      node->mNext = cur;
      return;
    }
    prev = cur;
    cur = cur->mNext;
  }
}

int main() {
  LinkedList ll;
  for (int i = 2; i <= 40; i += 2) ll.insert(i);
  ll.print();

  vector<thread> threads(2);
  int value = 24;
  for (size_t idx = 0; idx < threads.size(); idx++) {
    threads[idx] = thread(sortedInsert, &ll, value);
    value = 23;
  }
  for (auto& t : threads) t.join();
  ll.print();
  return 0;
}