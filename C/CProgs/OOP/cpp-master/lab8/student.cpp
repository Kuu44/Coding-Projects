/*****
 *
 * Sujit Maharjan
 *
 * lab 8
 * problem 4
 *
 * Write a program that stores the information about students (name, student id,department and address) in a structure and then transfers the information to a file in your directory. Finally, retrieve the information from yourÂ  file and print in the proper format on your output screen.
 *****/

#include <iostream>
#include <cstring>
#include <fstream>

#define SUCCESS 0
using namespace std;
class Student{
 private:
    char name[20], id[10], department[20], address[20];
 public:
  Student(){};
  Student(char n[], char i[], char d[], char a[])
  {
    strncpy(name,n,20);
    strncpy(id,i,20);
    strncpy(department,d,20);
    strncpy(address,a,20);
  }
  void display(){
    cout << "Name: " << name << endl;
    cout << "Id: " << id << endl ;
    cout << "Department: " << department << endl;
    cout << "Address: " << address << endl;
  }
};



int main()
{
  ofstream data;
  data.open("Student.dat",ios::out|ios::binary);

  char name[20], id[10], department[20], address[20];
  char ans;

  do
  {
    cout << "Enter Student information" << endl;
    cout << "Name: ";
    cin >> name;
    cout << "Id: " ;
    cin >> id;
    cout << "Department: " ;
    cin >> department;
    cout << "Address: " ;
    cin >> address;

    Student newStudent(name,id,department,address);

    data.write(reinterpret_cast<char *>(&newStudent),sizeof(newStudent));
    cout << "Do you want to continue adding student data y/n";
    cin >> ans;
  }
  while(ans == 'y');
  data.close();
 
  ifstream info;
  info.open("Student.dat",ios::in|ios::binary);
  while(!info.eof()) 
  {
    Student newStudent;
    info.read(reinterpret_cast<char *>(&newStudent),sizeof(newStudent));
    if (info)
      newStudent.display();
  }
  info.close();
  
  return SUCCESS;
}
