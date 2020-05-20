#include <iostream>


using namespace std;

class Complex
{
 public:
  int real, img;
  Complex()
  {
    cout << "Enter real and imaginary parts:";
    cin >> real>> img;
  }
  void display ()
  {
    cout <<"("<<real<<"+"<<img<<"i"<<")";
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
  return 0;
}
