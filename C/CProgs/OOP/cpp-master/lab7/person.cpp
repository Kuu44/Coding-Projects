/**
 *
 * lab 7
 * problem 2
 *
 * Create a class Person and two derived classes Employee, and Student, inherited from class Person. Now create a class Manager which is derived from two base classes Employee and Student. Show the use of the virtual base class.
 *
 */
#include <iostream>
#include <cstring>
#define SUCCESS 0
using namespace std;

class Person
{
 private:
  string name;
 public:
  Person(){}
  Person(string n)
  {
    name = n;
  }
  string getname()
  {
    return name; 
  }
};
class Employee: virtual public Person
{
 private:
  int salary;
 public:
  Employee(string n, int s):Person(n),salary(s){};
  int getsalary()
  {
    return salary;
  }
};
class Student: virtual public Person
{
 private:
  string major;
 public:
  Student(string n, string m):Person(n),major(m){};
  string getmajor()
  {
    return major;
  }
};
class Manager:public Employee, public Student
{
 private:
 public:
  Manager(string n, string m, int s): Employee(n,s), Student(n,m), Person(n)
  {
  };
};
int main()
{
  Manager NTC("Sujit Maharjan","Electronics",50000);
  cout << "name " << NTC.getname() << endl;
  cout << "major " << NTC.getmajor() << endl;
  cout << "salary " << NTC.getsalary() << endl;
  return SUCCESS;
};
