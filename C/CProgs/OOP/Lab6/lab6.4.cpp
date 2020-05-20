#include <iostream>
#include <cstring>
#define SUCCESS 0
using namespace std;
class Person
{
 private:
  string name;
  int age;
 public:
  void setName(string n)
  {
    name = n;
  }
  void setAge(int a)
  {
    age = a;
  }
  string getName()
  {
    return name;
  }
};
class Student: public Person
{
 private:
  int rank;
  int cls;
 public:
 int getRank()
  {
    return rank;
  }
  int getClass()
  {
    return cls;
  }
  void setRank(int r)
  {
    rank = r;
  }
  void setClass(int c)
  {
    cls = c;
  }
};
class Employee: public Person
{
 private:
  string dep;
  int salary;
 public:
  void setDep(string d)
  {
    dep = d;
  }
  void setSalary(int s)
  {
    salary = s;
  }
  string getDep()
  {
    return dep;
  }
  int getSalary()
  {
    return salary;
  }
};
int main()
{
  Person p1, p2;
  Employee e1, e2;
  Student s1, s2;
  std::cout << &p1 << &p2 << std::endl;
  cout << sizeof(p1) << endl;
  cout << &p2 - &p1 << endl;
  std::cout << &e1 << &e2 << std::endl;
  cout<< sizeof(e1) << endl;
  cout << &e2 - &e1 << endl;
  std::cout << &s1 << &s2 << std::endl;
  cout<< sizeof(s1) << endl;
  cout << &s2 - &s1 << endl;
  return SUCCESS;
}
