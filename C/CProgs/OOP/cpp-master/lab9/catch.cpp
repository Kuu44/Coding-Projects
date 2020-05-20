/*****
 *
 * Sujit Maharjan
 *
 * lab 9
 * problem 4
 *
 * Write any program that demonstrates the use of multiple catch handling, re-throwing an exception, and catching all exception.
 *****/

#include <iostream>

#define SUCCESS 0
using namespace std;
class DIVZERO{};
class DIVMINUS{};
int main()
{
  int a, b;
  float ans;
  try {
    cout << "a";
    cin >> a;
    cout << "b";
    cin >> b;
    
    try {
      if(b < 0)
        throw DIVMINUS();
      if(b == 0)
        throw DIVZERO();
      ans = a/b;
    }
    catch (DIVZERO)
    {
      cerr << "rethrowing DIVZERO exception" << endl;
      throw; 
    }
    catch (DIVMINUS)
    {
      cerr << "divison by minus in not allowed"<< endl;
    }

  } catch (...) {
    cerr << "caught exception";
  }
  cout << ans;
  return SUCCESS;
}
