#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#define print(x) std::cout << x << std::endl;
using namespace std;
#define print3(x,y,z) cout << "start: " << x <<", end: "<<y<<", val: "<<z<<'\n';


struct Node{
    Node* left;
    Node* right;
    int start;
    int end;
    int val;
    Node(int s, int e) : left(nullptr), right(nullptr), start(s), end(e), val(0) {}
    Node(int s, int e, int v) : left(nullptr), right(nullptr), start(s), end(e), val(v) {}
};
/**
 * Class for Segment Tree
 */
class SegmentTree{
public:
    /**
     * Constructor, builds the tree from a vector
     */
    SegmentTree(vector<int>& nums) : mNums(nums) {
        int fullSum = 0;
        auto res = build(0, mNums.size()-1);
        tree = res.first;
    }
    
    /**
     * Updates a node of the tree with the value and then recursively
     * updates all the predecessor nodes with the new sums
     */
    void update(int start, int val){
        mNums.at(start) = val;
        auto root = tree;
        updateVal(root, start, val);
    }

    /**
     * Get the sum between indices start and end in O(logn)
     */
    int getSum(int start, int end){
        auto root = tree; mRes = 0;
        getRangeSum(root, start, end);
        return mRes;
    }

    /**
     * Print the tree
     */
    void printTree(){
        auto root = tree;
        logg(root);
    }
    int getFullSum(){ return tree->val; }
private:
    vector<int> mNums;
    Node* tree;
    int mRes = 0;
    
    /**
     * Builds tree recursively
     */
    std::pair<Node*,int> build(int start, int end){
        if(start > end){ return {nullptr, 0}; }
        if(start == end){ return { new Node(start, start, mNums.at(start)), mNums.at(start)}; }
        int leftSum = 0; int rightSum = 0;
        auto curTree = new Node(start, end);
        int mid = start + (end - start) / 2;
        curTree->start = start; curTree->end = end;
        auto left = build(start, mid);
        auto right = build(mid + 1, end);
        curTree->left = left.first; curTree->right = right.first;
        leftSum = left.second; rightSum = right.second;
        curTree->val = leftSum + rightSum;
        return { curTree, curTree->val};
    }

    /**
     * Updates the value
     */
    int updateVal(Node* root, int start, int val){
        if(!root){ return 0; }
        if(root->start == start && root->end == start){
            root->val = val;
            return root->val;
        }
        if(!root->left && !root->right){ return root->val; }
        int left = 0, right = 0;
        int mid = root->start + (root->end - root->start) / 2;
        if(start <= mid){
            left = updateVal(root->left, start, val);
            if(root->right){ right = root->right->val; }
        }
        else{
            right = updateVal(root->right, start, val);
            if(root->left){ left = root->left->val; }
        }
        root->val = left + right;
        return left + right;
    }

    /**
     * Get the sum between start and end
     */
    void getRangeSum(Node* root, int start, int end){
        if(!root){ return; }
        int mid = root->start + (root->end - root->start) / 2;
        if(start == root->start && end == root->end){ mRes += root->val; return; }
        if(start <= mid && end >= mid){
            getRangeSum(root->left, start, mid);
            getRangeSum(root->right, mid+1, end);
        }
        else if(end < mid){
            getRangeSum(root->left, start, end);
        }
        else if(start >= mid){
            getRangeSum(root->right, start, end);
        }
    }
    void logg(Node* tree){
        if(!tree){ return; }
        print3(tree->start, tree->end, tree->val);
        logg(tree->left);
        logg(tree->right);
    }
};
int main()
{
    vector<int> arr = {5,3,7,8,9,12,34,54,62,35,78,90};
    SegmentTree sg(arr);
    print(sg.getFullSum());
    // sg.update(0, 10);
    // sg.buildTree();
    print(sg.getFullSum());
    print(sg.getSum(0,arr.size()-2));
    return 0;
}