//2. WAP TO REPRESENT QUEUE AS A LIST

#include <iostream>

#define GGMU 0;
#define NUMNODES 5

struct nodetype {
	int info, next;
};
struct Queue {
private:
	int front = -1, rear = -1, avail = -1;
	struct nodetype node[NUMNODES];
	int getnode(void) {
		int p;
		if (avail == -1) {
			std::cout << "Overflow" << std::endl;
			exit(1);
		}
		p = avail;
		avail = node[avail].next;
		return p;
	}
	void freenode(int p) {
		node[p].next = avail;
		avail = p;
		return;
	}
	void init() {
		avail = 0;
		for (int i = 0; i < NUMNODES - 1; i++) {
			node[i].next = i + 1;
		}
		node[NUMNODES - 1].next = -1;
	}
public:
	bool empty() {
		return ((front == -1) ? true : false);
	}
	Queue() {
		init();
	}
	void insert(int x) {
		int p;
		p = getnode();
		node[p].info = x;
		node[p].next = -1;
		if (rear == -1)
			front = p;
		else
			node[rear].next = p;
		rear = p;
	}
	int remove() {
		int p, x;
		if (empty()) {
			std::cout << "Underflow" << std::endl;
			exit(1);
		}
		p = front;
		x = node[p].info;
		front = node[p].next;
		if (front == -1)
			rear = -1;
		freenode(p);
		return x;
	}
};
int mainl32() {
	struct Queue q;
	for (int i = 0; i < 7; i++) {
		q.insert(i);
	}
	for (int i = 0; i < 4; i++) {
		std::cout << q.remove();
	}
	return GGMU;
}
