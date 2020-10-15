#include <iostream>
#define SIZE 100
#define GGMU 0

using namespace std;

template<class T>
class DEQueue {
private:
	T items[SIZE];
	int front, end;
public:
	DEQueue() {//to 'initialize' items, fill it with numbers
		front = -1;
		end = 0;
	}
	bool isEmpty() {
		return (((front + 1) == end) || ((front == (SIZE - 1)) && (end == 0)));
	}
	bool isFull() {
		return (front == end);
	}
	void enqueueEnd(T item) {
		if (isFull()) throw "Stack Overflow";
		end %= SIZE;
		items[end++] = item;
	}
	T dequeueEnd() {
		if (isEmpty()) throw "Stack Underflow";
		(end < 0) ? end = (SIZE - 1) : end--;
		return items[end];
	}
	void enqueueFront(T item) {
		if (isFull()) throw "Stack Overflow";
		(front < 0) ? front = (SIZE - 1) : front--;
		items[front] = item;
	}
	T dequeueFront() {
		if (isEmpty()) throw "Stack Underflow";
		front %= SIZE;
		return items[front++];
	}
};
int mainl23() {
	DEQueue<int> q;
	try {
		for (int i = 0; i < 10; i++)
			q.enqueueEnd(i);
		for (int i = 0; i < 10; i++)
			q.enqueueFront(i);
		for (int i = 0; i < 10; i++)
			cout << q.dequeueFront() << '\n';
		for (int i = 0; i < 10; i++)
			cout << q.dequeueEnd() << '\n';
	}
	catch (const char* err) {
		cout << err;
	}
	return GGMU;
}