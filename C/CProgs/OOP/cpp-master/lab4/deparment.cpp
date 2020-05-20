/*********
 * 
 * Sujit Maharjan
 *
 * lab4
 * problem 3
 *
 * Write a class that can store Department ID and Department Name with constructors to initialize its members. Write destructor member in the same class and display the message "Object n goes out of the scope". Your program should be made such that it should show the order of constructor and destructor invocation.
 *
 */
#include <iostream>
#include <cstring>
#define SUCCESS 0

using namespace std;

class Department
{
private:
  int id;
  char name[20];
public:
  Department(int i, const char *n):id(i)
  {
    strncpy(name,n,20);
    cout << "Object "<< name << " has been contructed"<< endl;
  }
  ~Department()
  {
    cout << "Object "<< name << " goes out of scope" << endl;
  }
};
int main()
{
  Department d(1,"Walmart");
  return SUCCESS;
}
