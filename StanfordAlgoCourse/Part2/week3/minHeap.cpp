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

class MinHeap {
public:
  vector<int> heap;

    MinHeap(vector<int>& vector)
    {
        buildHeap(vector);
    };

    void buildHeap(vector<int>& vector) {
        for(auto i = 0; i < vector.size(); i++){
			insert(vector.at(i));
		}
        for(auto i = 0; i < vector.size(); i++){
			remove();
		}
    }
	void swap(int i, int j){
		int temp = heap.at(i);
		heap.at(i) = heap.at(j);
		heap.at(j) = temp;
	}
    void siftDown(int idx, int endIdx) {
        while(idx < heap.size()){
            int left = std::numeric_limits<int>::max();
            bool hasChild = false;
            int right = numeric_limits<int>::max();
            int minChild = numeric_limits<int>::max(); int newIdx = -1;
            if(2*idx + 1 < heap.size()){
                left = heap.at(2*idx+1); hasChild = true;
            }
            if(2*idx + 2< heap.size()){
                right = heap.at(2*idx+2);
            }
            if(!hasChild){return;}
            if(left < right){
                minChild = left; newIdx = 2*idx + 1;
            }
            else{
                minChild = right; newIdx = 2*idx + 2;
            }
            if(heap.at(idx) > minChild){
                swap(idx, newIdx);
                idx = newIdx;
            }
            else{
                return;
            }
        }
    }

    void siftUp(int idx) {
        int parent;
        if(idx % 2 == 0){parent = idx/2 -1;}
        else{parent = idx/2;}
        while(parent >= 0 && heap.at(idx) < heap.at(parent)){
            swap(parent, idx);
            idx = parent;
            if(idx % 2 == 0){parent = idx/2 -1;}
            else{parent = idx/2;}
        }
    }

    int peek() {
        return heap.at(0);
    }

    int remove() {
        int res = heap.at(0);
        swap(0, heap.size()-1);
        heap.pop_back();
        siftDown(0, heap.size()-1);
        return res;
    }

    void insert(int value) {
		heap.push_back(value);
		if(heap.size() == 1){return;}
		siftUp(heap.size()-1);
  }
};

int main(){
    vector<int> vec;
    vec.push_back(48);
    vec.push_back(12);
    vec.push_back(24);
    vec.push_back(7);
    vec.push_back(8);
    MinHeap heap(vec);
    return 0;
}