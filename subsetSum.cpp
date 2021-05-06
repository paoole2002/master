#include <iostream>
#include <vector>
using namespace std;
#define print(x) cout<<x<<endl;
#define printSer(x) cout<<x<<',';
#include <chrono>
// Return true if there exists a subsequence of arr[0..n) with given sum
bool subsetSum(int arr[], int n, int sum)
{
  auto tBegin = std::chrono::high_resolution_clock::now();
	// T[i][j] stores true if subset with sum j can be attained with
	// using items up to first i items
	bool T[n + 1][sum + 1];

  int closest = 0;
  int finalI = -1;
  int finalJ = -1;

	// if 0 items in the list and sum is non-zero
	for (int j = 1; j <= sum; j++)
		T[0][j] = false;

	// if sum is zero
	for (int i = 0; i <= n; i++)
		T[i][0] = true;

	// do for ith item
	for (int i = 1; i <= n; i++)
	{
		// consider all sum from 1 to sum
		for (int j = 1; j <= sum; j++)
		{
			// don't include ith element if j-arr[i-1] is negative
			if (arr[i - 1] > j)
				T[i][j] = T[i - 1][j];
			else
			// find subset with sum j by excluding or including the ith item
				T[i][j] = T[i - 1][j] || T[i - 1][j - arr[i - 1]];
      if(T[i][j] && j > closest){
        closest = j; // closest sum we reached so far
        finalI = i;
        finalJ = j; // update indices from which we will start backtracing
      }
		}
	}
  vector<int> steps;
  int i = finalI; int j = finalJ; // convenient  
  while(i > 0 && j >= 0){
    if(T[i][j] == T[i-1][j]){
      i--;
    }
    else{
      steps.push_back(arr[i]);
      j -= arr[i];
      i--;
    }
  }
  //print("Final steps");
  //for(auto& elem : steps){
  //  printSer(elem);
  //}
  cout<<endl;
  auto tEnd = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> duration = tEnd - tBegin;
  printSer("Time: ");
  print(duration.count()*1e-3);
	return T[n][sum];
}

// Subset Sum Problem
int main()
{
	// Input: set of items and a sum
	int arr[] = {25,25,25,25,25,25,25,25,25,50,50,50,50,50,50,50,50,50,
               100,100,100,100,100,100,100,100,100};
	int sum = 1426;

	// number of items
	int n = sizeof(arr) / sizeof(arr[0]);

	if (subsetSum(arr, n, sum))
		cout << "Yes";
	else
		cout << "No";

	return 0;
}