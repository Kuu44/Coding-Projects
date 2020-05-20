/*****
 *
 * Sujit Maharjan
 *
 * lab 8
 * problem 3
 *
 * Write a program to overload stream operators to read complex number and display the complex number in a+ib format.
 *****/

#include <iostream>

#define SUCCESS 0
using namespace std;

class Complex{
 private:
  int real, img;
 public:
  Complex(int r, int i):real(r),img(i){};
  friend ostream& operator<<(ostream& a, Complex c);
  
};
ostream& operator<<(ostream& a, Complex c)
{
    a << c.real << "+i" << c.img;
}
int main()
{
  Complex w(1,3);
  cout << w;
  return SUCCESS;
}
