/********
 *
 * Sujit Maharjan
 *
 * Wap that can store Department ID and Department name with constructor. Also write destructor in the same class and show that objects are destroyed in reverse order of creation with suitable message
 *******/

#include <iostream>
#include <cstring>
using namespace std;
#define SUCESS 0

class Department
{
 private:
  int id;
  char name[20];
 public:
  Department(int i, char n[])
  {
    id = i;
    strcpy(name,n);
  }
  ~Department()
  {
    cout << name << " is destroyed" << endl;
  }
};
int main()
{
  Department a(1, "Walmart");
  Department b(2,"Bhatbhatani");
  
  return SUCESS;
}
