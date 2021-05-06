#include <vector>
#include <iostream>
using namespace std;

class MergeSort{
public:
  MergeSort() = default;
  vector<int> getSortedVec(vector<int>& vec){
    mergesort(vec, 0, vec.size() - 1);
    return vec;
  }
private:
  void merge(vector<int>& vec, int start, int mid, int end){
    int l1 = start;
    int lim1 = mid;
    int l2 = mid + 1;
    int lim2 = end;
    vector<int> temp(end - start + 1); int k = 0;
    while(l1 <= lim1 && l2 <= lim2){
      if(vec[l1] < vec[l2]){
        temp[k] = vec[l1++];
      }
      else{
        temp[k] = vec[l2++];
      }
      k++;
    }
    while(l1 <= lim1){ temp[k++] = vec[l1++]; }
    while(l2 <= lim2){ temp[k++] = vec[l2++]; }
    for(int i = start; i <= end; i++){
      vec[i] = temp[i - start];
    }
  }
  void mergesort(vector<int>& vec, int start, int end){
    if(start >= end){ return; }
    int mid = start + (end - start) / 2;
    mergesort(vec, start, mid);
    mergesort(vec, mid + 1, end);
    merge(vec, start, mid, end);
  }
};


class QuickSort{
public: 
  QuickSort() = default;
  vector<int> mysort(vector<int>& nums){
    quicksort(nums, 0, nums.size() - 1);
    return nums;
  }
private:
  void swap(vector<int>& nums, int i, int j){
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
  }
  int findPivot(vector<int>& nums, int start, int end){
    int wall = start + 1;
    int pivot = nums[start];
    for(size_t i = start + 1; i <= end; i++){
      if(nums[i] < pivot){
        swap(nums, i, wall);
        wall++;
      }
    }
    swap(nums, start, wall - 1);
    return wall - 1;
  }
  void quicksort(vector<int>& nums, int start, int end){
    if(start >= end){ return; }
    int pivot = findPivot(nums, start, end);
    quicksort(nums, start, pivot - 1);
    quicksort(nums, pivot + 1, end);
  }
};

int main() {
  vector<int> vec = {10,5,2,7,5,2,10,2,4,6,1,8,3};
  // vector<int> vec = {3,1,2,5,4};
  // MergeSort mrg;
  // vector<int> sortedVec = mrg.getSortedVec(vec);
  // for(const int& num : sortedVec){
  //   cout << num << ", ";
  // }
  // cout << endl;
  QuickSort q;
  vector<int> quickVec = q.mysort(vec);
  for(const int& num : quickVec){
    cout << num << ", ";
  }
  cout << endl;
  return 0;
}