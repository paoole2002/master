#include <vector>
#include <iostream>

using namespace std;


class PriorityQueue {
public:
  PriorityQueue(const vector<int>& input) { heapify(input); }

  const vector<int>& getPq() const { return mPq; }

  int getMax() {
    if(empty()){ return -1; }
    int maxi = mPq[0];
    swap(0, mPq.size() - 1);
    mPq.pop_back();
    percolateDown();
    return maxi;
  }

  bool empty() const { return mPq.empty(); }
private:
  void heapify(const vector<int>& input) {
    for(const int& num : input) {
      mPq.push_back(num);
      percolateUp();
    }
  }

  void percolateUp() {
    int idx = mPq.size() - 1;
    while(idx > 0) { // till we reach root
      int parentIdx = idx % 2 == 0 ? (idx - 1) / 2 : idx / 2;
      if(mPq[idx] > mPq[parentIdx]) {
        swap(idx, parentIdx);
      }
      idx = parentIdx;
    }
  }

  void percolateDown() {
    int idx = 0;
    while(idx < mPq.size()) {
      int lIdx = idx * 2 + 1;
      int rIdx = idx * 2 + 2;
      if(lIdx < mPq.size() && rIdx < mPq.size()) {
        if(mPq[idx] < mPq[lIdx] && mPq[idx] < mPq[rIdx]) {
          if(mPq[rIdx] > mPq[lIdx]){ swap(idx, rIdx), idx = rIdx; }
          else{ swap(idx, lIdx); idx = lIdx; }
        }
        else if(mPq[idx] < mPq[lIdx]) { swap(idx, lIdx); idx = lIdx; }
        else if (mPq[idx] < mPq[rIdx]) { swap(idx, rIdx), idx = rIdx; }
        else{ return; }
      }
      else if(lIdx < mPq.size() && mPq[lIdx] > mPq[idx]){ swap(idx, lIdx); idx = lIdx; }
      else{ return;}
    }
  }


  void swap(int i, int j) {
    int temp = mPq[i];
    mPq[i] = mPq[j];
    mPq[j] = temp;
  }

  vector<int> mPq;
};

int main() {
  vector<int> vec = {3,5,6,2,1,9,7,8,12,10,14,15,16,19,20,21,2,1,2,3};
  // vector<int> vec = {3,5,6,2};

  PriorityQueue pq(vec);

  while(!pq.empty()) {
    cout << pq.getMax() << ",";
  }

  return 0;
}