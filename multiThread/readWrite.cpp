#include <iostream>
#include <thread>
#include <mutex>
#include <array>
#include <condition_variable>

using namespace std;

bool ready = true;

void read(condition_variable& cvRead, condition_variable& cvWrite, array<int,100>& arr, int idx) {
  while (idx < 100) {
    std::mutex m;
    std::unique_lock<std::mutex> lk(m);
    cvRead.wait(lk, []{ return !ready; });
    cout << "Reading data at idx " << idx << " is " << arr[idx] << endl;
    idx++;
    ready = true;
    lk.unlock();
    cvWrite.notify_one();
  }
}
void write(condition_variable& cvRead, condition_variable& cvWrite, std::array<int,100>& arr, int idx) {
  while(idx < 100) {
    std::mutex m;
    std::unique_lock<std::mutex> lk(m);
    cvWrite.wait(lk, []{ return ready; });
    ready = false;
    arr[idx++] = idx + 2;
    lk.unlock();
    cvRead.notify_one();
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
  std::array<int,100> mArr;
  void startThreads() {
    thread t1 = thread(read, ref(mCvRead), ref(mCvWrite), ref(mArr), 0);
    thread t2 = thread(write, ref(mCvRead), ref(mCvWrite), ref(mArr), 0);
    t1.join();
    t2.join();
  }
};

int main() {
  MyClass cls;
  cls.run();
  return 0;
}