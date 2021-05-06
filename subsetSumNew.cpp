#include <iostream>
#include <vector>
using namespace std;
#define print(x) cout<<x<<endl;
#define printSer(x) cout<<x<<',';
#include <chrono>
#include <algorithm>

struct Node{
  size_t idx;
  int val;
  Node(size_t i, int v) : idx(i), val(v) {}
  friend bool operator< (const Node& n1, const Node& n2){
    return n1.val < n2.val;
  }
};
// Return true if there exists a subsequence of arr[0..n) with given sum
bool subsetSum(std::vector<Node> bVals, int target)
{
  int size = bVals.size();
  auto tBegin = std::chrono::high_resolution_clock::now();

  std::vector<std::vector<bool>> dp(size+1, std::vector<bool>(target+1, false));

	// if 0 items in the list and sum is non-zero
	for (unsigned int i = 0; i <= size; i++){ // target 0 is true
    dp.at(i).at(0) = true;
  }

  auto step = -1; // store final indices of 2d vector of the closest value to target
  auto val = -1; // we reached
  // do for ith item
  for (unsigned int i = 1; i <= size; i++) {
    // consider all target from 1 to sum
    for (int j = 1; j <= target; j++)
    {
      // don't include ith element if j-arr[i-1] is negative
      if (bVals[i - 1].val > j){
        dp.at(i).at(j) = dp.at(i-1).at(j);
      }
      else{
      // find subset with sum j by excluding or including the ith item
        dp.at(i).at(j) = dp.at(i-1).at(j) || dp.at(i - 1).at(j - bVals.at(i - 1).val);
      }
      if(dp.at(i).at(j) && j > val){
        step = i;
        val = j; // update indices from which we will start backtracing
      }
    }
  }
  vector<int> steps;
  while(step > 0 && val >= 0){
    if(dp.at(step).at(val) == dp.at(step-1).at(val)){
      step--;
    }
    else{
      steps.push_back(bVals.at(step-1).idx);
      val -= bVals.at(step-1).val;
      step--;
    }
  }
  print("Final steps");
  for(auto& elem : steps){
    printSer(elem);
  }
  cout<<endl;
  auto tEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = tEnd - tBegin;
  printSer("Time: ");
  print(duration.count()*1e-3);
	return dp[size][target];
}

// Subset Sum Problem
int main()
{
	// Input: set of items and a sum
  std::vector<std::vector<int>> arr {{25,25,25,25,25,25,25,25,25},
                                     {50,50,50,50,50,50,50,50,50},
                                     {100,100,100,100,100,100,100,100,100}};
  std::vector<Node> susc;

  for(auto i = 0; i < arr.size(); i++){
    for(const auto& val : arr.at(i)){
      susc.emplace_back(i, val);
    }
  }

  std::sort(susc.begin(), susc.end());
  int target = 1151;
  auto res = subsetSum(susc, target);
	return 0;
}