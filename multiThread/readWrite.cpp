#include <iostream>
#include <thread>
#include <mutex>
#include <array>
#include <condition_variable>
#include <sstream>

using namespace std;

bool ended = false;

static int fullSlots = 0;
static int emptySlots = 8;
static int iterations = 10;

void read(condition_variable& cvRead, condition_variable& cvWrite, array<int,8>& arr) {
  int cnt = 0;
  while(cnt < (int)arr.size() * iterations) {
    mutex m;
    unique_lock<mutex> lk(m);
    cvRead.wait(lk, []{return fullSlots > 0; });

    stringstream ss; ss << "read value " << arr.at(cnt % arr.size());
    cout << ss.str() << endl;
    emptySlots++;

    fullSlots--;
    cvWrite.notify_one();
    cnt++;
  }
}

void write(condition_variable& cvRead, condition_variable& cvWrite, array<int,8>& arr) {
  int cnt = 0;
  while(cnt < (int)arr.size() * iterations) {
    mutex m;
    unique_lock<mutex> lk(m);
    cvWrite.wait(lk, []{return fullSlots < 8; });
    fullSlots++;
    emptySlots--;

    arr[cnt % arr.size()] = cnt;

    cvRead.notify_one();
    cnt++;
  }
}

class MyClass {
public:
  MyClass() = default;

  void run() { startThreads(); }
private:
  mutex mReadLock;
  mutex mWriteLock;
  condition_variable mCvRead;
  condition_variable mCvWrite;
  std::array<int,8> mArr;
  void startThreads() {
    thread t1 = thread(read, ref(mCvRead), ref(mCvWrite), ref(mArr));
    thread t2 = thread(write, ref(mCvRead), ref(mCvWrite), ref(mArr));
    t1.join();
    t2.join();
  }
};

int main() {
  MyClass cls;
  cls.run();
  return 0;
}