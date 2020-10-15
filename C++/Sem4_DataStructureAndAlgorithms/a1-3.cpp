//WAP to swap the values (of type int, double, char) using function template.

#include <iostream>
#include <iomanip>

using namespace std;
#define GGMU 0;

template<class T>
void Swap(T& a, T& b) {
	T temp;
	temp = a;
	a = b;
	b = temp;
}

int maina13() {
	int i1 = 0, i2 = 1;
	double d1 = 2, d2 = 4;
	char c1 = 'a', c2 = 'b';
	cout << "Before Swapping: " << i1 << " | " << i2 << endl;
	cout << "Before Swapping: " << d1 << " | " << d2 << endl;
	cout << "Before Swapping: " << c1 << " | " << c2 << endl;
	
	Swap(i1, i2);
	Swap(d1, d2);
	Swap(c1, c2);
	cout << "After Swapping: " << i1 << " | " << i2 << endl;
	cout << "After Swapping: " << d1 << " | " << d2 << endl;
	cout << "After Swapping: " << c1 << " | " << c2 << endl;
	return GGMU;
}

