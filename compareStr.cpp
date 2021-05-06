#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <limits>
#include <array>
#define print(x)  std::cout<<x<<std::endl;
using namespace std;

int main(int argc, char* argv[]){
  string s1, s2;
  s1 = argv[1];
  s2 = argv[2];
  array<int,26> arr1 {0};
  array<int,26> arr2 {0};
  if(std::abs((int)s1.size() - (int)s2.size()) > 1){ cout<< "IMPOSSIBLE\n"; return 0; }
  for(const auto& ch : s1){
    arr1.at(ch - 97)++;
  }
  for(const auto& ch : s2){
    arr2.at(ch - 97)++;
  }
  char c1 = '-', c2 = '-';
  if(s1.size() != s2.size()) {
    for(unsigned int i = 0; i < 26; i++){
      if(s1.size() != s2.size() && arr1.at(i) > arr2.at(i)){
        cout<<"REMOVE " << (char)(i + 97) <<endl;
      }
      else if (s1.size() != s2.size() && arr1.at(i) < arr2.at(i)) {
        cout<<"INSERT " << (char)(i + 97) <<endl;
      }
    }
  }
  else {
    for(unsigned int j = 0; j < s1.size(); j++) {
      if(s1[j] != s2[j]) {
        int idx = s1[j] - 97;
        if(arr1.at(idx) == arr2.at(idx)){
          cout << "SWAP " << s1[j] << " " <<s2[j] << '\n';
          return 0;
        }
        else {
          cout << "IMPOSSIBLE\n";
          return 0;
        }
      }
    }
  }
  cout<<"EQUAL\n";
  return 0;
}