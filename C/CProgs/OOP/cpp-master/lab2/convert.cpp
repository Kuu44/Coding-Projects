/********
 *
 * Sujit Maharjan
 *
 * lab2
 * Write a program using the function overloading that converts feet to inches. Use function with no argument, one argument and two arguments. Decide yourself the types of arguments. Use pass by reference in any one of the function above.*
 ********/
// header file for input and output
#include <iostream>
// header file for input output manipulation
#include <iomanip>
// adding std namespace
using namespace std;
#define SUCESS 0
#define CONVERSION_FACTOR 12

/**
 *
 * \brief coverts feet to inches
 *
 * \params feet
 * \params inches
 */
void convert() // when no argument is supplied
{
  cout << "Feet?";
  int feet;
  cin >> feet;
  float inch;
  inch = feet * CONVERSION_FACTOR;
  cout << "In inch" << inch;
}
float convert(int feet) // one arugument
{
  return feet * CONVERSION_FACTOR;
}
void convert(int feet, float &inch) // two argument
{
  inch = feet * CONVERSION_FACTOR;
}

int main()
{
  
  convert();
  int feet = 12;
  float inch;
  cout << "Converting 12 feet to inch" << endl;
  cout << "12 feet in inch :" << convert(feet) << endl;
  feet = 10;
  convert(feet,inch);
  cout << "Converting " << feet << "to inch" << endl;
  cout << feet << " in inch:" << inch << endl;
  return SUCESS;
}
