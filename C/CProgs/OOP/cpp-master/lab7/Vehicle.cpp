/*****
 *
 * lab 7
 * problem 4
 *
 * Create a polymorphic class Vehicle and create other derived classes Bus, Car and Bike from Vehicle. With this program illustrate RTTI by the use of dynamic_cast and typeid operators.
*/
#include <iostream>
#include <cstring>
#include <typeinfo>
#define SUCCESS 0
using namespace std;
class Vehicle
{
 private:
 protected:
  string registration;
  int noOfWheels;
 public:
  Vehicle(string r, int n)
  {
    registration = r;
    noOfWheels = n;
  }
  string getRegistration()
  {
    cout << "Vehicle getRegistratin called" << endl;
    return registration;
  }
};
class Bus : public Vehicle
{
 private:
 public:
  Bus(string r):Vehicle(r,4){};
  string getRegistration()
  {
    cout << "Bus getRegistratin called" << endl;
    return registration;
  }
};
class Car : public Vehicle
{
 private:
 public:
  Car(string r):Vehicle(r,4){};
  string getRegistration()
  {
    cout << "Car getRegistratin called" << endl;
    return registration;
  }
};
class Bike : public Vehicle
{
 private:
 public:
  Bike(string r):Vehicle(r,2){};
  string getRegistration()
  {
    cout << "Bike getRegistratin called" << endl;
    return registration;
  }
};
 
int main()
{
  Vehicle *vlist[3];
  Bus *bs = new Bus("1");
  Car *c = new Car("1");
  Bike *b = new Bike("1");
  vlist[0] = dynamic_cast<Vehicle *>(bs);
  vlist[1] = dynamic_cast<Vehicle *>(c);
  vlist[2] = dynamic_cast<Vehicle *>(b);
  for(int i = 0; i < 3 ; i++)
  {
    cout << typeid(*vlist[i]).name() << endl;
    cout << vlist[i]->getRegistration() << endl;
  }
  cout << typeid(*bs).name() << endl;
  cout << typeid(*c).name() << endl;
  cout << typeid(*b).name() << endl;
  return SUCCESS;
}
