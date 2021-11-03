#include <thread>
#include <mutex>
#include <array>
#include <iostream>
#include <vector>
#include <memory>
#include <unistd.h>
#include <condition_variable>
#include <sstream>
#include <unordered_map>
#include <string>

using namespace std;

void fillMap(unordered_map<char,int>& cnts, mutex& mapLock, const string& word) {
  for(const char& ch : word) {
    mapLock.lock();
    cnts[ch]++;
    mapLock.unlock();
  }
}

void readMap(const unordered_map<char,int>& d) {
  for(const auto& [ch, cnt] : d) {
    stringstream ss;
    ss << "char: " << ch << " has freq: " << cnt << "\n";
    cout << ss.str();
  }
}

int main() {
  mutex mapLock;

  vector<string> words = {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbccddeeffgg", "aaabbbcccdddeeefffggg", "aaabbbcccdddeeefffgggabcdefgh"};
  unordered_map<char,int> cnts;

  vector<thread> threads(3);

  for(int i = 0; i < 3; i++) {
    threads[i] = thread(fillMap, ref(cnts), ref(mapLock), ref(words[i]));
  }
  
  for(thread& t : threads) {
    t.join();
  }

  cout << "here\n";

  thread read = thread(readMap, ref(cnts));
  read.join();

  return 0;
}