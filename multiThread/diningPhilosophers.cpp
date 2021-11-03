#include <thread>
#include <mutex>
#include <array>
#include <iostream>
#include <vector>
#include <memory>
#include <unistd.h>
#include <condition_variable>
#include <sstream>

using namespace std;

static int permits = 3;

void think(const int philosopher) {
  mutex m1;
  m1.lock();
  stringstream ss;
  ss << "philosopher with id: " << to_string(philosopher) << " is eating.\n";
  cout << ss.str();
  m1.unlock();
}

void eat(mutex& leftFork, mutex& rightFork, condition_variable& cv, const int philosopher) {

  mutex lm;
  unique_lock<mutex> lk(lm);

  cv.wait(lk, []{ return permits > 0;}); // this acts like a while loop
  permits--; // decrement permits by 1

  leftFork.lock(); // acquire the left fork
  rightFork.lock(); // acquire the right fork
  think(philosopher);

  mutex m;
  m.lock();
  stringstream ss;
  ss << philosopher << " starts eating om nom nom nom.\n";
  cout << ss.str();
  m.unlock();
  sleep(3);
  m.lock();
  stringstream ss1;
  ss1 << philosopher << " is done eating.\n";
  cout << ss1.str();
  m.unlock();

  rightFork.unlock(); // release left fork
  leftFork.unlock(); // release right fork
  permits++;
  cv.notify_all();
}

int main() {
  array<thread,5> threads;
  mutex locks[5];
  condition_variable cv;

  for(int i = 0; i < 5; i++) {
    int philosopher = i;
    mutex& leftFork = locks[i];
    mutex& rightFork = locks[(i + 1) % 5];
    threads[i] = thread(eat, ref(leftFork), ref(rightFork), ref(cv), (philosopher));
  }
  
  for(thread& t : threads) {
    t.join();
  }
  return 0;
}