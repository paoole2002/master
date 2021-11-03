#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>

static int CNT = 10;
static bool READING = false;
static bool WRITING = true;
static bool STOPPED = false;
static int idx = 0;
void read(std::mutex& lock, std::condition_variable& readCv, std::condition_variable& writeCv,
          std::unordered_map<std::string,int>& dict) {
  while(!STOPPED) {
    std::unique_lock<std::mutex> lk(lock);
    while(WRITING) {
      readCv.wait(lk);
    }
    if (STOPPED) return;
    READING = false;
    lk.unlock();
    writeCv.notify_all();
  }
}

void write(std::mutex& lock, std::condition_variable& readCv, std::condition_variable& writeCv,
           std::unordered_map<std::string,int>& dict) {
  while(idx < CNT) {
    std::unique_lock<std::mutex> lk(lock);
    while(READING) {
      writeCv.wait(lk);
    }
    if(idx >= CNT) return;
    std::stringstream ss; ss << idx << ",";
    std::cout << ss.str();
    dict[std::to_string(idx)]++;
    WRITING = false;
    idx++;
    lk.unlock();
    readCv.notify_all();
  }
  STOPPED = true;
  readCv.notify_all();
  std::cout << '\n';
}

int main() {
  std::mutex readLock, writeLock;
  std::condition_variable readCv, writeCv;
  std::unordered_map<std::string,int> dict;
  
  std::vector<std::thread> readVec, writeVec;
  for(int i = 0; i < 4; i++) {
    readVec.emplace_back(read, std::ref(readLock), std::ref(readCv), std::ref(writeCv), std::ref(dict));
    writeVec.emplace_back(write, std::ref(writeLock), std::ref(readCv), std::ref(writeCv), std::ref(dict));
  }
  // std::thread readThread = std::thread(read, std::ref(readLock), std::ref(readCv), std::ref(writeCv), std::ref(dict));
  // std::thread writeThread = std::thread(write, std::ref(writeLock), std::ref(readCv), std::ref(writeCv), std::ref(dict));

  for(std::thread& t : writeVec) {
    t.join();
  }
  for(std::thread& t : readVec) {
    t.join();
  }
  // readThread.join();
  // writeThread.join();
  for(const std::pair<std::string,int>& p : dict) {
    std::cout << p.first << " has cnt " << p.second << std::endl;
  }
  return 0;
}