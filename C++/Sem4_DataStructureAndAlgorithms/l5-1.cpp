#include <iostream>
#define GGMU 20

using namespace std;

class Node {
public:
	int data;
	Node* next;
	Node* prev;
	Node(int d = 0) {
		data = d;
		next = NULL;
		prev = NULL;
	}
};

class DLinkedList {
private:
	Node* head;
public:
	DLinkedList(Node* in = NULL) {
		head = in;
	}
	Node* giveHead() {
		return head;
	}
	Node* nodeExists(Node* n) {
		Node* temp = NULL;
		Node* ptr = head;
		if (head == NULL) throw "List is empty";
		while (ptr != NULL) {
			if (n->data == ptr->data) temp = ptr;
			ptr = ptr->next;
		}
		return temp;
	}
	Node* nodeExists(int data) {
		Node* temp = NULL;
		Node* ptr = head;
		if (head == NULL) throw "List is empty ";
		while (ptr != NULL) {
			if (data == ptr->data) temp = ptr;
			ptr = ptr->next;
		}
		return temp;
	}
	void prependNode(Node* n) {
		if (head == NULL) head = n;
		else
		{
			head->prev = n;
			n->next = head;
			head = n;
		}
	}
	void appendNode(Node* n) {
		if (head == NULL) head = n;
		else
		{
			Node* ptr = head;
			while (ptr != NULL) ptr = ptr->next;
			n->prev = ptr;
			ptr->next = n;
		}
	}
	void insertAfter(int data, Node* n) {
		Node* ptr = nodeExists(data);
		if (ptr->next == NULL) {
			n->prev = ptr;
			ptr->next = n;
		}
		else {
			n->next = ptr->next;
			ptr->next->prev = n;
			n->prev = ptr;
			ptr->next = n;
		}
	}
	void insertBefore(int data, Node* n) {
		Node* ptr = nodeExists(data);
		if (ptr->prev == NULL) {
			n->next = ptr;
			ptr->prev = n;
			head = n;
		}
		else {
			n->prev = ptr->next;
			ptr->prev->next = n;
			n->next = ptr;
			ptr->prev = n;
		}
	}
	void deleteFirst() {
		if (head == NULL) throw "List is Empty";
		head = head->next;
		head->prev = NULL;
	}
	void deleteEnd() {
		Node* ptr = head;
		while (ptr->next != NULL) ptr = ptr->next;
		ptr = ptr->prev;
		ptr->next = NULL;
	}
	void deleteAfter(int data) {
		Node* ptr = nodeExists(data);
		Node* prevnode = ptr->prev;
		Node* nextnode = ptr->next;
		if (ptr->next == NULL) throw "No element exists after that  node";
		nextnode->next->prev = ptr;
		ptr->next = nextnode->next;
	}
	void deleteBefore(int data) {
		Node* ptr = nodeExists(data);
		Node* prevnode = ptr->prev;
		Node* temp = ptr->prev;
		Node* nextnode = ptr->next;
		prevnode->prev->next = ptr;
		ptr->prev = prevnode->prev;
	}
	void show() {
		Node* ptr = head;
		cout << "The data are: " << endl;
		while (ptr != NULL) {
			cout << ptr->data << endl;
			ptr = ptr->next;
		}
	}
};

int mainl51() {
	DLinkedList d;
	Node n1(2), n2(3), n3(4), n4(5), n5(6), n6(7);
	d.appendNode(&n1);
	d.prependNode(&n2);
	d.show();
	d.insertAfter(2, &n3);
	d.show();
	d.insertAfter(2, &n4);
	d.show();
	d.insertBefore(3, &n5);
	d.show();
	d.insertBefore(4, &n6);
	d.show();
	d.deleteBefore(2);
	d.show();
	d.deleteAfter(2);
	d.show();
	d.deleteFirst();
	d.show();
	d.deleteEnd();
	d.show();
	return GGMU;
}