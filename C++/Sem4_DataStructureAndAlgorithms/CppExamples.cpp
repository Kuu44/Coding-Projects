//Note: To test any part of the file, just remove the '/*' in that part of code

#include<iostream>
#include<cmath>
#include<typeinfo>
#include<vector>
#include<algorithm>
#define PI 3.14156
#define MAXSIZE 50

#pragma region IntroFunctions

/*boolean*/
bool ANDGate(bool a, bool b) {
	return (a && b);
}

/*Scope and Scope Resolution*/
namespace Ishani {
	std::string surname = "Malla";
	void sleep() {
		std::cout << "Snore";
	}
}

/*struct and union*/
struct Animal {
	std::string name;
	int noOfFeet;
};
union Triangle {
	int cornerA;
	int cornerB;
	int cornerC;
};

/*class*/
class Person {
private:
	int a;
	
public:
	static int b;

	Person(int A):a(A){}
	Person(int A, int B):a(A){
		b = B;
	}
	int getA(){
		return a;
	}
	int getB() {
		return b;
	}
};

/*function overloading*/
int Add(int a, int b) {
	return a+b;
}
float Add(float a=5, float b=3.14) {  //Add(float)
	return a+b;
}
void Add(int a, float b) {
	std::cout << "\nEaster Egg";
}
double Add(double a, double b) {
	return a+b;
}
int Addition(int a, int b) {
	return a += b;
}

/*Pass by reference*/
int Addition2ElectricBoogaloo(int &a, int &b) {
	return a += b;
}

/*Return by reference*/
int& stupidAddition(int &x) {
	x += 2;
	return x;
}
#pragma endregion
#pragma region ClassesAndStuff

class Aanimal {
private:
	int noOfFeet;
	void Heartbeat();
	const int noOfEyes;

protected:

public:
	static std::string Class; //static data member
	std::string cry;
	char color;
//Constructors
	Aanimal():noOfEyes(2) {
		noOfFeet = 0;
		color = 'b';
		cry = "something";
		std::cout << "Aanimal is now created\n";
		Class = "Mammal";
	}
	Aanimal(int feet, char col, std::string c):noOfEyes(2) {
		noOfFeet = feet; 
		color = col; 
		cry = c;
		std::cout << "Aanimal is now created\n";
	}	
	Aanimal(std::string c, int feet, char col) : cry(c),noOfFeet(feet),color(col), noOfEyes(2) {} //cry(c) means cry=c;

	Aanimal(int noOfFeet, std::string cry, char color) :noOfEyes(2) {
		this->noOfFeet = noOfFeet; this->cry = cry; this->color = color;
	}

	/*Working of Copy constructor
	Aanimal(Aanimal animal) {
		noOfFeet = animal.noOfFeet;
		color = animal.color;
	}
	*/
	~Aanimal() {
		std::cout << "Aanimal is now destroyed\n";
	}

	void Cry() {
		Heartbeat();
		std::cout << "Some animal with "<<getNoOfFeet()<<" feet and of "<<color<<" color, says: "<<cry<<"\n";
	}
	int getNoOfFeet() const{
		return noOfFeet;
	}
	//Declaring member function
	void setNoOfFeet(int);

	static void PrintClass() {
		std::cout << Class;
	}

};
//Defining Member functions
void Aanimal::Heartbeat() {
	std::cout << "Dhuk dhuk\n";
}
void Aanimal::setNoOfFeet(int feet) {
	noOfFeet = feet;
}
//Passing Objects and returning objects from functions
int PrintFeet(Aanimal anim) {
	return anim.getNoOfFeet();
}
Aanimal InitializeCow() {
	Aanimal anim(4, 'w', "moo");
	return anim;
}
//Friend Class
class Person1 {
private:
	std::string secret;
public:
	Person1() {
		secret = "I have 6 toes";
	}
	friend class Person2;
};
class Person2 {

private: 
	std::string secret;
public:
	Person2() {
		secret = "I hate going to cinemas";
	}
	void tellSecret(Person1 p) {
		std::cout << p.secret;
	}
	void tellSecret2(Person1 p) {
		std::cout << p.secret; 
	}
	friend void tellSecrets(Person2);
};
//Friend Function
void tellSecrets(Person2 p) {
	std::cout << p.secret;
}

