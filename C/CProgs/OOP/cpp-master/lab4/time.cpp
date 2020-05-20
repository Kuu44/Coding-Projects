/*********
 * 
 * Sujit Maharjan
 *
 * lab4
 * problem 1
 *
 * Write a program that has a class to represent time. The class should have constructors to initialize data members hour, minute and second to 0 and to initialize them to values passed as arguments. The class should have member function to add time objects and return the result as time object. There should be another function to display the result in 24 hour format.
 *
 */
#include <iostream>

#define SUCCESS 0

using namespace std;

class Time
{
private:
  int hours, minutes, seconds;
public:
  Time()
  {
    hours = 0;
    minutes = 0;
    seconds = 0;
  }
  Time(int h, int m, int s)
  {
    setHours(h);
    setMinutes(m);
    setSeconds(s);
  }
  // getters
  int getHour(){return hours;}
  int getMinutes(){return minutes;}
  int getSeconds(){return seconds;}
  // setters
  bool setHours(int h)
  {
    if (h < 24)
      {
	hours = h;
	return true;
      }
    else
      {
	cerr << "there can only be 24 hours in a day";
	return false;
      }
  }
  bool setMinutes(int m)
  {
    if (m < 60)
      {
	minutes = m;
        return true;
      }
    else
      {
	cerr << "there can only be 60 minutes in 1 hour";
	return false;
      }
  }
  bool setSeconds(int s)
  {
    if (s < 60)
      {
	seconds = s;
        return true;
      }
    else
      {
	cerr << "there can only be 60 seconds in 1 minute";
	return false;
      }
  }
  
  Time &add(Time a)
  {
    seconds += a.getSeconds();
    minutes += a.getMinutes();
    hours += a.getHour();
    if (seconds >= 60)
      {
	minutes += seconds/60;
	seconds %= 60;
      }
    if(minutes >= 60)
      {
	hours += minutes/60;
	minutes %= 60;
      }
    if (hours >= 24)
      hours %= 24;
   
    return *this;
  }
  void displayTime()
  {
    cout << hours << ":" << minutes << ":" << seconds;
  }
};
int main()
{
  int hour, min, sec;
  char temp;
  cout << "Enter the time format hour:min:sec?";
  cin >> hour >>temp  >> min>> temp >> sec;
  Time t(hour,min,sec);
  cout << "Enter the time format hour:min:sec?";
  cin >> hour >>temp  >> min>> temp >> sec;
  Time t1(hour,min,sec);
  cout << "When we add above time we get ";
  t.add(t1).displayTime();
  return SUCCESS;
}
