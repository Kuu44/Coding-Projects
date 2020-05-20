/********
 *
 * Sujit Maharjan
 * lab 5
 * 
 * problem 4
 *4.      Write a class Date that uses pre increment and post increment operators to add 1 to the day in the Date object, while causing appropriate increments to the month and year (use the appropriate condition for leap year). The pre and post increment operators in your Date class should behave exactly as the built in increment operators.
 */
#include <iostream>

#define SUCCESS 0
int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
using namespace std;
class Date
{
private:
  int year;
  int month;
  int day;
public:
  Date(int y, int m, int d)
  {
    setDate(y, m, d);
  }
  static bool isLeapYear(int y)
  {
    if(y % 4 == 0)
      return true;
    else
      return false;
  }
  bool setDate(int y, int m, int d )
  {
    year = y;
    if (m <= 12 && m > 0)
      {
	month = m;
      }
    else
      {
	cerr << "invalid month";
	return false;
      }
    if (d > 0 && d <= days[m-1])
      {
	day = d;
      }
    else if (m == 2 && d <= 30)
      {
	day = d;
      }
    else
      {
	cerr << "invalid days in month";
	return false;
      }
    return true;
  }
  Date operator++()// pre
  {
    day += 1;
    if (month == 2 && isLeapYear(year) == true)
      {
	if (day > 29)
	  {
	    month += day / 29;
	    day = day % 29;
	  }
      }
    else
      {
	if (day > days[month-1])
	  {
	    int temp = month;
	    month += day / days[temp-1];
	    day = day % days[temp-1];
	   }
      }
    if (month > 12)
      {
	year += month/12;
	month = month%12;
	
      }
    return *this;
  }
  Date operator++(int)// post
  {
    Date temp = *this;
    ++(*this);
    return temp;
  }
  void display()
  {
    cout << year << "-" << month << "-" << day;
  }
};
int main()
{
  int y, m, d;
  char temp;
  cout << "Enter date yyyy-mm-dd";
  cin >> y >> temp >> m >> temp >> d;
  Date date(y,m,d);
  cout << "Post increment of date return value";
  (date++).display();
  cout << endl;
  cout << "Post increment after execution";
  date.display();
  cout << endl;
  cout << "Pre of date return value";
  (++date).display();
  cout << endl;
  cout << "Pre increment after execution";
  date.display();
  return SUCCESS;
}
