/*********
 * 
 * Sujit Maharjan
 *
 * lab4
 * problem 6
 *
 * Create a class with a data member to hold "serial number" for each object created from the class. That is, the first object created will be numbered 1, the second 2 and so on by using the basic concept of static data members. Use static member function if it is useful in any of the member functions declared in the program. Otherwise make separate program that demonstrate the use of static member function.
 *
 */
#include <iostream>

#define SUCCESS 0

using namespace std;
class Student
{
private:
  unsigned int serial_number;
  static unsigned int total;
public:
  
  Student()
  {
    total++;
    serial_number = total;
  }
  void display()
  {
    cout << "serial number is "<< serial_number << " total is "<< total << endl;
  }
  unsigned int getTotal()
  {
    return total;
  }
};
unsigned int Student::total=0;
int main()
{
  Student no1, no2;
  no1.display();
  no2.display();
  return SUCCESS;
}
