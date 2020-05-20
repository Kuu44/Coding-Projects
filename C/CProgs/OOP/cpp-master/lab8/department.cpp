/*****
 *
 * Sujit Maharjan
 *
 * lab 8
 * problem 1
 *
 * Write a program to demonstrate the use of different ios flags and functions to format the output. Create a program to generate the bill invoice of a department store by using different formatting.
 *****/

#include <iostream>
#include <fstream>
#include <iomanip>

#define SUCCESS 0
using namespace std;

int main()
{
  ofstream bill("bill.txt",ios::out);
  bill << setw(40) << "SUJIT COMPANY LIMITED" << endl;
  cout << setw(40) << "SUJIT COMPANY LIMITED" << endl;
  int sno = 1;
  char part[20];
  int qt;
  float price;
  float subtotal;
  float total = 0;
  char ans;
  bill << setw(4) << "Sno " << setw(20) << left << "Particulars "<< setw(10) << "Quantity " << setw(6) << "Price "<< setw(10) <<"Sub total " << endl;
  do{
    cout << "Particulars:" ;
    cin >> part;
    cout << "Quantity:";
    cin >> qt;
    cout << "Price:";
    cin >> price;
    cout << "Sub Total:";
    subtotal = qt * price;
    cout << subtotal << endl;
    total += subtotal;
    bill << setw(4) << sno++ << setw(20) << left << part << setw(10)  << qt << setw(6) << price << setw(10) << subtotal << endl;
    cout << "Do you want to continue (y/n)";
    cin >> ans;
  }
  while(ans == 'y');
  cout << "total " << total;
  bill << setw(34) << "total" << setw(10) << total << endl;
  bill.close();
  return SUCCESS;
}
