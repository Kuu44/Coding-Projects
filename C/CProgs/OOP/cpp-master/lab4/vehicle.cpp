/*********
 * 
 * Sujit Maharjan
 *
 * lab4
 * problem 4
 *
 * Assume that one constructor initializes data member say num_vehicle, hour and rate. There should be 10% discount if num_vehicle exceeds 10. Display the total charge. Use two objects and show bit-by-bit copy of one object to another (make your own copy constructor).
 *
 */
#include <iostream>

#define SUCCESS 0

using namespace std;

class Lease
{
private:
  int num_vehicles;
  float hour, charge;
public:
  Lease(int n, float h, float c):num_vehicles(n),hour(h),charge(c){};
  Lease(Lease &a)
  {
    num_vehicles=a.getNumVehicles();
    hour=a.getHour();
    charge=a.getCharge();
  }
  int getNumVehicles()
  {
    return num_vehicles;
  }
  float getHour()
  {
    return hour;
  }
  float getCharge()
  {    
    return charge;
  }
  float getTotal()
  {
    float total = num_vehicles*hour*charge;
    if (num_vehicles > 10)
      {
	total *= 0.9;
      }
    return total;
  }
  void display()
  {
    cout << "No of vehicle " << num_vehicles << endl;
    cout << "No of hours " << hour << endl;
    cout << "Charge " << charge << endl;
    cout << "Total " << getTotal() << endl;
  }
};
  

int main()
{
  Lease a(4,5,5),b(12,5,5);
  cout << "Object constructed via constructor" << endl;
  a.display();
  b.display();
  Lease c= a, d=b;
  cout << "Object constuced via copy constructor" << endl;
  c.display();
  d.display();
  return SUCCESS;
}
