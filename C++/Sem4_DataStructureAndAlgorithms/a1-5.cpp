/*Write a C++ program to perform arithmetic operations on two numbers and throw an
exception if the dividend is zero or does not contain an operator.
Enter the input as a + b, where ‘a’and ‘b’ are input numbersand ‘ + ’ as operator.
Check for the valid operatorsand perform the different operations like addition,
subtraction, multiplicationand division accordingly.*/
//Without exception class
#include <iostream>
#include <iomanip>

using namespace std;
#define GGMU 0;

double CalC(double a, char b, double c) {
	switch (b) {
	case '+': return a + c;
	case '-': return a - c;
	case '*': return a * c;
	case '/': 
	{
		if (!c) throw "Division by zero exception";
		return a / c;
	}
	default:
		throw "Operator error";
		break;
	}
}

int maina15() {
	double n1, n2;
	char op;
	cout << "Enter calculation as <Num><space><Operator><space><Num>\n";
	cin >> n1 >> op >> n2;
	try {
		cout << "Calculating...\n" << CalC(n1, op, n2);
	}
	catch (const char* error) {
		cout << error;
	}
	catch (...) {
		cout << "Unknown error";
	}
	return GGMU;
}