#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <unordered_set>
#define print(x)  std::cout<<x<<std::endl;
#define print2(x,y) std::cout<<x<<" , "<<y<<std::endl;
using namespace std;

struct Node{
    int vertex; int cost;
    Node(int v, int c) : vertex(v), cost(c) {}
    friend bool operator < (const Node& n1, const Node& n2){
        return n1.cost > n2.cost;
    }
};
struct Prims{
    unordered_map<int, vector<Node>> graph;
    priority_queue<Node, vector<Node>> q;
    unordered_set<int> visited;
    long long res = 0;
    void parse(string filename){
        ifstream file(filename);
        string line; int cnt = 0;
        while(getline(file, line)){
            if(cnt == 0){cnt++; continue;}
            istringstream iss(line);
            int from,to,cost;
            iss >> from >> to >> cost;
            graph[from].emplace_back(to, cost);
            graph[to].emplace_back(from, cost);
        }
    }
    void run(){
        for(auto & elem : graph[1]){
            q.emplace(elem.vertex, elem.cost);
        }
        visited.insert(1);
        while(!q.empty()){
            int size = q.size();
            for(auto i = 0; i < size; i++){
                auto node = q.top(); q.pop();
                if(visited.count(node.vertex) == 0){
                    visited.insert(node.vertex);
                    res += node.cost;
                    for(auto child : graph[node.vertex]){
                        q.emplace(child.vertex, child.cost);
                    }
                }
            }
        }
        print(res);
    }
};
// -3612829
int main(){
    Prims runPrims;
    runPrims.parse("primsToy.txt");
    runPrims.run();
    return 0;
}
