/********
 *
 * Sujit Maharjan
 *
 * lab2
 * Define two namespaces: Square and Cube. In both the namespaces, define an integer variable named "num" and a function named "fun". The "fun" function in "Square" namespace, should return the square of an integer passed as an argument while the "fun" function in "Cube" namespace, should return the cube of an integer passed as an argument. In the main function, set the integer variables "num" of both the namespaces with different values. Then, compute and print the cube of the integer variable "num" of the "Square" namespace using the "fun" function of the "Cube" namespace and the square of the integer variable "num" of the "Cube" namespace using the "fun" function of the "Square" namespace
 ********/
// header file for input and output
#include <iostream>
// header file for input output manipulation
#include <iomanip>
// adding std namespace
using namespace std;
#define SUCESS 0

/********
 * namespace square
 ********/
namespace square
{
  int num;
  /********
   * \brief returns square of the no
   ********/
  int fun (int no)
  {
    return no * no;
  }
};

/********
 * namespace cube
 ********/
namespace cube
{

  int num;
  /********
   * \brief returns square of the no
   ********/
  int fun (int no)
  {
    return no * no * no;
  }
};
int main()
{
  cout << "Enter number for squaring?";
  cin >> square::num;
  cout << "square of " << square::num <<" is "<< square::fun(square::num) << endl;
  cout << "Enter number for cubing?";
  cin >> cube::num;
  cout << "cube of " << cube::num << " is " << cube::fun(cube::num) << endl; 
  return SUCESS;
}
