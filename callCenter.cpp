#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

enum Type {Responder = 0, Manager, Director};

class Employee {
public:
  Employee() = default;
  Employee(const string& s, const Type t) : mName(s), mType(t) {}

  virtual bool canHandleCall() const = 0;
protected:
  string mName;
  Type mType;
  bool mAvailable = true;
};

class Responder : public Employee {
public:
  Responder() = default;
  Responder(const string& name) : Employee(name, Type::Responder) {}

  bool canHandleCall() const override {
    // returns whether 
    return true;
  }
};

class Manager : public Employee {
public:
  Manager(const string& name) : Employee(name, Type::Manager) {}

  bool canHandleCall() const override {
    // returns whether 
    return true;
  }
};

class Director : public Employee {
public:
  Director() = default;
  Director(const string& name) : Employee(name, Type::Director) {}

  bool canHandleCall() const override {
    // returns whether 
    return true;
  }
};


class CallCenter{
public:
  CallCenter(int resps, int mangs, int dirs) {

  }
private:
  unordered_map<int, Employee> d;
  vector<Employee> mEmpls;
};

int main(){
  return 0;
}