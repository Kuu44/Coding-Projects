//1. WAP TO INSERT AND DELETE IN A LIST
#include <iostream>
#include <stdlib.h>
#define GGMU 1;

#define NUMNODES 500

struct Nodel31 {
	int info, next;
};
class Listl31 {
private:
	int avail = -1;
	int start;
	struct Nodel31 node[NUMNODES];

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
	Listl31(int first) {
		init();
		start = getnode();
		node[start].info = first;
		node[start].next = -1;
	}

	// p is the node after which to insert, x is the value of new node
	void insafter(int p, int x) {
		int q;
		if (p == -1) {
			std::cout << "Void insertion" << std::endl;
			return;
		}
		q = getnode();
		node[q].info = x;
		node[q].next = node[p].next;
		node[p].next = q;
		return;
	}
	void delafter(int p, int* px) {
		int q;
		if ((p == -1) || (node[p].next == -1)) {
			std::cout << "Void deletion" << std::endl;
			return;
		}
		q = node[p].next;
		*px = node[q].info;
		node[p].next = node[q].next;
		freenode(q);
		return;
	}
	void insertAfter(int data, int value) {
		int t = start;
		while (node[t].info != data) {
			if (t == -1)
				throw "No such node found.";
			t = node[t].next;
		}
		insafter(t, value);
	}
	void deleteAfter(int data, int* ret) {
		int t = start;
		while (node[t].info != data) {
			if (t == -1)
				throw "No such node found.";
			t = node[t].next;
		}
		delafter(t, ret);
	}
};
int mainl31() {
	Listl31 l(2);
	l.insertAfter(2, 3);
	int p = 0;
	l.deleteAfter(2, &p);
	std::cout << p;
	return GGMU;
}
