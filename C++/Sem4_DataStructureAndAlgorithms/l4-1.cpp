//IMPLEMENT STACK AS LINKED LIST

#include <iostream>
#define GGMU 20
using namespace std;
constexpr auto stacksize = 5;

template <class T>
struct Nodel41 {
public:
    T data;
    Nodel41<T>* next;
    Nodel41(T dataIn = 0, Nodel41<T>* nextIn = NULL) {
        data = dataIn;
        next = nextIn;
    }
};

template <class T>
class LinkedListl41 {
private:
    Nodel41<T>* head;
public:
    LinkedListl41(Nodel41<T>* n = NULL) {
        head = n;
    }
    T top() {
        return head->data;
    }
    Nodel41<T>* giveHead() {
        return head;
    }
    void append(Nodel41<T>* n) {
        if (head == NULL) head = n;
        else {
            Nodel41<T>* ptr = head;
            while (ptr->next != NULL) ptr = ptr->next;
            ptr->next = n;
        }
    }
    void prepend(Nodel41<T>* n) {
        Nodel41<T>* temp = head;
        head = new Nodel41<T>;
        head = n;
        head->next = temp;
    }
    void frontDelete() {
        if (head == NULL)throw "List is Empty: Erorr Func: FrontDelete";
        Nodel41<T>* temp = head;
        head = head->next;
        delete temp;
    }
    void endDelete() {
        Nodel41<T>* ptr = head;
        Nodel41<T>* temp = NULL;
        while (ptr->next->next != NULL) {
            temp = ptr;
            ptr = ptr->next;
        }
        ptr->next = NULL;
        delete temp;
    }
    void show() {
        Nodel41<T>* ptr = head;
        while (ptr != NULL) {
            cout << ptr->data;
            ptr = ptr->next;
        }
        cout << endl;
    }
    /*Nodel41<T>* nodeExists(T d) {
        Nodel41<T>* temp = NULL;
        Nodel41<T>* ptr = head;
        Nodel41<T>* preptr = NULL;
        while (ptr != NULL) {
            if (ptr->data == d) temp = ptr;            
            ptr = ptr->next;
        }
        return temp;
    }
    Nodel41<T>* nodeBefore(T d) {
        Nodel41<T>* ptr = head;
        Nodel41<T>* preptr = NULL;
        Nodel41<T>* temp = NULL;
        while (ptr->data != d) {
            temp = preptr;
            preptr = ptr;
            ptr = ptr->next;
        }
        return preptr;
    }
    void insertNodeAfter(T data, Nodel41<T>* n) {
        Nodel41<T>* ptr = nodeExists(data);
        if (ptr->next == NULL) cout << "Nodel41 with" << data << " value is non existent" << endl;
        else {
            n->next = ptr->next;
            ptr->next = n;
        }
    }
    void insertNodeBefore(T data, Nodel41<T>* n) {
        Nodel41<T>* ptr = nodeBefore(data);
        if (ptr == NULL) cout << "Nodel41 with" << data << " value is non existent" << endl;
        else {
            n->next = ptr->next;
            ptr->next = n;
        }
    }
    void deleteAfter(T data) {
        Nodel41<T>* ptr = nodeExists(data);
        if (ptr == NULL) {
            cout << "Nodel41 with" << data << " value is non existent" << endl;
            exit(1);
        }
        Nodel41<T>* temp = ptr->next;
        ptr->next = ptr->next->next;
        delete temp;
    }*/    
};
template <class T>
class Stackl41 {
    LinkedListl41<T> list;
    int count;
public:
    Stackl41() {
        count = 0;
    }
    void push(T data) {
        Nodel41<T>* n = new Nodel41<T>(data);
        if (count == 0) {
            list.append(n);
            count++;
        }
        else if (count < stacksize) {
            list.prepend(n);
            count++;
        }
        else throw "Stack Overflow";
    }
    T pop() {
        T temp = list.top();
        list.frontDelete();
        count--;
        return temp;
    }
    int getCount() {
        return count;
    }
    void show() {
        list.show();
    }
    T top() {
        return list.top();
    }
};
int mainl41 () {
    Stackl41<int> s1;
    try
    {
        for(int i=1;i<5;i++) s1.push(i);
        cout << "Total number of elements in the stack are: " << s1.getCount() << endl;
        s1.show();
        s1.pop();
        cout << "Total number of elements in the stack are: " << s1.getCount() << endl;
        s1.show();
        cout << "Top is: " << s1.top();
    }
    catch (const char* err)
    {
        cout << err;
    }
    return GGMU;
}