#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#define print(x)  std::cout<<x<<std::endl;
using namespace std;

struct Graph{
    vector<bool> mFinalSeqIndices;
    vector<long long> mArr;
    int mSize;

    void parse(string filename){
        ifstream file(filename);
        string line; int cnt = -1;
        while(getline(file, line)){
            istringstream iss(line);
            long long curWeight;
            iss >> curWeight;
            if(cnt == -1){
                mSize = (int)curWeight; cnt++;
                continue;
            }
            mArr.push_back(curWeight);
            cnt++;
        }
    }

    void runAlgo(){
        vector<long long> dp(mArr.size(), 0);
        mFinalSeqIndices.resize(mSize + 1);
        fill(mFinalSeqIndices.begin(), mFinalSeqIndices.end(), false);
        dp.at(0) = mArr.at(0);
        dp.at(1) = mArr.at(1);
        for(auto i = 2; i < mArr.size(); i++){
            dp[i] = max(dp.at(i-1), dp.at(i-2) + mArr.at(i));
        }
        int idx = mArr.size()-1;
        while(idx >= 2){
            if(mArr.at(idx) + dp.at(idx - 2) <= dp.at(idx-1)){
                idx--;
            }
            else{
                mFinalSeqIndices[idx + 1] = true;
                idx -= 2;
                if(idx < 2){
                    mFinalSeqIndices[idx+1] = true;
                }
            }
        }
    }
};
int main(){
    Graph g;
    g.parse("graphDp.txt");
    g.runAlgo();
    return 0;
}