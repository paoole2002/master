#include "iostream"

using namespace std;

/**
 * Custom class for a Stack using a Node class
 * Missing Exception Handling
 * If we wanted to conver the stack to a min/max stack then simply have the node hold 2 values,
 * one being minSoFar and the other being the value
 */

template <class T> class Stack {
public:
  void push(T v) {
    Node* node = new Node(v);
    if(!stak){
      stak = node;
      return;
    }
    node->next = stak;
    stak = node;
  }

  T top() {
    try{
      T res = stak->val;
      return res;
    }
    catch (...) {
      throw "Stack is empty";
    }
  }
  void pop() {
    try{
      stak = stak->next;
    }
    catch (...) {
      throw "Stack is empty";
    }
  }

  bool empty(){
    return stak == nullptr;
  }
private:
  struct Node{
    T val = -1;
    Node* next;
    Node(T v) : val(v) {}
  };
  Node* stak = nullptr;
};

int main(){
  Stack<int> s;
  s.push(4);
  s.push(1);
  s.push(2);
  s.push(3);
  while(!s.empty()) {
    cout << "Top value: " << s.top() << endl;
    s.pop();
  }
  s.top();
  return 0;
}