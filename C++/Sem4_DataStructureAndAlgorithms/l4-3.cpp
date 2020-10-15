//WAP to represent Polynomial equation using linked list to perform addition of two polynomials
#include <iostream>
#define GGMU 20
using namespace std;
constexpr auto stacksize = 5;

template <class T>
class Nodel43 {
public:
	T data;
	Nodel43<T>* next;
	Nodel43(T dataIn, Nodel43<T>* nextIn = NULL) {
		data = dataIn;
		next = nextIn;
	}
};
template <class T>
class LinkedListl43 {
private:
	Nodel43<T>* head;
public:
	Nodel43<T>* giveHead() {
		return head;
	}
	LinkedListl43(Nodel43<T>* n = NULL) {
		head = n;
	}
	Nodel43<T>* nodeExists(T d) { //code = 1 for ptr and code =-1 for pre-ptr;
		Nodel43<T>* temp = NULL;
		Nodel43<T>* ptr = head;
		Nodel43<T>* preptr = NULL;
		while (ptr != NULL) {
			if (ptr->data == d) temp = ptr;
			ptr = ptr->next;
		}
		return temp;
	}
	Nodel43<T>* nodeBefore(T d) {
		Nodel43<T>* ptr = head;
		Nodel43<T>* preptr = NULL;
		Nodel43<T>* temp = NULL;
		while (ptr->data != d) {
			temp = preptr;
			preptr = ptr;
			ptr = ptr->next;
		}
		return preptr;
	}
	void append(Nodel43<T>* n) {
		if (head == NULL) {
			head = n;
		}
		else {
			Nodel43<T>* ptr = head;
			while (ptr->next != NULL) {
				ptr = ptr->next;
			}
			ptr->next = n;

		}
	}
	void prepend(Nodel43<T>* n) {
		Nodel43<T>* temp = head;
		head = new Nodel43<T>;
		head = n;
		head->next = temp;
	}
	void insertNodeAfter(T data, Nodel43<T>* n) {
		Nodel43<T>* ptr = nodeExists(data);
		if (ptr->next == NULL) {
			cout << "Node with" << data << " value is non existent" << endl;
		}

		else {
			n->next = ptr->next;
			ptr->next = n;
		}
	}
	void insertNodeBefore(T data, Nodel43<T>* n) {
		Nodel43<T>* ptr = nodeBefore(data);
		if (ptr == NULL) {
			cout << "Node with" << data << " value is non existent" << endl;
		}
		else {
			n->next = ptr->next;
			ptr->next = n;

		}
	}
	void frontDelete() {

		if (head == NULL)throw "List is Empty: Erorr Func: FrontDelete";
		Nodel43<T>* temp = head;
		head = head->next;
		delete temp;
	}
	void endDelete() {
		Nodel43<T>* ptr = head;
		Nodel43<T>* temp = NULL;
		while (ptr->next->next != NULL) {
			temp = ptr;
			ptr = ptr->next;
		}
		ptr->next = NULL;
		delete temp;

	}
	void deleteAfter(T data) {
		Nodel43<T>* ptr = nodeExists(data);
		if (ptr == NULL) {
			cout << "Node with" << data << " value is non existent" << endl;
			exit(1);
		}
		Nodel43<T>* temp = ptr->next;
		ptr->next = ptr->next->next;
		delete temp;
	}
	void show() {
		Nodel43<T>* ptr = head;
		while (ptr != NULL) {
			cout << ptr->data;
			ptr = ptr->next;
		}
		cout << endl;
	}
};
template <class T>
LinkedListl43<T> add(LinkedListl43<T> l1, LinkedListl43<T> l2) {
	LinkedListl43<T> list;
	Nodel43<T>* ptr = l1.giveHead();
	for (Nodel43<T>* ptr2 = l2.giveHead(); ptr2 != NULL; ptr2 = ptr2->next) {
		Nodel43<T>* n1 = new Nodel43<T>((ptr->data) + (ptr2->data));
		list.append(n1);
		ptr = ptr->next;
	}
	return list;
}
template <class T>
void displayPolar(LinkedListl43<T> list, int degree) {

	Nodel43<T>* ptr = list.giveHead();
	int count = 0;
	while (ptr) {
		if (count == 0) {
			if (ptr->data != 0)	cout << ptr->data;
			count++;
			ptr = ptr->next;
		}
		else {
			if (ptr->data != 0)	cout << ptr->data;
			cout << "x^";
			cout << count;

			ptr = ptr->next;
			count++;
		}
		if (count <= degree) cout << '+';
	}
}
int mainl43() {
	int degree, temp;
	LinkedListl43<int> l1, l2;
	cout << "Enter the degree of polynomial eqn";
	cin >> degree;
	try {
		cout << "for first polynomial eqn, " << endl;
		cout << "Enter you coefficent from c0 to cn (spaces in between)";
		for (int i = 0; i <= degree; i++) {
			cin >> temp;
			Nodel43<int>* n = new Nodel43<int>(temp);
			l1.append(n);
		}
		cout << "for second polynomial eqn, " << endl;
		cout << "Enter you coefficent from c0 to cn(spaces in between)";
		for (int i = 0; i <= degree; i++) {
			cin >> temp;
			Nodel43<int>* n = new Nodel43<int>(temp);
			l2.append(n);
		}
		cout << "\n The addition of the polynomials give: ";
		displayPolar(add(l1, l2), degree);
	}
	catch (const char* err) {
		cout << err;
	}
	return GGMU;
}