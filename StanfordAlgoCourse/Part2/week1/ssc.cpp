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

struct ConnectedComponents{
    int nodes;
    int nodesInStrongConnectedComponent = 0;
    vector<bool> visited; // keep track of which nodes visited to avoid revisiting - cycles
    vector<int> nodesReOrdered; // fix order of nodes for second pass (we want opposite order)
    unordered_map<int,vector<int>> forward; // forward adjacency list
    unordered_map<int, vector<int>> backward; // backward adjacency list
    vector<int> res;

    /**
     * Constructor and calls the required functions to compute strongly connected components
     * @param size number of nodes in directed graph
     */
    ConnectedComponents(int size, string filename) : nodes(size)
    {
        parse(filename);
        visited.resize(nodes+1, false); // initially all nodes unvisited
        firstPass();
        fill(visited.begin(), visited.end(), false); // render all nodes unvisited again
        secondPass();
        sort(res.begin(), res.end()); // for assignemnt purposes only
        for(auto i = res.size()-1; i >= res.size()-5; i--){
            print(res.at(i));
        }
    };

    /**
     * Parse the given file and create the forward and backward graph
     * @param fileName name of input file
     */
    void parse(string fileName){
        string line;
        ifstream file(fileName);
        while(getline(file, line)) // To get you all the lines.
        {
            std::istringstream iss(line);
            int a, b;
            iss >> a >> b;
            forward[a].push_back(b);
            backward[b].push_back(a);
        }
        file.close();
    }


    /**
     * First pass for DFS starting at every node (unless visited) in the reversed graph to get
     * order of iteration for second run of DFS in the forward graph
     */
    void firstPass(){
        for(auto node = nodes; node > 0; node--){
            if(!visited.at(node)){
                dfs(node, backward, true);
            }
        }
    }


    /**
     * Second pass of DFS in forward graph, gives out the connected components along with number
     * of nodes in each
     */
    void secondPass(){
        vector<int>::reverse_iterator it = nodesReOrdered.rbegin();
        for(; it != nodesReOrdered.rend(); ++it){
            if(!visited.at(*it)){
                nodesInStrongConnectedComponent = 0;
                dfs(*it, forward, false);
                res.push_back(nodesInStrongConnectedComponent); // found a strong connecected component
            }
        }
    }


    /**
     * DFS from a starting node
     * @param node starting node of DFS
     * @param d graph representation 
     * @param add boolean to avoid appending to vector during second pass
     */
    void dfs(int node, unordered_map<int,vector<int>> & d, bool add){
        visited.at(node) = true;
        if(d.count(node) > 0){
            for(const auto child : d[node]){
                if(!visited.at(child)){
                    dfs(child, d, add);
                }
            }
        }
        nodesInStrongConnectedComponent++;
        if(add){ // if we are in the first DFS on the reverse graph
            nodesReOrdered.push_back(node); // like a topological sort the nodes with higher visiting //times - deeper nodes on DFS will be visited last, thus in second loop we iterate this
            //vector in reverse
        }
    }
};


int main()
{
    // driver codes
    ConnectedComponents comp(875714, "SSCom1"); // initialize with number of nodes
    return 0;
}