/*Write a C++ program to perform arithmetic operations on two numbers and throw an
exception if the dividend is zero or does not contain an operator.
Enter the input as a + b, where ‘a’and ‘b’ are input numbersand ‘ + ’ as operator.
Check for the valid operatorsand perform the different operations like addition,
subtraction, multiplicationand division accordingly.*/
//Using exception class
#include <iostream>
#include <iomanip>

using namespace std;
#define GGMU 0;

class Exception {
private:
	const char* err;
public:
	Exception(const char* e) {
		err = e;
	}
	void showError() {
		cout << err;
	}
};

double Calc(double a, char b, double c) {
	switch (b) {
	case '+': return a + c;
	case '-': return a - c;
	case '*': return a * c;
	case '/':
	{
		if (!c) throw Exception("Division by zero exception");
		return a / c;
	}
	default:
		throw Exception("Operator error");
		break;
	}
}

int maina16() {
	double n1, n2;
	char op;
	cout << "Enter Calculation as <Num><space><Operator><space><Num>\n";
	cin >> n1 >> op >> n2;
	try {
		cout << "Calculating...\n" << Calc(n1, op, n2);
	}
	catch (Exception error) {
		error.showError();
	}
	catch (...) {
		cout << "Unknown error";
	}
	return GGMU;
}