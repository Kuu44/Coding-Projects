/*********
 *
 * Sujit Maharjan
 * lab 6
 *
 * problem 5
 * Write base class that ask the user to enter a complex number and make a derived class that adds the complex number of its own with the base. Finally make third class that is friend of derived and calculate the difference of base complex number and its own complex number.
 **********/
#include <iostream>
#define SUCCESS 0

using namespace std;

class Complex
{
 public:
  int real, img;
  Complex()
  {
    cout << "Enter real part";
    cin >> real;
    cout << "Enter imaginary part";
    cin >> img;
  }
  void display ()
  {
    cout << real << "+i" << img;
  }
};

class ComplexMath:public Complex
{
 private:
 public:
  ComplexMath(){
  }

  ComplexMath& operator+(const Complex a)
  {
    real += a.real;
    img += a.img;
    return *this;
  }
};

int main()
{
  Complex a;
  ComplexMath c;
  a.display();
  std::cout << "+";
  c.display();
  cout << "=";
  (c+a).display();
  return SUCCESS;
}
