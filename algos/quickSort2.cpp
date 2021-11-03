#include "iostream"
#include <string.h>
#include <vector>

using namespace std;

class QuickSort {
public:
  QuickSort(vector<int>& nums) {
    quicksort(nums, 0, nums.size() - 1);
  }
private:
  void quicksort(vector<int>& nums, int start, int end) {
    if(start >= end){ return; }
    pair<int,int> p = findPivot(nums, start, end);
    int fir = p.first; int sec = p.second;
    quicksort(nums, start, fir - 1);
    quicksort(nums, sec + 1, end);
  }

  pair<int,int> findPivot(vector<int>& nums, int start, int end) {
    int mid = start + (end - start) / 2;
    int pivotValue = nums.at(mid);
    int l = start; int r = end; int cur = start;
    while(cur <= r) {
      if(nums[cur] < pivotValue) {
        swap(nums, l, cur);
        cur++; l++;
      }
      else if(nums[cur] > pivotValue) {
        swap(nums, cur, r);
        r--;
      }
      else{ cur++; }
    }
    return {l,r};
  }

  void swap(vector<int>& nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
  }
};

int main() {
  vector<int> nums(30);
  for(int i = 0; i < nums.size(); i++) {
    nums[i] = rand() % (nums.size() - 15);
  }

  for(const int& num : nums) {
    cout << num << ",";
  }
  cout << endl;

  QuickSort q(nums);
  for(const int& num : nums) {
    cout << num << ",";
  }
  cout << endl;

  return 0;
}