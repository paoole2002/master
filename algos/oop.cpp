#include "iostream"
using namespace std;
#define print(x) cout << x << endl

template<typename T> class Parent{
public:
  Parent(T x, T y)
  : mX(x), mY(y)
  {}
protected:
  T mX;
  T mY;
};

class Child : public Parent<int>{
public:
  Child(int x, int y, int new_x, int new_y)
  : Parent(x, y), mNewX(new_x), mNewY(new_y)
  {}
  double getDistance()
  {
    return mNewX - mX + mNewY - mY;
  }
  void setX(int new_val){
    mNewX = new_val;
  }
  void setY(int new_val){
    mNewY = new_val;
  }
private:
  int mNewX;
  int mNewY;
};
int main()
{
  Child child(1, 1, 3, 3);
  int dist = child.getDistance();
  print(dist);
  child.setX(30);
  child.setY(2);
  print(child.getDistance());
  return 1;
}