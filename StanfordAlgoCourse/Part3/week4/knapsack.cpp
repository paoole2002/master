#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
using namespace std;

struct Knapsack{
    int mCapacity;
    int mSize;
    vector<long> mVals; 
    vector<int> mWeights;
    void parse(string filename){
        mVals.push_back(0);
        mWeights.push_back(0);
        int cnt = 0;
        ifstream file(filename);
        string line;
        while(getline(file, line)){
            istringstream cur(line);
            int a, b;
            cur >> a >> b;
            if(cnt == 0){
                mCapacity = a; mSize = b; cnt++;
            }
            else{
                mWeights.push_back(b);
                mVals.push_back((long)a);
            }
        }
    }
    void runAlgo(){
        vector<vector<long>> dp(mSize+1, vector<long>(mCapacity + 1,0));
        for(auto i = 1; i < mSize+1; i++){
            for(auto j = 0; j < mCapacity + 1; j++){
                if(i == 0){
                    dp[i][j] = 0;
                }
                else if(j >= mWeights[i]){
                    dp[i][j] = max(dp[i-1][j], dp[i-1][j - mWeights[i]] + mVals[i]);
                }
                else{
                    dp[i][j] = dp[i-1][j];
                }
            }
        }
    }
    
    void runAlgoSpaceOptimizes(){
        vector<long> dp(mCapacity + 1, 0); long res = 0;
        for(auto i = 0; i < mVals.size(); i++){
            for(auto j = mCapacity; j >= mWeights.at(i); j--){
                dp[j] = max(dp[j], mVals.at(i) + dp[j - mWeights.at(i)]);
                res = max(res, dp[j]);
            }
        }
    }
};
int main(){
    Knapsack kn;
    kn.parse("knapsackBig.txt");
    kn.runAlgo();
    kn.runAlgoSpaceOptimizes();
    return 0;
}