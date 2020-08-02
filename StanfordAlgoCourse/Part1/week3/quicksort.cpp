#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <queue>
#define print(x)  std::cout<<x<<std::endl;
using namespace std;

struct Node{
  int val;
  int idx;
  Node(int value, int index){
    this->val = value;
    this->idx = index;
  }
};

struct Compare{
  bool operator()(Node a, Node b){
    return a.val < b.val;
  }
};

int res = 0;
void swap(vector<int> & arr, int i, int j){
  int temp = arr.at(i);
  arr.at(i) = arr.at(j);
  arr.at(j) = temp;
}

int partition(vector<int> & arr, int l, int r){
  priority_queue<Node, vector<Node>, Compare> q;
  q.emplace(arr.at(l), l);
  q.emplace(arr.at(r - 1), r - 1);
  q.emplace(arr.at(l+(r-1-l)/2), l+(r-1-l)/2);
  q.pop();
  int pivIdx = q.top().idx;
  swap(arr, l, pivIdx);
  int pivot = arr.at(l);
  res += r - l - 1;
  int i = l + 1;
  for (auto j = l + 1; j < r; j++){
    if(arr.at(j) < pivot){
      swap(arr, j, i);
      i++;
    }
  }
  swap(arr, l, i - 1);
  return i-1;
}
void quickSort(vector<int> & arr, int l, int r)
{
  if(l >= r){
    return;
  }
  int split = partition(arr, l, r);
  quickSort(arr, l, split);
  quickSort(arr, split+1, r);
}
int main()
{
  ifstream file("dataQuickSort.txt");
  string line;
  vector<int> vec;
  while(getline(file, line)){
    vec.push_back(stoi(line));
  }
  quickSort(vec, 0, vec.size());
  print(res);
  return 0;
}