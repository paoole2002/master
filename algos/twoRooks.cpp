#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <limits>
#define print(x)  std::cout<<x<<std::endl;
using namespace std;

struct Node{
  int mVal = 0; int mPos = 0;
  Node() = default;
  Node(int v, int p) : mVal(v), mPos(p) {}
};

int main(){
  //vector<vector<int>> v = {{2,0,1,0}, {0,1,1,1}, {1,1,1,0},{0,1,0,2}};
  vector<vector<int>> v = {{5,6},{9,8}};
  
  if(v.empty()){ return 0; }
  if(v.at(0).empty() || v.size() < 2){ return 0; }

  vector<vector<Node>> mRows(v.size(), vector<Node>(2));
  vector<vector<Node>> mCols(v.at(0).size(), vector<Node>(2));
  
  // for rows
  for(unsigned int i = 0; i < v.size(); i++){
    auto max1 = numeric_limits<int>::min();
    auto max2 = numeric_limits<int>::min();
    auto col1 = -1; auto col2 = -1;
    for(unsigned int j = 0; j < v.at(i).size(); j++){
      auto num = v.at(i).at(j);
      if(num > max1) {
        max2 = max1; col2 = col1;
        max1 = num; col1 = j;
      }
      else if (num > max2){
        max2 = num;
        col2 = j;
      }
    }
    mRows.at(i).at(0) = {max1, col1}; mRows.at(i).at(1) = {max2, col2};
  }

  // for cols
  for(unsigned int i = 0; i < v.at(0).size(); i++){
    auto max1 = numeric_limits<int>::min();
    auto max2 = numeric_limits<int>::min();
    auto col1 = -1; auto col2 = -1;
    for(unsigned int j = 0; j < v.size(); j++){
      auto num = v.at(j).at(i);
      if(num > max1) {
        max2 = max1; col2 = col1;
        max1 = num; col1 = j;
      }
      else if (num > max2){
        max2 = num;
        col2 = j;
      }
    }
    mCols.at(i).at(0) = {max1, col1}; mCols.at(i).at(1) = {max2, col2};
  }

  // for whole
  int mRes = numeric_limits<int>::min();

  for (unsigned int i = 0; i < v.size(); i++){
    // check maxSum between max of that row and max of other columns
    auto max1 = mRows.at(i).at(0).mVal;
    auto col1 = mRows.at(i).at(0).mPos;
    for (unsigned int j = 0; j < v.at(i).size(); j++){
      if(j == col1) { continue; }
      auto maxNode = mCols.at(j).at(0);
      if(maxNode.mPos == i){
        mRes = max(mRes, max1 + mCols.at(j).at(1).mVal);
      }
      else{
        mRes = max(mRes, max1 + maxNode.mVal);
      }
    }
    // check maxSum between second max of that row and all columns
    auto max2 = mRows.at(i).at(1).mVal;
    auto col2 = mRows.at(i).at(1).mPos;
    for (unsigned int j = 0; j < v.at(i).size(); j++){
      if(j == col2) { continue; }
      auto maxNode = mCols.at(j).at(0);
      if(maxNode.mPos == i){
        mRes = max(mRes, max2 + mCols.at(j).at(1).mVal);
      }
      else{
        mRes = max(mRes, max2 + maxNode.mVal);
      }
    }
  }
  print(mRes);
  return mRes;
}