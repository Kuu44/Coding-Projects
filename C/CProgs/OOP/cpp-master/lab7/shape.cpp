/***
 *
 * lab 7
 *
 * problem 1
 *
 * Write a program to create a class shape with functions to find area of the shapes and display the name of the shape and other essential component of the class. Create derived classes circle, rectangle and trapezoid each having overridden functions area and display. Write a suitable program to illustrate virtual functions and virtual destructor.
 *
 */

#include <iostream>
#include <cstring>
#define SUCESS 0
#define PIE 3.14
using namespace std;

class Shape {
 protected:
  string Sname;
  float Sarea;
 public:
  Shape()
  {
    Sname = "shape";
    Sarea = 0;
  }
  Shape(float a, string n="shape")
  {
    Sname = n;
    Sarea = a;
  }
  virtual float area()
  {
    return Sarea;
  }
  string name()
  {
    cout << "Shape " << Sname << endl;
    return Sname;
  }
  virtual ~Shape()
  {
    cout << "Destructor of Shape " << endl;
  }
};
class Circle:public Shape
{
 protected:
  float radius;
 public:
  Circle(int r, string n = "circle")
  {
    radius = r;
    Sname = n;
  }
  float area()
  {
    Sarea = PIE * radius * radius;
    return Shape::area();
  }
  string name()
  {
    cout << "Circle " << Sname << endl;
    return Sname;
  }
   ~Circle()
  {
    cout << "Circle destructor" << endl;
  }
  
};
class Rectangle:public Shape
{
 protected:
  float length, breadth;
 public:
  Rectangle(float l, float b, string n="rectangle"):length(l),breadth(b)
  {
    Sname = n;
  }
  float area()
  {
    Sarea = length*breadth;
    return Shape::area();
  }
  string name()
  {
    cout << "Rectangle " << Sname << endl; 
    return Sname;
  }
   ~Rectangle()
  {
    cout << "Rectangle destructor" << endl;
  }
};
class Trapezoid:public Shape
{
 protected:
  float paralleside[2];
  float nonParallelside[2];
 public:
  Trapezoid(float a1, float a2, float b1, float b2, string n= "Trapezoid")
  {
    paralleside[0] = a1;
    paralleside[1] = a2;
    nonParallelside[0] = b1;
    nonParallelside[1] = b2;
    Sname = n;
  }
  float area()
  {
    Sarea =  (paralleside[0]+paralleside[1])/2.0*(nonParallelside[0]+nonParallelside[1])/2.0;
    return Shape::area();
  }
  string name()
  {
    cout << "Trapezoid " << Sname << endl; 
    return Sname;
  }
   ~Trapezoid()
  {
    cout << "Trapezoid destructor" << endl;
  }
};
int main()
{
  Shape *sh;
  sh = new Circle(4,"ball");
  sh->name();
  cout << sh->area() << endl;
  delete(sh);
  sh = new Trapezoid(200,400, 100 , 100,"fancy stadium");;
  sh->name();
  cout << sh->area() << endl;
  delete(sh);
  sh = new Rectangle(240,240,"ground");;
  sh->name();
  cout << sh->area() << endl;
  delete(sh);
  return SUCESS;
}
