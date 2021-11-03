#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <map>

using namespace std;

struct Comp
{
    bool operator()( const vector<int>& v1, const vector<int>& v2) const {
        return v1[1] < v2[1];
    }
};

// Your task is to find an element from a and an element form b such that the sum of their values is less or equal to
// target and as close to target as possible.
// Return a list of ids of selected elements

vector<vector<int>> optUtil(vector<vector<int>>& nums1, vector<vector<int>>& nums2, int target) {
  vector<vector<int>> res;
  int maxSoFar = 0;
  sort(nums1.begin(), nums1.end(),Comp());
  sort(nums2.begin(), nums2.end(),Comp());

  int idx = 0;
  for(const vector<int>& v: nums1) {
    int val1 = v[1]; int idx1 = v[0];
    // binary search with new target
    int newTar = target- val1;
    int start = 0; int end = nums2.size() - 1; int maxi = 0;
    while(start <= end) {
      int mid = start + (end - start) / 2;
      if(nums2[mid][1] <= newTar) {
        if(res.empty()) {
          res = {{idx, mid}};
        }
        else {
          int curResVal = nums1[res[0][0]][1] + nums2[res[0][1]][1];
          int curVal = val1 + nums2[mid][1];
          if(curVal > curResVal) {
            res = {{idx, mid}};
          }
          else {
            res.push_back({idx, mid});
          }
        }
        start = mid + 1;
      }
      else {
        end = mid - 1;
      }
    }
    idx++;
  }
  for(vector<int>& v : res) {
    v[0] = nums1[v[0]][0];
    v[1] = nums2[v[1]][0];
  }
  return res;
}

int main() {
  vector<vector<int>> nums1 = {{1, 8}, {2, 15}, {3, 9}};
  vector<vector<int>> nums2 = {{2, 11}, {1, 8}, {3, 12}};
  int target = 20;

  vector<vector<int>> res = optUtil(nums1, nums2, target);
  for(const vector<int>& v : res) {
    cout << v[0] << "," << v[1] << endl;
  }
  return 0;
}