
/*****
 *
 * Sujit Maharjan
 *
 * lab 9
 * problem 1
 *
 *Create a function called sum ( ) that returns the sum of the elements of an array. Make this function into a template so it will work with any numerical type. Write a main ( ) program that applies this function to data of various type.
 *****/

#include <iostream>

#define SUCCESS 0
using namespace std;

template < typename T>
T sum(T array[],int n)
{
  T s= 0;
  for(int i = 0 ; i < n; i++)
  {
    s+=array[i];
  }
  return s;
}
int main()
{
  int num[] = {4,5,6};
  float fnum[] = {4.0,3.0,5.5};
  cout << sum(num,3) << endl;
  cout << sum(fnum,3) << endl;
  
  return SUCCESS;
}
