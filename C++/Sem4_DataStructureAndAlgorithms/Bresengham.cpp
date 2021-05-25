//Note: To test any part of the file, just remove the '/*' in that part of code

#include <iostream>

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

int main() {
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
}



