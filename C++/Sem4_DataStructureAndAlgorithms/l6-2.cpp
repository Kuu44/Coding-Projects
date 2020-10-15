//b. FIND THE FIBONACCI NUMBER FOR GIVEN TERM ‘N’.
#include <iostream>
#define GGMU 20;

using namespace std;

long double Fibonacci(long double n) {
	if (n == 1 || n == 2) return 1;
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int mainl62() {
	long double f = 39;
	cout << Fibonacci(f);
	return GGMU;
}