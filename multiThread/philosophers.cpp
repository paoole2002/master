#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <unistd.h>
#include <sstream>
#include <vector>

static void think() { sleep(5); }
static int PERMITS = 1;

void eat(int id, std::mutex& leftFork, std::mutex& rightFork, std::condition_variable& cv) {
  std::mutex m;
  std::unique_lock<std::mutex> lk(m);
  while(PERMITS <= 0) {
    cv.wait(lk,[]{ return PERMITS > 0; } );
  }
  PERMITS--;
  leftFork.lock();
  rightFork.lock();
  std::stringstream ss;
  ss << "philosopher eating and thinking: " << id << std::endl;
  std::cout << ss.str();
  think();
  leftFork.unlock();
  rightFork.unlock();
  PERMITS++;
  lk.unlock();
  cv.notify_all();
}

int main() {
  std::vector<std::thread> philosophers(5);
  int idx = 0;
  std::condition_variable cv;
  std::mutex forks[5];
  for(std::thread& philosopher : philosophers) {
    philosopher = std::thread(eat, idx, ref(forks[idx]), ref(forks[(idx + 1) % 5]), ref(cv));
    idx++;
  }
  for(std::thread& philosopher : philosophers) {
    philosopher.join();
  }
  return 0;
}