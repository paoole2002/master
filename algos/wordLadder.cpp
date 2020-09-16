#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <limits>
#define print(x)  std::cout<<x<<std::endl;
using namespace std;

struct StringMathcer{
    unordered_map<char,vector<string>> dict;
    unordered_map<string,int> memo; string target;
    int dfs(int idx){
        if(idx >= target.size()){
            return -1;
        }
        if(memo.count(to_string(idx)) > 0){
            return memo[to_string(idx)];
        }
        int ans = numeric_limits<int>::max(); // better use max int
        for(auto i = 0; i < dict[target[idx]].size(); i++){
            string num = dict[target[idx]][i];
            int j = 0; int k = idx; bool found = true; int curSize = num.size();
            if(num.size() > target.size() - idx){ continue; }
            while(j < num.size()){
                if(num[j++] != target[k++]){ found = false; break; }
            }
            if(found){ // if prefix was found recurse with the new index advanced by the word length
                int spaces = dfs(idx + curSize);
                ans = min(ans,spaces+1);
            }
        }
        memo[to_string(idx)] = ans;
        return ans;
    }
    int numbersInPi(string pi, vector<string> numbers) {
        target = pi;
        for(const auto & word : numbers){
            dict[word[0]].push_back(word);
        }
        print(dfs(0));
        return 0;
    }
};

int main(){
    StringMathcer sm;
    string pi = "3141592653589793238462643383279";
    vector<string> nums({"141592653589793238462643383279",
    "314159265358979323846",
    "327",
    "26433",
    "8",
    "3279",
    "9",
    "314159265",
    "35897932384626433832",
    "79",
    "3"});
    sm.numbersInPi(pi, nums);
    return 0;
}
