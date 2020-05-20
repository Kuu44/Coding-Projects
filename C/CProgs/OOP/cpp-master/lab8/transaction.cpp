/*****
 *
 * Sujit Maharjan
 *
 * lab 8
 * problem 5
 *
 * Write a program for transaction processing that write and read object randomly to and from a random access file so that user can add, update, delete and display the account information (accountnumber, lastname, firstname, totalbalance).
 *****/

#include <iostream>
#include <fstream>
#include <cstring>
#define SUCCESS 0
using namespace std;

class Transaction{
 private:
  char firstName[20], lastName[20];
  int accountNumber, totalBalance;
 public:
  Transaction(){};
  Transaction(char fn[], char ln[], int an, int tb):accountNumber(an),totalBalance(tb){
    strncpy(firstName,fn,20);
    strncpy(lastName,ln,20);
  }
  friend istream& operator>>(istream& in, Transaction &tr);
  friend ostream& operator<<(ostream& out, Transaction tr); 
  
};
istream& operator>>(istream& in, Transaction &tr)
{
  cout << "------------------------------------------" << endl;
  cout << "First Name: ";
  in >> tr.firstName;
  cout << "Last Name: ";
  in >> tr.lastName;
  cout << "Account Number: ";
  in >> tr.accountNumber;
  cout << "Total Balance: ";
  in >> tr.totalBalance;
  cout << "------------------------------------------" << endl;
  return in;
}

ostream &operator<<(ostream &out, Transaction tr)
{
  cout << "------------------------------------------" << endl;
  out << "First Name: " << tr.firstName << endl;
  out << "Last Name: " << tr.lastName << endl;
  out << "Account Number: " << tr.accountNumber << endl;
  out << "Total Balance: " << tr.totalBalance << endl;
  cout << "------------------------------------------" << endl;
  return out;
}
int main()
{
  int ans;
  do
  {
    cout << "Menu" << endl;
    cout << "1.create record" << endl;
    cout << "2.add record" << endl;
    cout << "3.delete record" << endl;
    cout << "4.edit record" << endl;
    cout << "5.display record" << endl;
    cout << "Enter your choice"; 

    cin >> ans;
    fstream acc;
    if(ans== 1)
    {
      char ans;
      acc.open("account.dat",ios::out|ios::binary);
    do
    {
      Transaction tr;
      cin >> tr;
      acc.write(reinterpret_cast<char *>(&tr),sizeof(tr));
      if (!acc)
      {
        cerr << "Couldnot write the data to the file";
        return 1;
      }
      cout << "Do you want to continue y/n ";
      cin >> ans;
    }
    while(ans=='y');
    acc.close();
  }
  else if(ans == 2)
  {
    char ans;
    acc.open("account.dat",ios::out|ios::app|ios::binary);
    do
    {
      Transaction tr;
      cin >> tr;
      acc.write(reinterpret_cast<char *>(&tr),sizeof(tr));
      if (!acc)
      {
        cerr << "Couldnot modify the data of the file";
        return 2;
      }
      cout << "Do you want to continue y/n ";
      cin >> ans;
    }
    while(ans=='y');
    acc.close();
  }
  else if(ans == 3)
  {
    char ns;
    Transaction tr;
    acc.open("account.dat",ios::in|ios::binary);
    fstream newacc;
    newacc.open("tmp.dat",ios::out|ios::binary);
    if(!newacc)
    {
      cerr << "couldnot create tmp record file";
    }
    while(!acc.eof())
    {
      acc.read(reinterpret_cast<char *>(&tr),sizeof(tr));
      if (acc)
      {
        cout << tr;
        cout << "Do you want to delete this record y/n ";
        cin >> ns;
        if (ns != 'y')
        {
          newacc.write(reinterpret_cast<char *>(&tr),sizeof(tr));
          if(!newacc)
          {
            cerr << "unable to write to a temp file";
            return 3;
          }
        }
        else
        {
          cout << "record deleted" << endl;
        }
      }
    }
    
    acc.close();
    newacc.close();
    remove("account.dat");
    rename("tmp.dat","account.dat");
  }
  else if(ans == 4)
  {
    char ans;
    acc.open("account.dat",ios::in|ios::binary|ios::out);
    while(!acc.eof())
    {
      Transaction tr;
      int pos = acc.tellg();
      acc.read(reinterpret_cast<char *>(&tr),sizeof(tr));
      if (acc)
      {
        cout << tr;
        cout << "Do you want to edit this record y/n";
        cin >> ans;
        if (ans == 'y')
        {
          cin >> tr;
          acc.seekp(pos);
          acc.write(reinterpret_cast<char *>(&tr),sizeof(tr));
          if(acc)
          {
            cout << "Record sucessfully edited"<< endl;
          }
          else
          {
            cerr<< "Unable to modify the record";
            return 4;
          }
        }
      }
    }
    
    acc.close();
  }
  else if (ans == 5)
  {
    acc.open("account.dat",ios::in|ios::binary);
    while(!acc.eof())
    {
      Transaction tr;
      acc.read(reinterpret_cast<char *>(&tr),sizeof(tr));
      if(acc)
      {
        cout << tr;
      }
      else
      {
        cerr << "Couldnot read through the file" << endl;
      }
    }   
    acc.close();
  }
  }  
  while(ans <= 5 && ans > 0 );
  return SUCCESS;
}
