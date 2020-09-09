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

struct Node{
    int maxFreq, minFreq;
    long long weight;
    Node(int minf, int maxf, long long w) : minFreq(minf), maxFreq(maxf), weight(w) {}
    friend bool operator < (const Node & n1, const Node & n2){
        return n1.weight > n2.weight;
    }
};
struct Huffman{
    priority_queue<Node, vector<Node>> q;
    int mSize;
    int mMinFreq = 0;
    void parse(string filename){
        ifstream file(filename);
        string line; int cnt = -1;
        while(getline(file, line)){
            istringstream iss(line);
            long long curWeight;
            iss >> curWeight;
            if(cnt == -1){
                mSize = (int)curWeight; cnt++; continue;
            }
            q.emplace(0, 0, curWeight); cnt++;
        }
    }
    void build(){
        while(q.size() >= 2){
            auto node1 = q.top(); q.pop();
            auto node2 = q.top(); q.pop();
            auto maxF = max(node1.maxFreq, node2.maxFreq);
            auto minF = min(node1.minFreq, node2.minFreq);
            q.emplace(minF + 1,maxF + 1, node1.weight + node2.weight);
        }
        print(q.top().maxFreq); //δεκαεννια
        print(q.top().minFreq); //εννια
    }
};
int main(){
    Huffman huff;
    huff.parse("huffman.txt");
    huff.build();
    return 0;
}