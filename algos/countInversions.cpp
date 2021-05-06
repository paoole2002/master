#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#define print(x)  std::cout<<x<<std::endl;
using namespace std;

pair<vector<int>, long long> merge(vector<int>& left, vector<int>& right){
  int i = 0;
  int j = 0;
  long long inv = 0;
  vector<int> res;
  while(i < left.size() && j < right.size()){
    if(left.at(i) < right.at(j)){
      res.push_back(left.at(i++));
    }
    else{
      res.push_back(right.at(j++));
      inv += (left.size() - i);
    }
  }
  while(i < left.size()){
    res.push_back(left.at(i++));
  }
  while(j < right.size()){
    res.push_back(right.at(j++));
  }
  return make_pair(res, inv);
}

pair<vector<int>, long long> mergeSort(vector<int>& arr){
  if(arr.size() <= 1){
    return make_pair(arr, 0);
  }
  vector<int> left, right, result;
  int mid = arr.size() / 2;
  for (auto i = 0; i < mid; i++){
    left.push_back(arr.at(i));
  }
  for (auto i = mid; i < arr.size(); i++){
    right.push_back(arr.at(i));
  }
  auto l = mergeSort(left);
  auto r = mergeSort(right);
  auto both = merge(l.first, r.first);
  return make_pair(both.first, l.second + r.second + both.second);
}
int main(){
  ifstream file("sampleInput.txt");
  string line;
  vector<int> vec;
  while(getline(file, line)){
    vec.push_back(stoi(line));
  }
  auto out = mergeSort(vec);
  print(out.second)
  return 0;
}