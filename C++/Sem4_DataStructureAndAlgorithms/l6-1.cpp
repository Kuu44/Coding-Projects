//a. FIND THE FACTORIAL FOR GIVEN NUMBER ‘N’.
#include <iostream>
#define GGMU 20;

using namespace std;

//Non tail
long int factorial(long int n) {
	if (n == 0) return 1;
	return n * factorial(n - 1);
}

long int mainl61() {
	cout << factorial(4);
	return GGMU;
}