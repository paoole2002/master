#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#define print(x)  std::cout<<x<<std::endl;
using namespace std;

static int MOD =  10e5 + 7;
static int PRIME = 227;
class Hash{
public:
    void runAlgo(string s1, string tar){
        auto tarSize = tar.size();
        int hashTarget = hash(tar);
        int rollHash = hash(s1.substr(0,tarSize));
        auto power = getPower(tarSize);
        if(hashTarget == rollHash){
            starts.push_back(0);
            ends.push_back(tarSize - 1);
        }
        for(auto i = tarSize; i < s1.size(); i++){
            rollHash = rollHash * PRIME + s1[i];
            rollHash %= MOD;
            rollHash = (rollHash - power * s1[i-tarSize]) % MOD;
            if(rollHash < 0){
                rollHash += MOD;
            }
            rollHash %= MOD;
            if(rollHash == hashTarget){ // keep track of starting and ending indices of matching substr
                int start = i - tarSize + 1;
                int end = i;
                if(!ends.empty() && end - ends.at(ends.size()-1) <= tarSize){
                    ends.pop_back(); ends.push_back(end);
                }
                else{
                    starts.push_back(start); ends.push_back(end);
                }
            }
            print(rollHash);
        }
    }
private:
    vector<int> starts; vector<int> ends;
    int getPower(int len){
        int power = 1;
        for(auto i = 1; i <= len; i++){ // have to go one power more than the size of target string
            power = (power * PRIME) % MOD;
        }
        return power;
    }
    int hash(string s){
        int res = 0;
        for(auto i = 0; i < s.size(); i++){
            res = PRIME*res + s[i];
            res %= MOD;
        }
        return res;
    }
};

int main(){
    Hash h;
    string s1 = "abcabcabcabcabcabcabcabcabcabcabcabcabcabc";
    string s2 = "abc";
    h.runAlgo(s1, s2);
    return 0;
}