#pragma endregion
#pragma region Operators

class Complex {
private:
	float real, imag;
public:
	Complex():real(0),imag(0) {}
	Complex(float r, float i) :real(r), imag(i) {}
	Complex(int r) {
		real = r; imag = 0;
	}
	explicit Complex(float r) {
		real = r; imag = 0;
	}
	
	Complex add(Complex c1) {
		Complex result; 
		result.real= real + c1.real;
		result.imag = imag + c1.imag;
		return result;
	}
	
	//Defining operator in class
	/*Complex operator+(Complex right) {
		Complex result;
		result.real = real + right.real;
		result.imag = imag + right.imag;
		return result;
	} */
	//Defining operator outside of class
	Complex operator-(Complex);
	//Defining operator as friend function
	friend Complex operator*(Complex, Complex);
	//Prefix
	friend void operator++(Complex);
	//Postfix
	friend void operator++(Complex, int);
	friend Complex _Add(Complex, Complex);
	//Type Conversion
	operator int() {
		int r = real;
		return real;
	}
	void print() {
		std::cout << "The number is " << real << " +i" << imag << std::endl;
	}
};
Complex Complex::operator-(Complex right) {
	Complex result;
	result.real = real - right.real;
	result.imag = imag - right.imag;
	return result;
}
Complex operator*(Complex left, Complex right) {
	Complex result;
	result.real = (left.real * right.real) - (left.imag * right.imag);  // (A+iB)*(C+iD) = (AC-BD)+i(AD+BC)
	result.imag = (left.real * right.imag) + (left.imag * right.real);
	return result;
}
void operator++(Complex right) {
	++right.real; ++right.imag;
}
void operator++(Complex left, int) {
	left.real++; left.imag++;
}
/*
//Type Conversion
class Cartesian {
private:
	int x, y;
public:
	Cartesian() :x(0), y(0) {}
	Cartesian(int x, int y) {
		this->x = x; this->y = y;
	}
	Cartesian(Polar p) {
		float radian = p.😅 * PI / 180;
		x = p.r * cos(radian);
		y = p.r* sin(radian);
	}
	operator Polar() {
		int r = sqrt(x * x + y * y);
		int theta = atan2(y, x);
		Polar p(r, theta);
		return p;
	}
	void print() {
		std::cout << "The number is (" << x << ", " << y << ")" << std::endl;
    }
};
class Polar {
private:
	int r, 😅;
public:
	Polar():r(0), 😅(0){}
	Polar(int r, int 😅) {
		this->r = r; this->😅 = 😅;
	}
	operator Cartesian() {
		float radian= 😅*PI/180;
		Cartesian c ( r*cos(radian), r*sin(radian) );
		return c;
	}
	void print() {
		std::cout << "The number is " << r << " <" << 😅 << std::endl;
	}
	friend class Cartesian;
};
*/
#pragma endregion
#pragma region Inheritance

class Parent {
private:
	int cuteness;
protected:
	std::string name;
public:
	std::string surname;
	int noOfTeeth;
	Parent(){}
	Parent(std::string nam, std::string surnam, int teeth, int cute):name(nam),
		surname(surnam),noOfTeeth(teeth){}
	void printBio() {
		std::cout << "This is " << name << " " << surname << ". Who has " << noOfTeeth
			<< " teeth"<<std::endl;
	}
};
class Child : public Parent{
public:
	std::string favColor;
	Child(std::string nam, std::string surnam, int teeth, std::string col){
		name = nam; surname = surnam; noOfTeeth = teeth; favColor = col; 
	}
	void printBio() {
		Parent::printBio();
		std::cout << " and likes "<<favColor << std::endl;
	}
};
//Single Inheritance
class Base1 {};
class Derived1 : public Base1 {};

//Multiple Inheritance
class A2 {
public:
	void shout() { std::cout << "I am A";}
}; 
class B2 {
public:
	void shout() {std::cout << "I am A";}
};
class C2 : public A2, public B2 {
public:
	void speak() { 
		A2::shout(); B2::shout(); //Solving ambiguity
	}
};

//Multilevel Inheritance
class GP3 {
public:
	void doSomething() {}
};
class P3 : protected GP3 {};
class C3 : public P3 {};

