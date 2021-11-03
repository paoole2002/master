#include <queue>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <sstream>

class BlockingQueue {
public:
  BlockingQueue(int size) : mSize(size) {}

  void push(int val) {
    std::unique_lock<std::mutex> lk(mPushLock);
    while(mQ.size() >= mSize) {
      mPushCv.wait(lk);
    }
    mQ.push(val);
    mPopCv.notify_all();
  }

  int popFront() {
    std::unique_lock<std::mutex> lk(mPopLock);
    while(mQ.empty()) {
      mPopCv.wait(lk);
    }
    int val = mQ.front(); mQ.pop();
    mPushCv.notify_all();
    return val;
  }

  int getSize() { return mQ.size(); }
private:
  std::mutex mPopLock, mPushLock;
  std::condition_variable mPushCv, mPopCv;
  int mSize = 0;
  std::queue<int> mQ;
};

void write(BlockingQueue& bq, std::mutex& m) {
  for(int i = 0; i < 10; i++) {
    m.lock();
    bq.push(i);
    m.unlock();
  }
}

void read(BlockingQueue& bq, std::mutex& m) {
  for(int i = 0; i < 10; i++) {
    m.lock();
    std::stringstream ss;
    int size = bq.getSize();
    int val = bq.popFront();
    ss << "Val is: " << val << " with size: " << size << std::endl;
    std::cout << ss.str();
    m.unlock();
  }
}

int main() {
  BlockingQueue bq(5);
  std::thread writeThreads[3];
  std::thread readThreads[3];
  std::mutex m1, m2;
  for(int i = 0; i < 1; i++) {
    writeThreads[i] = std::thread(write, std::ref(bq), std::ref(m1));
    readThreads[i] = std::thread(read, std::ref(bq), std::ref(m2)); 
  }
  for(int i = 0; i < 1; i++) {
    writeThreads[i].join();
    readThreads[i].join();
  }
  return 0;
}