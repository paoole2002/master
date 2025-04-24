#include <iostream>

enum class MyEnum {
  A,
  B,
  C,
  Unknown,
};

int main () {
  MyEnum en = MyEnum::Unknown;
  switch (en) {
    case MyEnum::A:
    {
      std::cout << "A" << std::endl; break;
    }
    case MyEnum::B:
    {
      std::cout << "B" << std::endl; break;
    }
    case MyEnum::C:
    {
      std::cout << "C" << std::endl; break;
    }
    default:
      std::cout << "Value not found" << std::endl;
  }
  return 0;
}