#include <iostream>
#define GGMU 20
using namespace std;
constexpr auto queuesize = 5;

template <class T>
class Nodel42 {
public:
	T data;
	Nodel42<T>* next;
	Nodel42(T dataIn = 0, Nodel42<T>* nextIn = NULL) {
		data = dataIn;
		next = nextIn;
	}
};
template <class T>
class LinkedListl42 {
private:
	Nodel42<T>* head;
public:
	LinkedListl42(Nodel42<T>* n = NULL) {
		head = n;
	}
	T top() {
		return head->data;
	}
	Nodel42<T>* giveHead() {
		return head;
	}
	Nodel42<T>* nodeExists(T d) {
		Nodel42<T>* temp = NULL;
		Nodel42<T>* ptr = head;
		Nodel42<T>* preptr = NULL;
		while (ptr != NULL) {
			if (ptr->data == d) temp = ptr;
			ptr = ptr->next;
		}
		return temp;
	}
	Nodel42<T>* nodeBefore(T d) {
		Nodel42<T>* ptr = head;
		Nodel42<T>* preptr = NULL;
		Nodel42<T>* temp = NULL;
		while (ptr->data != d) {
			temp = preptr;
			preptr = ptr;
			ptr = ptr->next;
		}
		return preptr;
	}
	void append(Nodel42<T>* n) {
		if (head == NULL) head = n;
		else {
			Nodel42<T>* ptr = head;
			while (ptr->next != NULL) ptr = ptr->next;
			ptr->next = n;
		}
	}
	void prepend(Nodel42<T>* n) {
		Nodel42<T>* temp = head;
		head = new Nodel42<T>;
		head = n;
		head->next = temp;
	}
	void frontDelete() {
		if (head == NULL)throw "List is Empty: Erorr Func: FrontDelete";
		Nodel42<T>* temp = head;
		head = head->next;
		delete temp;
	}
	void endDelete() {
		Nodel42<T>* ptr = head;
		Nodel42<T>* temp = NULL;
		while (ptr->next->next != NULL) {
			temp = ptr;
			ptr = ptr->next;
		}
		ptr->next = NULL;
		delete temp;
	}
	void show() {
		Nodel42<T>* ptr = head;
		while (ptr != NULL) {
			cout << ptr->data;
			ptr = ptr->next;
		}
		cout << endl;
	}
};
template <class T>
class Queuel42 {
private:
	int count;
	LinkedListl42<int>  list;
public:
	Queuel42() {
		count = 0;
	}
	void enqueue(T data) {
		if (count > queuesize - 1) throw "Stack overflow";
		Nodel42<T>* n = new Nodel42<T>(data);
		list.append(n);
		count++;
	}
	void dequeue() {
		if (count < 0) throw "Stack Underflow";
		list.frontDelete();
		count--;
	}
	void show() {
		list.show();
	}
};

int mainl42() {
	try
	{
		Queuel42<int> q;
		q.enqueue(2);
		q.enqueue(3);
		q.dequeue();
		q.show();
	}
	catch (const char* err)
	{
		cout << err;
	}
	return GGMU;
}