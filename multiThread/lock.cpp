#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

void myFunc1(mutex& m, bool& go) {
  while(!go) {}
  m.lock();
  cout << "This is thread 1" << endl;
  m.unlock();
}
void myFunc2(mutex& m, bool& go) {
  m.lock();
  cout << "This is thread 2" << endl;
  m.unlock();
  go = true;
}

class MyClass {
public:
  MyClass() = default;

  void run() { startThreads(); }
private:
  mutex m1;
  mutex m2;
  bool mGo = false;
  void startThreads() {
    thread t1 = thread(myFunc1, ref(m1), ref(mGo));
    thread t2 = thread(myFunc2, ref(m1), ref(mGo));
    t1.join();
    t2.join();
  }
};

int main() {
  MyClass cls;
  cls.run();
  return 0;
}