//Hierarchical Inheritance
class A4 {};
class B4 :public A4 {}; class C4 :public A4 {};

//Hybrid Inheritance
class GrandParent {
public:
	std::string name;
	GrandParent():name("GrandParent"){}
	void who() {
		std::cout << "I am in " << name << std::endl;
	}
};
class Mom : public virtual GrandParent{
public:
	Mom(){
		name = "Mom";
	}
}; 
class Dad : public virtual GrandParent {
public:
	Dad() {
		name = "Dad";
	}
};
class CChild : public Mom, public Dad {
public:
	CChild(){
		name = "Child";
	}
};
//Order of Invocation
class BaseClass {
public:
	std::string name;
	BaseClass(){}
	BaseClass(std::string name) {
		std::cout << "This is "<<name<<"'s Base Constructor\n";
	}
	~BaseClass() {
		std::cout << "This is the Base Destructor\n";
	}
};
class DerivedClass : public BaseClass {
public:
	int a;
	DerivedClass() {}
	DerivedClass(std::string name, int a):BaseClass(name) {
		std::cout << "This is " << name << "'s Derived Constructor\n";
	}
	~DerivedClass() {
		std::cout << "This is the Derived Destructor\n";
	}
};
class VeryDerivedClass : public DerivedClass {
public:
	float b;
	VeryDerivedClass() {}
	VeryDerivedClass(std::string name, int a, float b):DerivedClass(name, a) {
		std::cout << "This is " << name << "'s Very Derived Constructor\n";
	} 
	~VeryDerivedClass() {
		std::cout << "This is the Very Derived Destructor\n";
	}
};

//Order of Invocation in Multiple Inheritance
class A6{
public:
	A6() {
		std::cout << "This is A6's Constructor\n";
	}
};
class B6{
public:
	B6() {
		std::cout << "This is B6's Constructor\n";
	}
};
class C6 :public B6, public A6 {
public:
	C6() {
		std::cout << "This is C6's Constructor\n";
	}
};
#pragma endregion
#pragma region Polymorphism

class Vehicle {
public:
	int wheels;
	virtual void howManyWheels() = 0;
};
class Car : public Vehicle {
public:
	Car() {
		wheels = 4;
	}
	std::string paint = "red";
	void howManyWheels() override  {
		std::cout << "A car has " << wheels << " wheels\n";
	}
}; 
class MotorBike : public Vehicle {
public:
	MotorBike() {
		wheels = 2;
	}
	std::string paint = "blue";
	void howManyWheels() override {
		std::cout << "A motorbike has " << wheels << " wheels\n";
	}
};
class Tempo : public Vehicle {
public:
	Tempo() {
		wheels = 2;
	}
	std::string paint = "green/white";
	void howManyWheels() override {
		std::cout << "A Tempo has "<<wheels<<" wheels\n";
	}
};
class People {
public:
	Vehicle *vehicle;
};
#pragma endregion
#pragma region Templates
//Problem

/*void Print(int n) {
	std::cout << "The integer is " << n << std::endl;
}
void Print(float n) {
	std::cout << "The float is " << n << std::endl;
}
void Print(long double n) {
	std::cout << "The double is " << n << std::endl;
}
void Print(std::string n) {
	std::cout << "The string is \""<< n <<"\""<< std::endl;
}*/
//Solution with Templates
template<class T>
void Print(T n) {
	std::cout << "The "<<typeid(T).name()<<" is " << n << std::endl;
}
//Dangers of templates
/*int _Add(int left, int right) {
	std::cout << "The second parameter is " << typeid(int).name() << std::endl;
	return left + right; //if i replace left with lef here in a template, no error
}*/
template<class T1, typename T2>
T1 _Add(T1 left, T1 right) {
	std::cout << "The second parameter is " << typeid(T2).name() << std::endl;
	return left + right;
}
//Template overloading
template<typename T2>
Complex _Add(Complex left, Complex right) {
	std::cout << "The second parameter is " << typeid(T2).name() << std::endl;
	Complex result;
	result.real = left.real + right.real;
	result.imag = right.imag + right.imag;
	return result;
}
void Print(Complex n) {
	n.print();
}
template<class T>
void Print(T n, T n2) {
	std::cout << "The values are " << n << " and " << n2 << std::endl;
}

