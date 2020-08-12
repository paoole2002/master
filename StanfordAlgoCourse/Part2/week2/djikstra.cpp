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

/**
 * Helper struct for the priority queue 
 */
struct Node{
    int node = -1;
    int cost = -1;
    Node(int nodeVal, int curCost){
        this->node = nodeVal;
        this->cost = curCost;
    };
};

/**
 * Custom comparator for priority queue
 */
struct Comp{
    bool operator()(Node a, Node b){
        return a.cost > b.cost;
    }
};

/**
 * Struct with the djikstra algorithm and parsing the input file
 */
struct Djikstra{
    // struct members
    unordered_map<int, unordered_map<int, int>> mGraph;
    vector<int> mDist;

    /**
     * Parse the file and create graph representation along with costs
     * @param filename name of input file
     */
    void parse(string filename){
        ifstream file(filename);
        string str;
        string file_contents;
        while (getline(file, str)) {
            int i = 0;
            string node;
            while(str[i] != '\t' && str[i] != ' '){
                node += str[i]; i++;
            }
            i++;
            while(i < str.size() -1){
                string child; string cost;
                while(str[i] != ','){
                    child += str[i]; i++;
                }
                i++;
                while(i < str.size() && str[i] != '\t' && str[i] != ' ' && str[i] != '\n'){
                    cost += str[i]; i++;
                }
                i++;
                mGraph[stoi(node)][stoi(child)] = stoi(cost);
            }
        }
        file.close();
    }

    /**
     * Parse the file and create graph representation along with costs
     * @param startVertex start vertex of the algorithm
     */
    void runDjikstra(int startVertex){
        mDist.resize(mGraph.size()+1); fill(mDist.begin(), mDist.end(), 1000000);
        mDist[1] = 0;
        vector<bool> visited(mGraph.size()+1, false);
        priority_queue<Node, vector<Node>, Comp> q;
        q.emplace(startVertex, 0);
        while(!q.empty()){
            int size = q.size();
            for(auto i = 0; i < size; i++){
                auto node = q.top().node;
                auto curCost = q.top().cost; // minimum cost up to current node
                q.pop();
                visited[node] = true;
                for(const auto & [child, cost] : mGraph[node]){
                    if(!visited[child]){
                        if(mDist[child] > curCost + cost){ // append cost of edge node-child
                            mDist[child] = curCost + cost;
                        }
                        q.emplace(child, curCost + cost);
                    }
                }
            }
        }
    }

    // For assignemnt purposes
    void printRes(){
        print2(7, mDist[7]);
        print2(37, mDist[37]);
        print2(59, mDist[59]);
        print2(82, mDist[82]);
        print2(99, mDist[99]);
        print2(115, mDist[115]);
        print2(133, mDist[133]);
        print2(165, mDist[165]);
        print2(188, mDist[188]);
        print2(197, mDist[197]);
    }
};

int main(){
    Djikstra djikstra;
    djikstra.parse("djikstra.txt"); // input file
    djikstra.runDjikstra(1); // start vertex as requested per assignment
    djikstra.printRes();
    return 0;
}