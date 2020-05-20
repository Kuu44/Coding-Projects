#include <iostream>

#define SUCCESS 0
#define METER_TO_FEET 3.280
using namespace std;

class Feet
{
private:
  int feet;
  int inches;
public:
  Feet(int f,int i):feet(f),inches(i){};
  Feet(float no)
  {
    feet=int(no);
    inches = int((no-int(no))*12);
  }
  float tofloat()
  {
    return float(feet+float(inches)/12);
  }
  void display()
  {
    cout <<feet<<"f"<< inches<<"in"<<endl;
  }

};

class Metric{
private:
  int meter;
  int centimeter;
public:
  Metric(int m,int cm):meter(m),centimeter(cm){};
  Metric(float no)
  {
    meter=int (no);
    centimeter=int((no-int(no))*100);
  }
  Metric(Feet f)
  {
    Metric(f.tofloat()*0.3048);
  }
  void display()
  {
    cout <<meter<<"m"<< centimeter<<"cm"<<endl;
  }
  float tofloat()
  {
    return float(meter+float(centimeter)/100.0);
  }
  operator Feet()
  {
    return Feet(tofloat()/0.3048);
  }
};



int main()
{
  cout << "Distance in Metric" << endl;
  Metric d(10.34);
  d.display();
  cout << "Converting into Feet" << endl;
  Feet(d).display();
  cout << "Distance in Feet" << endl;
  Feet f(20.34);
  f.display();
  cout << "Converting into Metric" << endl;
  Metric(f).display();
  return 0;
}