//Default Template arguments
template<class T1, class T2=int>
void Cry(T1 n, T1 n2) {
	T2 c = 5;
	std::cout << n + n2 + c<<std::endl;
}

template<typename T>
class Cartesian {
private:
	T x, y;
public:
	Cartesian() :x(0), y(0) {}
	Cartesian(T x, T y) {
		this->x = x; this->y = y;
	}
	void print() {
		std::cout << "The number is (" << x << ", " << y << ")" << std::endl;
	}
};

//Derived Templates
//Case 1: non-template derived, template base 
template<class T>
class base1{
public:	T a;
};
class derived1 : public base1<int> {
public: int b;
};
//Case 2: non-template base, template derived
class base2{
public: int a;
};
template<class T>
class derived2:public base2{
public: T b;
};
//Case 3: template base, template derived
template<class T>
class base3 {
public: T a;
};
template<class T>
class derived3 :public base3<int> {
public:	T b;
};
//Case 4: template derived, template base both of same type templates
template<class T>
class base4{
public: T a;
};
template<class T>
class derived4:public base4<T>{
public: T b;
};
//Case 5: template derived, template base, but with different no of arguments
template<class T>
class base5 {
public: T a;
};
template<class T1, class T2>
class derived5 :public base5<T1> {
public: T2 b;
};
template<class T1, class T2>
class base6{
public: T1 a; T2 b;
};
template<class T>
class derived6 : public base6<T, float> {};
#pragma endregion

