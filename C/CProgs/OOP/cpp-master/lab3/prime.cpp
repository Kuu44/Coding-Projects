/******
 *
 * lab3
 * problem 2
 *
 * Assume that you want to check whether the number is prime or not. Write a program that asks for a number repeatedly. When it finishes the calculation the program asks if the user wants to do another calculation. The response can be 'y' or 'n'. Don't forget to use the object class concept. 
 *
 */
// header file for input and output operation
#include <iostream>
// using standard namespace
using namespace std;
#define SUCESS 0
/*
 * class Number
 */
class Number{
private: 
  int num;
public:
  Number(int n){num = n;}
  bool isPrime()
  {
    if (num < 2) // prime no is defined for natural no greater than 2
      return false;
    else
      for (int i = 2; i <= num/2; i++) // brute force all the factor possible 
	{
	  if (num % i == 0) // i is found to be the factor
	    return false;
	}
    return true;
  }
};
int main()
{     
  int temp;
  char choice;
  do 
    {
      cout << "Enter no to Check?";
      cin >> temp;
      Number no(temp);
      if (no.isPrime() )
	cout << "Number is prime" << endl;
      else
	cout << "Number is not prime" << endl;
      cout << "Do you want to continue y/n";
      cin >> choice;
    }
  while(choice == 'y');
  return SUCESS;
}
