#include <iostream>
#include <thread>
#include <mutex>

#define print(x) std::cout << x << std::endl;

void t1(int* x, int* y, int* a, std::mutex& m) {
  m.lock();
  *x = 1;
  // print("Thread 1 running");
  *a = *y + 1;
  m.unlock();
}

void t2(int* x, int* y, int* a, int* b, std::mutex& m) {
  m.lock();
  *y = 2;
  *b = *x + 3;
  // print("Thread 2 running");
  *a = *x + *y;
  m.unlock();
}

int main() {
  int a = 0, b = 0, x = 0, y = 0;
  std::mutex m;
  std::thread thread2(t2, &x, &y, &a, &b, ref(m));
  std::thread thread1(t1, &x, &y, &a, ref(m));
  
  
  thread1.join();
  thread2.join();

  std::cout << "x: " << x << " y: " << y << " a: " << a << " b: " << b << '\n';
}