int main() {
#pragma region Introduction
	//static key word
		/*Person A(1,2), B(2,3), C(3,4);

		cout << "A: a=" << A.getA() << " b=" << A.getB() << endl;
		cout << "B: a=" << B.getA() << " b=" << B.getB() << endl;
		cout << "C: a=" << C.getA() << " b=" << C.getB() << endl;

		cout << "hello";
		return 0;
		int cat = 5;
		*/

		//Arrays and Pointers
		/*int a[3];

		a[0] = 1; a[1] = 2; a[2] = 3;

		int* b = a;
		cout << "Array: " << a[1] << endl;
		cout << "Pointer: " << *(a+1);
		*/

		//Scope and Scope Resolution
		/*int* a;
		{
			int b = 6;
			{
				a = &b;
				cout << "Inside scope: " << b <<" "<< *a;
			}
		}

		Person p(5);
		p.b;
		Person::b;

		cout << Ishani::surname<<endl;
		Ishani::sleep();
		*/

		//Struct, Union and Enum
		/*
		Animal anim;
		anim.name = "Cow";
		anim.noOfFeet = 4;

		Triangle tri;
		tri.cornerA = 5;
		tri.cornerB = 6;

		Animal a1, a2, a3;
		*/

		//Ternary Operator
		/*
		int A = 2, B = 3, C = 4;

		//to find max of 3 numbers
		if (A > B) {
			if (A > C) {
				cout << A;
			}
			else {
				cout << C;
			}
		}
		else {
			if (B > A) {
				cout << B;
			}
			else {
				cout << C;
			}
		}

		cout << (A > B) ? ( (A > C) ? A : C): ((B > A) ? B : C);
		*/

		//Type Casting
		/*
		short int a; double b = 2.156;

		cout << (b)<<endl;

		a = (int)b;
		cout << a <<endl;

		b = (double)a;
		cout << b;
		*/

		//Dynamic Memory Allocation
		/*
		int a=5;

		int* b = new int[3];
		float c=9;

		b[1] = 8;

		delete b;

		int d;
		*/

		//For Loop
		/*
		int i;
		for (
			i = 0; //initializer - runs once on start
			i < 5; //conditional statement - runs loop till true
			i = i+2    //runs once on every loop
			) {}

		float b = 4;

		for (int c = 2; b != 20; cout << b<<"yo\n") {
			b += c; // b=b+c
		}*/

		//Function Overloading
		/*
		int ai = 1, bi = 2;
		float af = 3.4, bf = 4.4;
		double ad = 6.786787, bd = 7.878787;

		std::cout << "Int: " << Add(ai, bi) << "\nFloat: " << Add(af, bf) << "\nDouble: " << Add(ad, bd);
		Add(ai, af);

		std::cout << "\nDefault: " << Add(af);
		*/

		//Pass and Return by reference
		/*
		int x = 5, y = 6;

		std::cout << Addition(x, y) << " Value of x: " << x<<std::endl;
		std::cout << Addition2(x, y) << " Value of x: " << x<<std::endl;
		std::cout << "Answer is: " << stupidAddition(y)<< "Value of y: "<< y<<'\n';
		stupidAddition(y) = 20; //Address = 20
		std::cout <<'\n'<< y;
		*/
#pragma endregion
#pragma region Classes

//Static
/*
Aanimal::Class = "Mammal"; //can be directly accessed by the scope resolution operator

Aanimal defAnimal, cat(4,'g',"meow");
Aanimal* pointerCat;
pointerCat = &cat;
*/
//Usage of copy constructor
/*
Aanimal dog(cat);
dog.color = 'b';
dog.cry = "bark";
*/
//Calling a static function
/*
cat.PrintClass();
dog.PrintClass();
Aanimal::PrintClass();
*/
/*Aanimal dogs[MAXSIZE];
for (int i = 0; i < 10; i++) {
	dogs[i] = Aanimal(dog);
}*/

//int var; float variab; double variable;

//animal.setNoOfFeet(4); //setting value of private members
/*
defAnimal.Cry(); //defaut constructor
cat.Cry(); //Parameterized constructor

if (cat.getNoOfFeet() == 4) {
	std::cout << "The animal has 4 feet";
}
*/
//delete(pointerCat);

//dog.Cry(); //Copy constructor
//animal.color = 5; //Setting value  of public members

//Class pointers: These three lines have the same meaning
/*
cat.Cry();
(*pointerCat).Cry(); //Dont do pointerCat.Cry()
pointerCat->Cry(); // -> = (*).
*/
//Returning objects
/*
std::cout << PrintFeet(cat) << std::endl;
Aanimal cow(InitializeCow());
cow.Cry();
*/
//Type Casting
/*
int a = 0;
int* aP; aP = &a;

float f=1; float* fP;

f = static_cast<float>(a); f = (float)a;
fP = reinterpret_cast<float*>(aP);
*/
//Const Cast
/*
const int var = 5; int var2;
const int* ptr = &var;

var2 = var;

int* ptr1 = const_cast<int*>(ptr);
*/
//Friend Functions
/*
Person1 p1;
Person2 p2;
p2.tellSecret(p1);
*/
#pragma endregion
#pragma region Operators
/*
Complex c1(1, 2), c2(2, 3);
Complex c3 = c1.add(c2);

c1.print();
c2.print();

c3.print();

Complex c4 = c3 + c2;
c4.print();

(c4 + c3).print();

Complex c5 = c3 + 2;
c5.print();
Complex c6 = c1 * c2;
c6.print();
*/
//prefix and postfix
/*
Complex preNpost(1,1);

std::cout << "Prefix: "; 
++preNpost;
preNpost.print();

//std::cout << "Postfix: "<< preNpost++ <<std::endl;
//std::cout << preNpost << std::endl;
*/
//Type conversion
/*
Complex c7(7, 7);
float f = 8; int real = 0;
//Basic to Basic
real = (int)f; f = real;
//User Defined to Basic Type
real = (int)c7; real = c7;
//Basic to User Defined Type
Complex c8 = (Complex)real; c8 = real;
//explicit construction
Complex c9(float(9));
std::cout << "The converted value is" << real << '\n';
c8.print();
*/
//User Defined to User Defined
/*
Polar p(5, 45); Cartesian c(10, 10);
Cartesian pC = p;
pC.print();
*/
#pragma endregion
#pragma region Inheritance
//Inheritance
/*
Parent Ishani("Ishani","Malla",32,10000);
Child LilIshani("Isha","Malla",16,"red");

Ishani.printBio();
LilIshani.printBio();
*/
//Ambiguity and virtual class
/*
Mom m; Dad d; CChild c;
m.who(); d.who();
c.who();
*/
//Order of Invocation
/*
VeryDerivedClass Inheriter("Inheriter", 5 , 5.0f);
C6 c;
*/
#pragma endregion
#pragma region Polymorphism
/*Vehicle vehicle; //Base Var
Car car; //Derived Var
//Using Vars
vehicle.howManyWheels();
car.howManyWheels();
car.Vehicle::howManyWheels();

vehicle = car;
car2 = vehicle;
vehicle.howManyWheels();

//vs using pointers
MotorBike m1;
Vehicle* v = &vehicle;
Car* c = &car;
MotorBike* m = &m1;

v->howManyWheels();
c->howManyWheels();

v = c;
v->howManyWheels();
v = m;
v->howManyWheels();

//Universal Pointer
int* i; float* f;
void* dd;
dd = i;
dd = f;

//Need of Polymorphism eg:
People p[3];

//Car car;
// vehicle = &car;
p[0].vehicle = new Car();
p[1].vehicle = new MotorBike();
p[2].vehicle = new Tempo();

for (int i = 0; i < 3; i++) {
	p[i].vehicle->howManyWheels();
}
//Dynamic Casting
Vehicle* v;

MotorBike* m = new MotorBike();
Car* c1 = new Car();
Car* c2;

v = c1;
if (m = dynamic_cast<MotorBike*>(v))
{
	m = reinterpret_cast<MotorBike*>(v);
	std::cout << "Assign value to m";
}
else std::cout << "Dont assign value to m";

if (c2 = dynamic_cast<Car*>(v)) {
	c2 = reinterpret_cast<Car*>(v);
	std::cout << "Assign value to c";
}
else std::cout << "Dont assign value to m";

//Type id
Vehicle* v; 
Car* c=new Car();
MotorBike* m = new MotorBike(); Tempo* t= new Tempo();
std::cout << typeid(t).name()<<std::endl;
std::cout << typeid(*t).name()<<std::endl;
std::cout << typeid(v).name()<<std::endl;
std::cout << typeid(*m).name()<<std::endl;

//Pass by value
int a = 5;
int b;
b = a;
b = 6;
std::cout << a;

//Pass by reference
int* cP;
int* aP = new int(5);
cP = aP;
*cP = 6;
std::cout << *aP;

//Calling functions

vehicle.howManyWheels();//from variable
v->howManyWheels(); //from Pointer
*/
#pragma endregion
#pragma region Templates
//calling template functions
/*Print<int>((int)5);
Print<float>(5.546f);
Print<long double>(6.567l);
Print<std::string>("some string");*/

//but compiler can understand from argument
/*Print(5);
Print(5.546f);
Print(6.567l);
Print("some string");*/

//Functions that need declaring
/*int a = 8, b = 9;
float af = 8, bf = 9;
double ad = 8, bd = 9;
long al = 8, bl = 9;
int c = _Add<int,double>(a, b);
float cf = _Add<float,int>(af, bf);
double cd = _Add<double,float>(ad, bd);
long cl = _Add<long,float>(al, bl);
//std::cout<<"The result is " << c << std::endl;
Print(c); Print(cf); Print(cd); Print(cl);*/

//Template overloading
/*Complex c1(5, 6), c2(8, 9);
Complex c3 = _Add<Complex, float>(c1, c2);
Print(c3);*/

//Default parameters
/*Cry(5, 6); //Cry<int>(5, 6); //Cry<int, int>(5, 6);
Cry(5.0f, 6.0f); //Cry<float, int>(5.0f, 6.0f);
Cry(5.0l, 6.0l); //Cry<double, int>(5.0l, 6.0l);*/

//Class Templates
Cartesian<int> ci(5, 6);
Cartesian<float> cf(5.01f, 6.02f);
Cartesian<double> cd(5.0989l, 6.676l);
Cartesian<Complex> cc(Complex(1, 2), Complex(3, 4));

ci.print(); cf.print(); cd.print();

//Derived Templates
base1<int> b;
derived1 d;
derived2<double> d2;
derived4<float> d2;
derived3<double> d3;
derived5<double, long double> d5;
derived6<int> d6;
//Standard Template Library
std::vector<int> v; std::vector<float> v2;
int a[5];
int i;
while (/*im taking input*/1) 
	a[i++] = /*input*/1; //Gives error after 5 inputs

while (/*im taking input*/1)
v.push_back(1); v2.push_back(5.0f); // push in inputs. can input "any" number of items

v.pop_back(); //removing items from vector

v.at(2); // similar to a[2]

//algorithm library
//qsort(void*, &a, 5);
#pragma endregion
return 0;
}


