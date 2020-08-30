#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <unordered_map>
#define print(x)  std::cout<<x<<std::endl;
#define print2(x,y) std::cout<<x<<" , "<<y<<std::endl;
using namespace std;
#include <chrono> 
using namespace std::chrono; 

struct TwoSum{
    // variables
    unordered_map<long long, long long> nums;
    int res = 0;
    void parse(string filename){
        ifstream file(filename);
        string line;
        long long curNum;
        long long cnt;
        while(getline(file, line)){
            cnt++;
            std::istringstream iss(line);
            iss >> curNum;
            if(nums.count(curNum) == 0){
                nums[curNum] = curNum;
            }
        }
    }

    void distinctPairs(){
        auto start = high_resolution_clock::now(); 
        for(auto t = -10000; t < 10001; t++){
            for(auto & [x, xRep] : nums){
                if(nums.count(t - x) > 0 && nums[t-x] != xRep){
                    print2(x, t-x);
                    res++;
                    break;
                }
            }
        }
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<microseconds>(stop - start); 
        print(res);
        print2(duration.count(), "s");
    }
};
int main()
{
    TwoSum twoSumUnique;
    twoSumUnique.parse("2sum.txt");
    twoSumUnique.distinctPairs();
    return 0;
}