/*********
 *
 * Sujit Maharjan
 * lab 6
 *
 * problem 3 
 * 3.Create a class called Musicians to contain three methods string ( ), wind ( ) and perc ( ). Each of these methods should initialize a string array to contain the following instruments
 -  veena, guitar, sitar, sarod and mandolin under string ( )
 -  flute, clarinet saxophone, nadhaswaram and piccolo under wind ( )
 -  tabla, mridangam, bangos, drums and tambour under perc ( )
 It should also display the contents of the arrays that are initialized. Create a derived class called TypeIns to contain a method called get ( ) and show ( ). The get ( ) method must display a  menu as follows

 Type of instruments to be displayed
 a. String instruments
 b. Wind instruments
 c. Percussion instruments
 The show ( ) method should display the relevant detail according to our choice. The base class variables must be accessible only to its derived classes
 **********/
#include <iostream>
#include <cstring>
#define SUCCESS 0

class Musicians
{
 protected:
  std::string str[5];
  std::string wnd[5];
  std::string per[5];
 public:
  void string()
  {
    str[0] ="vern";
    str[1]="guitar";
    str[2]="sitar";
    str[3]="sarod";
    str[4]="mandolin";
    std::cout<< "string instrument has been initialized to" << std::endl;
    for(int i = 0 ; i < 5; i++)
    {
      std::cout << str[i] << std::endl;
    }
  }
  void wind(){
    
    wnd[0]="flute";
    wnd[1]="mridangam";
    wnd[2]="bangos";
    wnd[3]="drums";
    wnd[4]="tambour";
    std::cout<< "wind instrument has been initialized to" << std::endl;
    for(int i = 0 ; i < 5; i++)
    {
      std::cout << wnd[i] << std::endl;
    }
  }
  void perc()
  {
    per[0]="tabla";
    per[1]="mridangam";
    per[2]="bangos";
    per[3]="drums";
    per[4]="tambour";
    std::cout<< "percussion instrument has been initialized to" << std::endl;
    for(int i = 0 ; i < 5; i++)
    {
      std::cout << per[i] << std::endl;
    }
  }
};
class TypeIns:public Musicians
{
 public:
  std::string* get()
  {
    std::cout<<"Type of instrument to be displayed" << std::endl;
    std::cout << "a. String instruments" << std::endl;
    std::cout << "b. Wind instruments" << std::endl;
    std::cout << "c. Percussion instruments" << std::endl;
    char choice;
    std::cin >> choice;
    show(choice);
  }
  void show(char choice)
  {
    if(choice == 'a')
    { 
      for(int i = 0 ; i < 5; i++)
      {
        std::cout << str[i] << std::endl;
      }      
    }
    else if(choice == 'b')
    {
      for(int i = 0 ; i < 5; i++)
      {
        std::cout << wnd[i] << std::endl;
      }
    }
    else
    {
      for(int i = 0 ; i < 5; i++)
      {
        std::cout << per[i] << std::endl;
      }
    }
  }
};
int main()
{
  TypeIns t;
  t.string();
  t.perc();
  t.wind();
  t.get();
  return SUCCESS;
}
