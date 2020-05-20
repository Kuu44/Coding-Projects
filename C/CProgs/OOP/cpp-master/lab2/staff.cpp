/********
 *
 * Sujit Maharjan
 *
 * lab2
 * Write a program that displays the current monthly salary of chief executive officer, information officer, and system analyst, programmer that has been increased by 9, 10, 12, and 12 percentages respectively in year 2010. Let us assume that the salaries in year 2009 are
 *
 * Chief executive officer Rs. 35000/m
 * Information officer Rs. 25000/m
 * System analyst Rs. 24000/m
 * Programmer Rs. 18000/m
 * Make function that takes two arguments; one salary and other increment. Use proper default argument.
 ********/
// header file for input and output
#include <iostream>
// header file for input output manipulation
#include <iomanip>
// adding std namespace
using namespace std;
#define SUCESS 0

struct employee
{
  char position[40];
  int salary;
  int rate;
};
inline int newSalary (int salary, int percentage = 12) {return salary * ( 1 + percentage/100.0);}
int main()
{
  // data for year 2009
  struct employee employee[] = {
    {"chief executive officer",35000,9},
    {"information officer",25000,10},
    {"system analyst",24000,12},
    {"programmer",18000,12}
  };
  cout << "For year 2009" << endl;
  for (int i = 0 ; i < sizeof(employee)/sizeof(struct employee); i++)
    {
      cout << employee[i].position << " Rs. " << employee[i].salary << "/m" <<endl;
    }
  cout << "For year 2010" << endl;
  for (int i = 0 ; i < sizeof(employee)/sizeof(struct employee); i++)
    {
      cout << employee[i].position << " Rs. " << newSalary(employee[i].salary,employee[i].rate) << "/m" <<endl;
    }
  return SUCESS;
}
