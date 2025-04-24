#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <sstream>

using namespace std;

vector<int> mergesort(const vector<int>& nums, int start, int end) {
  vector<int> ret;
  if (start < end) {
    int mid = start + (end - start) / 2;
    vector<int> l = mergesort(nums, start, mid);
    vector<int> r = mergesort(nums, mid + 1, end);

    int l1 = 0, l2 = 0;    
    while (l1 < l.size() && l2 < r.size()) {
      if (l[l1] <= r[l2]) {
        ret.push_back(l[l1]);
        l1++;
      }
      else {
        ret.push_back(r[l2]);
        l2++;
      }
    }

    while (l1 < l.size()) {
      ret.push_back(l[l1]); l1++;
    }

    while (l2 < r.size()) {
      ret.push_back(r[l2]); l2++;
    }
  }
  else if (start == end) { ret = { nums[start]}; }

  return ret;
}

vector<int> sortVecWithMergeSort(const vector<int>& nums) {
  return mergesort(nums, 0, nums.size() - 1);
}

void sortVecWithSelectionSort(vector<int>& nums) {
  for (int i = 0; i < nums.size(); i++) {
    for (int j = i + 1; j < nums.size(); j++) {
      if (nums[j] < nums[i]) {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
      }
    }
  }
}

void sortVecWithBubbleSort(vector<int>& nums) {
  for (int i = 0; i < nums.size(); i++) {
    for (int j = i; j < nums.size() - i; j++) {
      if (nums[j] > nums[j + 1]) {
        int tmp = nums[j];
        nums[j] = nums[j + 1];
        nums[j + 1] = tmp;
      }
    }
  }
}

// [5,3,2,6,4]
// [5, 3, 2, 6, 4] - i = 0, pivotIdx = -1
// -> [3, 5, 2, 6, 4] - i = 2, pivotIdx = 0
// -> [3, 2, 5, 6, 4] - i = 3, pivotIdx = 1
// -> [3, 2, 5, 6, 4] - i = 3, pivotIdx = 1
// -> [3, 2, 4, 6, 5] - pivotIdx = 2
int partition(vector<int>& nums, int start, int end) {
  int pivot = nums[end];
  int pivotIdx = start - 1;
  for (int i = start; i < end; i++) {
    if (nums[i] < pivot) {
      pivotIdx++;
      int temp = nums[i];
      nums[i] = nums[pivotIdx];
      nums[pivotIdx] = temp;
    }
  }

  int tmp = nums[end];
  nums[end] = nums[pivotIdx + 1];
  nums[pivotIdx + 1] = tmp; 

  return pivotIdx + 1;
}

void quicksort(vector<int>& nums, int start, int end) {
  if (start <= end) {
    int pivotIdx = partition(nums, start, end);
    quicksort(nums, start, pivotIdx - 1);
    quicksort(nums, pivotIdx + 1, end);
  }
}

void sortVecWithQuickSort(vector<int>& nums) {
  quicksort(nums, 0, nums.size() - 1);
}

int main() {
  /*ifstream file("dataQuickSort.txt");
  string line;
  vector<int> vec;
  while(getline(file, line)){
    vec.push_back(stoi(line));
  }*/

  vector<int> vec = {5, 3, 2, 6, 4, 8};

  // sort with quicksort
  //vector<int> sortedVec = sortVecWithMergeSort(vec);

  // sort with selection sort
  //sortVecWithSelectionSort(vec);

  // sort with bubble sort
  // sortVecWithBubbleSort(vec);

  // sort with insertion sort
  // sortVecWithInsertionSort(vec);

  // sort with quicksort
  sortVecWithQuickSort(vec);

  for (const auto& num : vec) {
    cout << num << ", ";
  }

  cout << '\n';

  return 0;
}