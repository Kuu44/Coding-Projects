//WAP to swap the values(of type int, double, char) using class template.

#include <iostream>
#include <iomanip>

using namespace std;
#define GGMU 0;

template<class T>
class Val {
private:
	T first, second;
public:
	Val(T a, T b) {
		first=a;
		second=b;
	}
	void Display() {
		cout<< first << " | " << second << endl;
	}
	void Swap() {
		T temp;
		temp = first;
		first = second;
		second = temp;
	}
};

int maina14() {
	Val<int> in(0, 0);
	Val<double> dn(2, 3);
	Val<char> cn('a', 'b');
	cout << "Before Swapping: "; in.Display();
	cout << "Before Swapping: "; dn.Display();
	cout << "Before Swapping: "; cn.Display();

	in.Swap();
	dn.Swap();
	cn.Swap();
	cout << "After Swapping: "; in.Display();
	cout << "After Swapping: "; dn.Display();
	cout << "After Swapping: "; cn.Display();
	return GGMU;
}