#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#define print(x)  std::cout<<x<<std::endl;
#define print2(x,y) std::cout<<x<<" , "<<y<<std::endl;
using namespace std;

struct NodeUF{
    int parent; int rank;
    NodeUF(int p, int r) : parent(p), rank(r) {};
};
struct Node{
    int from; int to; int cost;
    Node(int f, int t, int c) : from(f), to(t), cost(c) {}
    friend bool operator < (const Node & n1, const Node & n2){
        return n1.cost < n2.cost;
    }
};
/**
 * Idea is to build MST and then remove k-1 expensive edges, then we create the 4 clusters that are
 * most close to each other without creating a cycle (fso they remain clusters)
 */
struct Cluster{
    int size; int res = 0;
    vector<Node> nodes; vector<NodeUF> graph; vector<int> resVec;
    void parse(string filename){
        ifstream file(filename);
        string line; int cnt = 0;
        while(getline(file, line)){
            if(cnt == 0){cnt++; istringstream isa(line); int s; isa >> s; size = s; continue;}
            istringstream iss(line);
            int from, to, cost;
            iss >> from >> to >> cost;
            nodes.emplace_back(from, to, cost);
        }
    }
    int find(int x){
        if(graph[x].parent != x){
            graph[x].parent = find(graph[x].parent);
        }
        return graph[x].parent;
    }
    void unionFind(int x, int y, int cost){
        auto parentX = find(x);
        auto parentY = find(y);
        if(parentX == parentY){return;}
        resVec.push_back(cost);
        if(graph[parentX].rank > graph[parentY].rank){
            graph[parentY].parent = parentX;
        }
        else if(graph[parentX].rank < graph[parentY].rank){
            graph[parentX].parent = parentY;
        }
        else{
            graph[parentY].parent = parentX;
            graph[parentX].rank++;
        }
    }
    void runKruskal(){
        sort(nodes.begin(), nodes.end());
        // initialize union find data structure
        for(auto i = 0; i < size+1; i++){
            graph.emplace_back(i, 0);
        }
        for(auto & edge : nodes){
            unionFind(edge.from, edge.to, edge.cost);
        }
        print(resVec.at(resVec.size()-3));
    }
};
int main(){
    Cluster cluster;
    cluster.parse("clusterCase.txt");
    cluster.runKruskal(); // result is 106
    return 0;
}