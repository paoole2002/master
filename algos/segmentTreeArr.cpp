#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#define print(x) std::cout << x << std::endl;
using namespace std;
#define print3(x,y,z) cout << "start: " << x <<", end: "<<y<<", val: "<<z<<'\n';

/**
 * Class for Segment Tree
 */
class SegmentTree{
public:
    /**
     * Constructor, builds the tree from a vector
     */
    SegmentTree(vector<int>& nums) : mNums(nums) {
      // get closer power of 2
      int sz = getPow2(nums.size());
      mTree.resize(sz);
      build(0, 0, nums.size() - 1);
    }
    
    /**
     * Updates a node of the tree with the value and then recursively
     * updates all the predecessor nodes with the new sums
     */
    void update(int idx, int val){
      updateVal(0, 0, mNums.size() - 1, idx, val);
    }

    /**
     * Get the sum between indices start and end in O(logn)
     */
    int getSum(int start, int end){
      return getRangeSum(0, 0, mNums.size() - 1, start, end);
    }

    /**
     * Print the tree
     */
    void printTree(){
        for(const int& num : mTree) { cout << num << ", "; }
        cout << endl;
    }
    int getFullSum(){ return mTree[0]; }
private:
    vector<int> mNums;
    vector<int> mTree;
    int mRes = 0;
    
    int getPow2(int val) { int cur = 1; while(cur < val) { cur *= 2; } return cur; }

    /**
     * Builds tree recursively
     */
    void build(int node, int start, int end){
      if(start == end) { mTree[node] = mNums[start]; return; }
      int mid = start + (end - start) / 2;
      build(2 * node + 1, start, mid);
      build(2 * node + 2, mid + 1, end);
      mTree[node] = mTree[2 * node + 1] + mTree[2 * node + 2];
    }

    /**
     * Updates the value
     */
    void updateVal(int node, int start, int end, int idx, int val){
      if(start == end) {
        mTree[node] = val; return;
      }
      int mid = start + (end - start) / 2;
      if(idx > mid){
        updateVal(2 * node + 2, mid + 1, end, idx , val);
      }
      else{
        updateVal(2 * node + 1, start, mid, idx , val);
      }
      mTree[node] = mTree[2 * node + 1] + mTree[2 * node + 2];
    }

    /**
     * Get the sum between start and end
     */
    int getRangeSum(int node, int start, int end, int rStart, int rEnd){
      // first check for out of requested range
      if(rEnd < start || rStart > end) return 0;
      // check for full coverage of range
      if(start <= rStart && end <= rEnd) return mTree[node];
      int mid = start + (end - start) / 2;
      int l = getRangeSum(2 * node + 1, start, mid, rStart, rEnd);
      int r = getRangeSum(2 * node + 2, mid + 1, end, rStart, rEnd);
      return l + r;
    }
};
int main()
{
    // vector<int> arr = {5,3,7,8,9,12,34,54,62,35,78,90};
    vector<int> arr = {0,9,5,7,3};
    SegmentTree sg(arr);
    sg.printTree();
    // print(sg.getFullSum());
    print(sg.getSum(2, 4));
    // print(sg.getSum(2,4));
    sg.update(0, 2);
    sg.printTree();
    print(sg.getSum(1,4));
    // print(sg.getSum(3,3));
    // sg.buildTree();
    // print(sg.getFullSum());
    // print(sg.getSum(0,arr.size()-2));
    return 0;
}