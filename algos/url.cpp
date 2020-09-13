using namespace std;
#include "iostream"
#include <fstream>
#include <string.h>
#include <stack>
#include <cctype> 
#define print(x)  std::cout<<x<<std::endl;

struct URL{
    stack<string> stak;
    string res;
    string shortenPath(string path) {
        int i = 0; bool slashFirst = false;
        if(path[0] == '/') { slashFirst = true; }
        while(i < path.size()){
            string word;
            if(path[i] == '/'){
                i++; continue;
            }
            int cntDots = 0;
            while(i < path.size() && path[i] == '.'){
                cntDots++; i++;
            }
            if(cntDots > 0){
                if(cntDots == 1){
                    continue;
                }
                else{
                    if(!stak.empty() && stak.top() != ".."){
                        stak.pop(); continue;
                    }
                    else{
                        stak.push("..");
                    }
                }
            }
            while(i < path.size() && isalpha(path[i])){
                word += path[i];
                i++;
            }
            if(!word.empty()){
                stak.push(word);
            }
        }
        while(!stak.empty()){
            if(slashFirst && stak.top() == ".."){
                stak.pop(); continue;
            }
            res = '/' + stak.top() + res;
            stak.pop();
        }
        if(!slashFirst){
            return res.substr(1, res.size()-1);
        }
        return res;
    }
};

int main(){
    struct URL url;
    auto res = url.shortenPath("../../../this////one/./../../is/../../going/../../to/be/./././../../../just/eight/double/dots/../../../../../..");
    print(res);
    return 0;
}

