/********
 *
 * Sujit Maharjan
 *
 * WAP to create a class LandMeasure that reads Ropani,ana, paisa and Dam as its data members. Write a function to pass two object of type land measure and return its sum
 * 
 *******/

#include <iostream>

using namespace std;
#define SUCESS 0
#define PAISA_ANA 16
#define ANA_ROPANI 4
class LandMeasure
{
 private:
  int Ropani, ana, paisa;
 public:
  LandMeasure(int r, int a, int p)
  {
    paisa = p;
    ana = a + paisa / PAISA_ANA;
    paisa %= PAISA_ANA;
    Ropani = r + ana / ANA_ROPANI;
    ana %= ANA_ROPANI;
  }
  LandMeasure operator+(LandMeasure a)
  {
    return LandMeasure(a.Ropani+Ropani, a.ana+ana, a.paisa+paisa);
  }
  void display()
  {
    std::cout << Ropani << "ropani" << ana << "ana" << paisa << "paisa" << std::endl;
  }
};
int main()
{
  LandMeasure a(1,2,2);
  LandMeasure b(2,6,9);
  a.display();
  b.display();
  (a+b).display();
  return SUCESS;
}
