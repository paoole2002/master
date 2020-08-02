#define NOMINMAX

#include "iostream"
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdio>
#define print(x)  std::cout<<x<<std::endl;
using namespace std;

long long myPow(int x, int p)
{
  if (p == 0) return 1;
  if (p == 1) return x;

  long tmp = myPow(x, p/2);
  if (p%2 == 0) return tmp * tmp;
  else return x * tmp * tmp;
}

long long karatsuba(std::string x, std::string y){
  if(x.size() <= 1 && y.size() <= 1){
    return stoi(x) * stoi(y);
  }
  long long ac, bd, z = 0;
  int max_len = max((int)x.size(), (int)y.size());
  int nby2 = max_len / 2;
  long long a = stoi(x);
  long long b = stoi(y);
  long long a1 = a / myPow(10, nby2);
  long long a2 = a % myPow(10, nby2);
  long long b1 = b / myPow(10, nby2);
  long long b2 = b % myPow(10, nby2);
  ac = karatsuba(to_string(a1), to_string(b1));
  bd = karatsuba(to_string(a2), to_string(b2));
  long long temp1 = a1 + a2;
  long long temp2 = b1 + b2;
  z = karatsuba(to_string(temp1), to_string(temp2));
  z -= (ac + bd);
  long long res = myPow(10, 2*nby2) * ac + myPow(10, nby2) * z + bd;
  return res;
}

int main(){
  long long first = 12345678;
  long long second = 87654321;
  std::string num1 = to_string(first);
  std::string num2 = to_string(second);
  long long prod = karatsuba(num1, num2);
  print(prod);
  print(first * second)
  return 0;
}