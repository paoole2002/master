#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <queue>
#define print(x)  std::cout<<x<<std::endl;
using namespace std;

int main(){
  vector<int> times;
  // times = {1,1,1,2,2,2,3,3,3,4,4,4};
  // times = {1,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,11,11,11};
  // times = {1,1,1,1,2,2,2,3,3,3,3,4,5,5,5,6,6,6,6,7,7,7,8,8,8,8,9,9,9,9,9,10,10,11,11,11,11,11,11,12,12,
          //  12,12,12,12,12,13,13,13,13,14,14,14,14,14,16,16,16,16,16,16,17,17,17,18,18,18,18,18,18};
  // for(auto i = 0; i < 21; i++){ times.push_back(1);}
  int curTime = times.at(0);
  queue<int> qTen;
  queue<int> qMin;
  auto secCnt = 0;
  int mDropped = 0;
  for(const auto& t : times) {
    while(!qTen.empty() && t - qTen.front() >= 10) {
      qTen.pop();
    }
    while(!qMin.empty() && t - qMin.front() >= 60) {
      qMin.pop();
    }
    qTen.push(t); qMin.push(t);
    if(qTen.size() > 20) {
      mDropped++;
    }
    if(qMin.size() > 60) {
      mDropped++;
    }
    if(t == curTime && secCnt >= 3){ mDropped++; }
    else if(t == curTime) { secCnt++; }
    else {
      secCnt = 1;
      curTime = t;
    }
  }
  print(mDropped)
  return mDropped;
}