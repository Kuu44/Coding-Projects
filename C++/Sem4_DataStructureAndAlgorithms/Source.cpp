#include<iostream>
#include<string.h>

using namespace std;

struct polynomialType {
	int coef;
	int exp;
	polynomialType* head, * tail, * temp, * next;
};

class Polynomial {
private:
	polynomialType* temp, * head, * tail;
public:
	Polynomial() {
		head = NULL;
		tail = NULL;
	}
	void createPolynomial() {
		polynomialType* newnode = new polynomialType;
		char c = 'y';
		while (c == 'y' || c == 'Y') {
			cout << "Enter the coefficient: ";
			cin >> newnode->coef;
			cout << "Enter the order of the coefficient variable: ";
			cin >> newnode->exp;
			newnode->next = NULL;
			if (head == NULL && tail == NULL) {
				head = tail = newnode;
			}
			else {
				temp = tail;
				tail->next = newnode;
				tail = newnode;
			}
			cout << "Do you want to enter more elements (y/n): ";
			cin >> c;
		}
	}
	static polynomialType* add(polynomialType* poly1, polynomialType* poly2) {
		polynomialType* result = new polynomialType;
		result = result->next;
		result->next = NULL;
		while (poly1->next || poly2->next) {
			if (poly1->next) {
				result->coef = poly1->coef;
				result->coef = poly1->exp;
				poly1 = poly1->next;
			}
			else if (poly2->next) {
				result->coef = poly2->coef;
				result->coef = poly2->exp;
				poly2 = poly2->next;
			}
		}
		while (poly1->next && poly2->next) {
			if (poly1->exp > poly2->exp) {
				result->coef = poly1->coef;
				result->exp = poly1->exp;
			}
			else if (poly2->exp > poly1->exp) {
				result->coef = poly2->coef;
				result->exp = poly2->exp;
			}
			else if (poly1->exp == poly2->exp) {
				result->coef = poly1->coef + poly2->coef;
				result->exp = poly1->exp;
			}
		}	
		return result;
	}
	void display(polynomialType* poly) {
		temp = head;
		cout << "The addition of polynomials is: " << endl;
		while (temp->next != NULL) {
			cout << poly->coef << "x^" << poly->exp << " + ";
			temp = temp->next;
		}
		cout << temp->coef;
	}
};

int mainpp() {
	Polynomial poly1, poly2;
	cout << "Enter for 1st polynomial:" << endl;
	poly1.createPolynomial();
	cout << "Enter for 2nd polynomial:" << endl;
	poly2.createPolynomial();
	poly1.display(Polynomial::add(&poly1, &poly2));
	return 0;
}

