#include "iostream"
#include <string.h>
#define print(x)  std::cout<<x<<std::endl;
#define print2(x,y) std::cout<<x<<" , "<<y<<std::endl;
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int value){
        this->val = value;
        this->left = nullptr;
        this->right = nullptr;
    };
};

class BST{

public:
    void insert(int key){
        root = insertVal(root, key);
    }
    void printInorder() {
        TreeNode* cur = root;
        printIn(cur);
    }

    bool contains(int key){
        return containsVal(root, key);
    }

    int getMax(){
        return getMaxVal(root);
    }

    void leftRotate(int key){
        TreeNode* cur = root;
        root = lRotation(key, root, NULL, false);
    }

    void rightRotate(int key){
        TreeNode* cur = root;
        root = rRotation(key, root, NULL, false);
    }

    void erase(int key){
        deleteVal(root, key);
    }

private:
    TreeNode* root = nullptr;

    void printIn(TreeNode* tree){
        if(tree){
            print(tree->val);
            printIn(tree->left);
            printIn(tree->right);
        }
    }

   

    TreeNode* insertVal(TreeNode* root, int key) {
        if(!root){
            root = new TreeNode(key);
        }
        else if(root->val > key){
            root->left = insertVal(root->left, key);
        }
        else{
            root->right = insertVal(root->right, key);
        }
        return root;
    }

    bool containsVal(TreeNode* root, int key){
        if(!root){return false;}
        if(root->val == key){return true;}
        else if(root->val > key){return containsVal(root->left, key);}
        else{return containsVal(root->right, key);}
    }

    int getMaxVal(TreeNode* root){
        if(root && !root->right){
            return root->val;
        }
        return getMaxVal(root->right);
    }

    TreeNode* findSuccessor(TreeNode* root){
        if(!root->right){return root;}
        root = root->right;
        while(root->left){
            root = root->left;
        }
        return root;
    }

    TreeNode* deleteVal(TreeNode* root, int key){
        if(!root){return root;}
        if(root->val > key){
            root->left = deleteVal(root->left, key);
        }
        else if(root->val < key){
            root->right = deleteVal(root->right, key);
        }
        else{
            if(!root->left && !root->right){return NULL;}
            else if(root->left && !root->right){
                root = root->left;
            }
            else if(root->right && !root->left){
                root = root->right;
            }
            else{
                TreeNode* successor = findSuccessor(root);
                root->val = successor->val;
                root->right = deleteVal(root->right, successor->val);
            }
        }
        return root;
    }

    TreeNode* lRotation(int key, TreeNode* root, TreeNode* parent, bool isLC){
        if(!root){return root;}
        if(root->val > key){root->left = lRotation(key, root->left, root, true);}
        else if(root->val < key){root->right = lRotation(key,root->right, root, false);}
        else{
            if(!parent){ // rotate root
                TreeNode* newRoot = root->right;
                TreeNode* temp = newRoot->left;
                newRoot->left = root;
                newRoot->left->right = temp;
                return newRoot;
            }
            else{ // parent exist
                if(isLC){ // rotate the left child of parent
                    TreeNode* newRoot = root->right;
                    TreeNode* temp = parent->left;
                    parent->left = newRoot;
                    newRoot->left = root;
                    root->right = NULL;
                    if(newRoot->left->right){
                        newRoot->left->right = temp->left;
                    }
                    return newRoot;
                }
                else{ // rotate the right child of parent
                    TreeNode* newRoot = root->right;
                    TreeNode* temp = parent->right;
                    parent->right = newRoot;
                    newRoot->left = root;
                    root->right = NULL;
                    if(newRoot->left->right){
                        newRoot->left->right = temp->left;
                    }
                    return newRoot;
                }
            }
        }
        return root;
    }

    TreeNode* rRotation(int key, TreeNode* root, TreeNode* parent, bool isLC){
        if(!root){return root;}
        if(root->val > key){root->left = rRotation(key, root->left, root, true);}
        else if(root->val < key){root->right = rRotation(key, root->right, root, false);}
        else{
            if(!parent){ // so it is just taking the left rotation and chaning right to left
                TreeNode* newRoot = root->left;
                TreeNode* temp = newRoot->right;
                newRoot->right = root;
                newRoot->right->left = temp;
                return newRoot;
            } // if parent exists then process is similar to left rotation.
        }
    }
    
};
int main()
{
    BST tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);
    tree.rightRotate(50);
    tree.printInorder();
    return 0;
}