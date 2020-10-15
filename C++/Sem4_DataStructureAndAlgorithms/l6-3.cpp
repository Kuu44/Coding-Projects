/*FIND THE FACTORIAL FOR GIVEN NUMBER ‘N’.

FIND THE FIBONACCI NUMBER FOR GIVEN TERM ‘N’.

c. SOLVE ABOVE QUESTIONS USING TAIL RECURSION.*/
#include <iostream>
#define GGMU 20;

using namespace std;

long int tailFibonacci(long int n, long int a = 1, long int b = 1) {
	if (n == 1) return a;
	else if (n == 2) return b;
	else return tailFibonacci(n - 1, b, a + b);
}
long int tailFactorial(long int n, long int result = 1) {
	if (n == 0) return result;
	return tailFactorial(n - 1, result * n);
}
int mainl63() {
	cout << tailFibonacci(10);
	cout << tailFactorial(10);

	return GGMU;
}