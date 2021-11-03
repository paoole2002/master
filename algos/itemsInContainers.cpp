#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <map>
#include <string>

using namespace std;


// Given a string s consisting of items as "*" and closed compartments as an open and close "|", an array of starting
// indices startIndices, and an array of ending indices endIndices,
// determine the number of items in closed compartments within the substring between the two indices, inclusive.

// return first index greater - equal than target
int findStart(const vector<vector<int>>& nums, int target) {
  int start = 0; int end = nums.size() - 1; int res = 0;
  while(start <= end) {
    int mid = start + (end - start) / 2;
    if(nums[mid][0] == target){ return mid; }
    else if(nums[mid][0] > target) {
      res = mid;
      end = mid - 1;
    }
    else {
      start = mid + 1;
    }
  }
  return res;
}

// return first index smaller - equal than target
int findEnd(const vector<vector<int>>& nums, int target) {
  int start = 0; int end = nums.size() - 1; int res = 0;
  while(start <= end) {
    int mid = start + (end - start) / 2;
    cout << nums[mid][1] << endl;
    if(nums[mid][1] == target){ return mid; }
    else if(nums[mid][1] > target) {
      end = mid - 1;
    }
    else {
      res = mid;
      start = mid + 1;
    }
  }
  return res;
}


vector<int> getChars(const string& s, const vector<int>& starts, const vector<int>& ends) {
  vector<vector<int>> vals; vector<int> res;
  int i = 0; int cnt = 0; int braqs = 0; int prevIdx= 0;
  while(i < (int)s.size()) {
    if(braqs == 1 && s[i] == '*'){ cnt++; }
    else if(s[i] == '|') {
      braqs++;
      if(braqs == 2 && i - prevIdx > 1) {
        vals.push_back({prevIdx, i, cnt});
        braqs--;
      }
      else if(i - prevIdx == 1){ braqs--; }
      prevIdx = i;
    }
    i++;
  }
  if(vals.empty()){ return {}; }
  for(int i = 0; i < (int)starts.size(); i++) {
    int start = starts[i]; int end = ends[i];
    int fir = findStart(vals, start);
    int sec = findEnd(vals, end);
    cout << "start " << start << ", " << " end " << end << endl;
    cout << fir << "," << sec << endl;
    if(fir == 0){ res.push_back(vals[sec][2]); }
    else if(sec > vals.size() - 1){ res.push_back(vals[sec][2]); }
    else {
      int rem = vals[fir - 1][2];
      int add = vals[sec][2];
      res.push_back(add - rem);
    }
  }
  
  return res;
}

int main() {
  vector<int> starts = {2, 0};
  vector<int> ends = {7, 18};
  string s = "|***|*||**|**||**||||";

  vector<int> res = getChars(s, starts, ends);
  for(const int& v : res) {
    cout << v << ",";
  }
  cout << endl;
  return 0;
}