/********
 *
 * Sujit Maharjan
 * lab3
 *
 * problem 5
 * Assume that an object represents an employee report that contains the information like employee id, total bonus, total overtime in a particular year. Use  array of objects to represent n employees' reports. Write a program that displays report. Use setpara() member function to set report attributes by passing the arguments and member function displayreport() to show the reports according to parameter passed. Display the report in following format. 
 *
 *   Employee with ... ... ... has received Rs ... ... ...as bonus and
    had worked ... ... ... hours as a over time in  year ... ... ... 
 *
 */
#include <iostream>

using namespace std;

#define SUCCESS 0

class employee
{

private:

  int id;
  int bonus;
  int overtime;
  int year;

public:

  void setpara(int i, int b, int o, int y)
  {
    id =i;
    bonus = b;
    overtime = o;
    year = y;
  }
  void displayreport()
  {
    cout << "Employee with id " << id << " has received Rs. " << bonus << " as bonus and had worked " << overtime << " hours as a over time in year " << year << endl; 
  }

};
int main()
{
  int n;
  cout << "Enter the no of employee?";
  cin >> n;
  employee e[n];
  for (int i = 0; i < n; i++)
    {
      int id, bonus, overtime, year;
      cout << "Employee id:";
      cin >> id;
      cout << "Bonus:";
      cin >> bonus;
      cout << "Overtime:";
      cin >> overtime;
      cout << "Year:";
      cin >> year;
      e[i].setpara(id,bonus,overtime,year);
    }
  
  for (int i = 0; i< n ; i++)
    {
      e[i].displayreport();
    }
  return SUCCESS;
}
