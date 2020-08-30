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

struct Job{
    int length;
    int weight;
    Job(int l, int w) : length(l), weight(w) {};
};

struct CompDiff{
    bool operator () (const Job & j1, const Job & j2) const{
        if(j1.weight - j1.length == j2.weight - j2.length){
            return j1.weight < j2.weight;
        }
        return j1.weight - j1.length > j2.weight - j2.length;
    }
};

struct CompRatio{
    bool operator () (const Job& j1, const Job & j2) const{
        return j1.weight * 1.0 / j1.length > j2.weight * 1.0 / j2.length;
    }
};

struct TaskScheduler{
    vector<Job> jobs;
    void parse(string filename){
        ifstream file(filename);
        string line; int cnt = 0;
        while(getline(file, line)){
            if(cnt > 0){
                istringstream iss(line);
                int weight, length;
                iss >> weight >> length;
                jobs.emplace_back(weight, length);
            }
            cnt++;
        }
    }

    int getMinWeightSumCompletionTimeDiff(){
        long long res = 0;
        sort(jobs.begin(), jobs.end(), CompDiff());
        long long finishTime = 0;
        for(const auto & job : jobs){
            finishTime += job.length;
            res += finishTime * job.weight;
        }
        print2("diff",res);
        return res;
    }

    int getMinWeightSumCompletionTimeRatio(){
        long long res = 0;
        sort(jobs.begin(), jobs.end(), CompRatio());
        long long finishTime = 0;
        for(const auto & job : jobs){
            finishTime += job.length;
            res += finishTime * job.weight;
        }
        print2("ratio",res);
        return res;
    }
};
int main(){
    TaskScheduler task;
    task.parse("jobs.txt");
    task.getMinWeightSumCompletionTimeDiff();
    task.getMinWeightSumCompletionTimeRatio();
    return 0;
}