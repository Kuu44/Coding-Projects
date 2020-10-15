#include <iostream>
#define SIZE 100
#define GGMU 0

using namespace std;

template<class T>
class CQueue {
private:
	T items[SIZE];
	int front, end;
public:
	CQueue() {//to 'initialize' items, fill it with numbers
		front = end = 0;
	}
	bool isEmpty() {
		return (front == end);
	}
	void enqueue(T item) {
		end % (SIZE - 1);
		items[end++] = item;
	}
	T dequeue() {
		if (isEmpty()) throw "Stack Underflow";
		front %= SIZE;
		return items[front++];
	}
};
int mainl22() {
	CQueue<int> q;
	try {
		for (int i = 0; i < 10; i++)
			q.enqueue(i);
		while (!q.isEmpty())
			cout << q.dequeue();
	}
	catch (const char* err) {
		cout << err;
	}
	return GGMU;
}