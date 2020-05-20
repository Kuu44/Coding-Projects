/*****
 *
 * Sujit Maharjan
 *
 * lab 8
 * problem 2
 * Write a program to create a userdefined manipulator that will format the output by setting the width, precision and fill character at the same time by passing arguments
 *
 *****/

#include <iostream>
#include <iomanip>
#define SUCCESS 0
 
using namespace std;
class Testmani{
 private:
  int width, precision;
  char fill;
 public:
  Testmani(int w, int p , char f):width(w),precision(p),fill(f){};
  friend ostream& operator<<(ostream &str, Testmani obj);
};
ostream& operator<<(ostream &str, Testmani obj)
{
  str << setw(obj.width)<< setfill(obj.fill) << setprecision(obj.precision);
  return str;
}
Testmani setwpf(int w, int p, char f)
{
  return Testmani(w,p,f);
}
int main()
{
  cout << setwpf(5,3,'$') << 5.630009; 
  return SUCCESS;
}
