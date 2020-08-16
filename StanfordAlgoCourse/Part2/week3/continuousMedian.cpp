#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#define print(x)  std::cout<<x<<std::endl;
#define print2(x,y) std::cout<<x<<" , "<<y<<std::endl;
using namespace std;

struct Comp{
    bool operator()(int a, int b) const
    {
        return a > b;
    }
};
struct ContinuousMedian{
    priority_queue<int, vector<int>, Comp> qLarger;
    priority_queue<int, vector<int>> qSmaller;
    vector<int> nums;
    int curSum = 0;
    void parse(string filename)
    {
        ifstream file(filename);
        string line;
        while(getline(file, line)){
            std::istringstream iss(line);
            int a;
            iss >> a;
            nums.push_back(a);
        }
        file.close();
    }

    void getMedian()
    {
        for(auto i = 0; i < nums.size(); i++){
            if(qLarger.size() == qSmaller.size()){
                if(qLarger.empty()){
                    qLarger.push(nums.at(i));
                }
                else{
                    int num = qSmaller.top();
                    if(nums.at(i) < num){
                        qLarger.push(qSmaller.top()); qSmaller.pop();
                        qSmaller.push(nums.at(i));
                    }
                    else{
                        qLarger.push(nums.at(i));
                    }
                }
            }
            else{
                int num = qLarger.top();
                if(nums.at(i) < num){
                    qSmaller.push(nums.at(i));
                }
                else{
                    qSmaller.push(qLarger.top()); qLarger.pop();
                    qLarger.push(nums.at(i));
                }
            }
            if(qLarger.size() == qSmaller.size()){
                curSum += (qSmaller.top());
            }
            else{
                curSum += (qLarger.top());
            }
        }
        curSum %= 10000;
        print(curSum % 10000);
    }
};
int main()
{
    ContinuousMedian median;
    median.parse("median.txt");
    median.getMedian();
    return 0;
}