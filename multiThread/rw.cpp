#include <queue>
#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <sstream>
#include <array>

#define print(x) std::cout << x << std::endl;

static int ROUNDS = 3;
static int FULL_SLOTS = 0;
static int EMPTY_SLOTS = 8;
static bool mDone = false;

void write(std::array<int,8>& arr, std::condition_variable& cvWrite, std::condition_variable& cvRead) {
  int idx = 0; std::mutex m;
  while(idx < arr.size() * ROUNDS) {
    std::unique_lock<std::mutex> lk(m);
    while(FULL_SLOTS >= 8) {
      cvWrite.wait(lk);
      if(mDone) return;
    }
    int k = idx % arr.size();
    arr[k] = idx;
    FULL_SLOTS++;
    cvRead.notify_one();
    
    idx++;
    // print(idx);
  }
  mDone = true;
  cvRead.notify_one();
}

void read(std::array<int,8>& arr, std::condition_variable& cvWrite, std::condition_variable& cvRead) {
  int idx = 0; std::mutex m;
  while(idx < arr.size() * ROUNDS) {
    std::unique_lock<std::mutex> lk(m);
    while(FULL_SLOTS <= 0) {
      cvRead.wait(lk);
      if(mDone) return;
    }

    std::stringstream ss;
    ss << arr[idx % arr.size()] << ",";
    std::cout << ss.str(); 

    FULL_SLOTS--;
    cvWrite.notify_one();
    idx++;
  }
  mDone = true;
  cvWrite.notify_one();
}

int main() {
  std::condition_variable readCv, writeCv;
  std::array<int,8> arr;
  std::thread writeThread(write, std::ref(arr), std::ref(writeCv), std::ref(readCv));
  std::thread readThread(read, std::ref(arr), std::ref(writeCv), std::ref(readCv));

  writeThread.join();
  readThread.join();
  return 0;
}
