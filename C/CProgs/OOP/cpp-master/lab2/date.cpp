/********
 *
 * Sujit Maharjan
 *
 * lab2
 * problem 1
 * Write a program to set a structure to hold a date (mm,dd and yy), assign values to the members of the structure and print out the values in the format 11/28/2004 by function. Pass the structure to the function
 ********/
// header file for input output in c++
#include <iostream>
// header file for input output manipulation
#include <iomanip>
#define SUCESS 0
#define true 0
#define false 1
// adding std namspace
using namespace std;

// date data structre
struct date {
  int year;
  int month;
  int day;
};

// function that displays date
void display(struct date d)
{
  cout << setw(2) << d.day << '/'<< setw(2) << d.month << '/' << setw(4) << d.year<< endl;
}

// function that gets date
void getdate(struct date *d)
{
  int sucess;
  do
    {
      sucess = true;
      cout << "day/month/year:";
      cin >> d->day >> d->month >> d->year;
      // date input validation
      if ( d->month < 1 || d->month > 12) // month should be between 1 to 12 
	{
	  cout << "month should be between 1 to 12" << endl;
	  sucess = false;
	}
      else if ( d->day < 1 || d->day > 33 ) // date of the month should be between 1 to 32
	{
	  cout << "date must be between 1 to 32" << endl;
	  sucess = false;
	} 
    }
  while(sucess != true); 
}

int main()
{
  // declaring an instance of struct date
  struct date d;
  
  // getting input from the user
  getdate(&d);

  // displaying input from the user
  display(d);

  // returning SUCESS
  return SUCESS;
}
