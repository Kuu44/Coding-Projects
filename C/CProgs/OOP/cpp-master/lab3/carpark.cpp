/********
 *
 * lab3
 * problem 3
 *
 * Create a class called carpart that has int data member for car id, int data member for charge/hour and float data member for time. Set the data and show the charges and parked hours of corresponding car id. Make two member functions for setting and showing the data. Member function should be called from other functions.
 *
 */
// header file for input and output operation
#include <iostream>
// using standard namespace
using namespace std;
#define SUCCESS 0

/**
 * carpark class 
 */
class Carpark 
{
private:
  int id;
  int charge;
  float time;
public:
  /*Carpark(int i, float c, float t)
  {
    id = i;
    charge = c;
    time = t;
  }*/
  void setId(int i){id = i;}
  void setCharge(int c){charge = c;}
  void setTime(float t){time = t;}
  int getId(){return id;}
  int getCharge(){return charge;}
  float getTime(){return time;}
  float getTotalCharge(){return time *charge;}
  void displayInfo()
  {
    cout << "Id of carpark is " << getId() << endl;
    cout << "Charge/hour "<< getCharge() << endl;
    cout << "Time parked "<< getTime() << endl;
    cout << "Total charge "<< getTotalCharge() << endl;
  } 
};

int main()
{
  Carpark park; 
  int id, charge, time;
  cout << "Enter car id";
  cin >> id;
  cout << "Enter charge per hour";
  cin >> charge;
  cout << "Enter time parked";
  cin >> time;
  
  park.setId(id);
  park.setCharge(charge);
  park.setTime(time);
  
  park.displayInfo();
  return SUCCESS;
}

