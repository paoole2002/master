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
class SegmentTree{
public:
    SegmentTree(vector<int>& nums) : mNums(nums) {}
    void buildTree(){
        int fullSum = 0;
        auto res = build(0, mNums.size()-1);
        tree = res.first;
    }
    void update(int start, int val){
        mNums.at(start) = val;
        auto root = tree;
        updateVal(root, start, val);
    }
    int getSum(int start, int end){
        auto root = tree; mRes = 0;
        getRangeSum(root, start, end);
        return mRes;
    }
    void printTree(){
        auto root = tree;
        logg(root);
    }
    int getFullSum(){ return tree->val; }
private:
    vector<int> mNums;
    Node* tree;
    int mRes = 0;
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

    void getRangeSum(Node* root, int start, int end){
        if(!root){ return; }
        int mid = root->start + (root->end - root->start) / 2;
        if(start == root->start && end == root->end){ mRes += root->val; return; }
        print3(root->start, root->end, root->val);
        print3(start, end, mid);
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
    vector<int> arr = {1,2,3,4,5};
    SegmentTree sg(arr);
    sg.buildTree();
    print(sg.getFullSum());
    sg.update(0, 10);
    // sg.buildTree();
    print(sg.getFullSum());
    print(sg.getSum(1,3));
    return 0;
}