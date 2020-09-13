#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#define print(x)  std::cout<<x<<std::endl;
using namespace std;

class PatternMatcher{
public:
    vector<string> runAlgo(string str, string pattern){
        if(pattern[0] == 'y'){ swapped = true; pattern = swap(pattern); }
        auto [cntX, cntY] = getCnts(pattern);
        if(cntY == 0){ // if pattern contains one letter our job is simple
            if(str.size() % cntX != 0){ return {}; }
            string target = str.substr(0, cntX);
            for(auto i = cntX; i < str.size(); i += cntX){
                string substr = str.substr(i, cntX);
                if(substr != target){ return {}; }
            }
            if(!swapped) { return {target, " "}; }
            else{ return {" ", target}; }
        }
        int firstY = getFirstY(pattern); // equals to how many X are before the first y occurence
        string a; string b; int limit = str.size() / cntX;
        for(auto i = 1; i <= limit; i++){
            a = ""; b= "";
            int cnty = getLen(cntX, cntY, i, str.size()); auto found = true;
            if(cnty == -1){ continue; }
            a = str.substr(0, i);
            for(auto j = a.size(); j < firstY * a.size(); j += a.size()){
                if(str.substr(j, a.size()) != a){
                    found = false; break;
                }
            }
            if(found){
                b = str.substr(a.size() * firstY, cnty);
            }
            else{
                continue;
            }
            int curIdx = firstY*a.size() + b.size();
            int j = firstY + 1;
            while(curIdx < str.size() && j < pattern.size()){
                if(pattern[j] == 'x'){
                    if(str.substr(curIdx, a.size()) != a){ break; }
                    else{ curIdx += a.size();}
                }
                else{
                    if(str.substr(curIdx, b.size()) != b){ break; }
                    else{ curIdx += b.size(); }
                }
                j++;
            }
            if((!a.empty() || !b.empty()) && j == pattern.size()){
                if(!swapped){ return {a, b}; }
                else{ return {b, a}; }
            }
        }
    }
private:
    bool swapped = false;
    // returns counts of X and Y of the pattern
    pair<int,int> getCnts(string pattern){
        int x = 0; int y = 0;
        for(auto & ch : pattern){
            if(ch == 'x'){ x++; }
            else if(ch == 'y') { y++ ;}
        }
        return make_pair(x,y);
    }
    // Solves a*X + b*y = str.size()
    double getLen(int cntA, int cntB, int cur, int size){
        if(cntB == 0){ return -1; }
        if((size - cntA * cur) % cntB == 0){
            return (size - cntA * cur) / cntB;
        }
        return -1;
    }
    // swaps pattern to have all X in front
    string swap(string s){
        string res;
        for(auto & ch : s){
            if(ch == 'x'){ res += 'y'; }
            else{ res += 'x'; }
        }
        return res;
    }
    // concept is to have all X in front of pattern to try their valid combinations and then get first
    // Y combination. We know the length of the Y substring because we know the length of X substring
    // and we have the counts of X and Y in pattern
    int getFirstY(string pattern){
        for(auto i = 0; i < pattern.size(); i++){
            if(pattern[i] == 'y') { return i; }
        }
        return -1;
    }
};
int main(){
    PatternMatcher pt;
    string s = "baddaddoombaddaddoomibaddaddoombaddaddoombaddaddoombaddaddoomibaddaddoomibaddaddoom";
    string pattern = "yxyyyxxy";
    auto res = pt.runAlgo(s, pattern);
    for(auto ch : res){
        print(ch);
    }
    return 0;
}