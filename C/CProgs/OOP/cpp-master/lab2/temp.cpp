/********
 *
 * Sujit Maharjan
 *
 * lab2
 * Write a function that passes two temperatures by reference and sets the larger of the two numbers to 100 by using return by reference.
 ********/
// header file for input and output
#include <iostream>
// header file for input output manipulation
#include <iomanip>
// adding std namespace
using namespace std;
#define SUCESS 0

/********
 * \brief weird function that set higher argument to 100
 *
 * \parmas temp1: temperature by reference
 * \parmas temp2: temperature by reference
 ********/
int &func (int &temp1,int &temp2)
  {
    if (temp1 > temp2)
      {
	return temp1;
      }
    else
      {
	return temp2;
      }
  }

int main()
{
  int temp1, temp2;
  cout << "Enter temp1 and temp2?";
  cin >> temp1 >> temp2;
  func(temp1,temp2) = 100;
  cout << "Value of temp1 and temp2 after calling the fucntion"<< endl;
  cout << "temp1 " << temp1 << " temp2 " << temp2; 
  return SUCESS;
}
