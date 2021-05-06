#include "iostream"

using namespace std;

class Queue {
public:
  void enqueue(int val) { // push in the end of queue
    Node* node = new Node(val);
    if(!first) {
      first = node;
      last = node; return;
    }
    last->next = node;
    last = node;
    cout << last->val << endl;
  }

  int front() { // return first element of queue
    if(!first){
      return -1;
    }
    return first->val;
  }

  void dequeue() { // pop first element from queue
    if(!first){ return; }
    first = first->next;
  }

  bool empty() { return first == nullptr; }
private:
  struct Node{
    int val = -1;
    Node* next;
    Node(int v) : val(v) {}
  };
  Node* first = nullptr;
  Node* last = nullptr;
};

int main() {
  Queue q;
  q.enqueue(1);
  q.enqueue(2);
  q.enqueue(3);
  q.enqueue(4);
  cout << "First element in queue: " << q.front() << endl;
  q.dequeue();
  cout << "First element in queue: " << q.front() << endl;
}