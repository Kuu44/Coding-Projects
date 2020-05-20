#include <iostream>

#define SUCCESS 0
using namespace std;

class Distance{
private:
  int meter;
  int centimeter;
public:
  Distance(int m,int cm):meter(m),centimeter(cm){};
  Distance(float no)
  {
    meter=no;
    centimeter=(no-int(no))*100;
  }
  operator float()
  {
    return float(meter) + float(centimeter)/100.0;
  }
  Distance operator+(Distance a)
  {
    return Distance(meter+a.meter+(centimeter+a.centimeter)/100,(centimeter+a.centimeter)%100);
  }
  void display()
  {
    cout << meter << " m " << centimeter << "cm" << endl;
  }
};
int main()
{
  Distance d(10.34);
  d.display();
  cout << "Distance typecasting to float ";
  cout << d << endl;
  Distance c(10,6);
  Distance s = d+c;
  cout << "addition of two distances" << endl;
  d.display();
  c.display();
  cout << "Gives";
  s.display();
  return SUCCESS;
}
