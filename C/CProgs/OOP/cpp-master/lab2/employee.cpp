/********
 *
 * Sujit Maharjan
 *
 * lab2
 * Assume that employee will have to pay 10 percent income tax to the government. Ask user to enter the employee salary. Use inline function to display the net payment to the employee by the company.
 ********/
// header file for input and output
#include <iostream>
// header file for input output manipulation
#include <iomanip>
// adding std namespace
using namespace std;
#define SUCESS 0
#define TAX_RATE (10.0/100.0)

/********
 * \brief calculates the income tax 
 *
 ********/
// returns tax on the salary
inline float tax (int i) {return (i * TAX_RATE);} 

int main()
{
  int income;
  cout << "Enter employee salary?";
  cin >> income;
  cout << "Income tax to be paid by the employee :" << tax(income) << endl; 
  return SUCESS;
}
