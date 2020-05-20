/********
 *
 * Sujit Maharjan
 * lab 5
 * 
 * problem 3 
 *
 * 3.Compare the two object that contains integer values that demonstrate the overloading of equality (==), less than (<), greater than (>), not equal (!=),greater than or equal to (>=) and less than or equal to(<=) operators. 
 */
#include <iostream>

#define SUCCESS 0
using namespace std;
class Integer
{
 private:
  int no;
 public:
  Integer(int a):no(a){};
  bool operator==(Integer a)
  {
    if(a.no == no)
      return true;
    else
      return false;
  }
  bool operator<(Integer a)
  {
  if(no < a.no)
      return true;
    else
      return false;
  }      
bool operator>(Integer a)
  {
  if(no > a.no)
      return true;
    else
      return false;
  }
bool operator<=(Integer a)
  {
  if(no <= a.no)
      return true;
    else
      return false;
  }
bool operator>=(Integer a)
  {
  if(no >= a.no)
      return true;
    else
      return false;
  }            
};
int main()
{
  int temp;
  cout << "Enter integer for object a";
  cin >> temp;
  Integer a(temp);
  cout << "Enter integer for object b";
  cin >> temp;
  Integer b(temp);
  if (a == b)
    cout << "object a and b are equal"<< endl;
  if (a < b)
    cout << "object a is less than b"<< endl;
  if (a > b)
    cout << "object a is greater than b"<< endl;
  if (a <= b)
    cout << "object a is less than or equal to b"<< endl;
  if (a >= b)
    cout << "object a is gerater than or equal to b"<< endl;

  return SUCCESS;
}
