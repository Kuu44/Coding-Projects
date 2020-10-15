/*
WRITE AN ALGORITHM AND PROGRAM FOR FOLLOWING
CASES IN SINGLY LINEAR LINKED LIST:
1. INSERTION OPERATIONS
a. INSERT NODE AT BEGINNING OF THE LIST
b. INSERT NODE AT END OF THE LIST
c. INSERT NODE AFTER SPECIFIC NODE
d. INSERT NODE BEFORE SPECIFIC NODE
2. DELETION OPERATIONS
a. DELETE NODE FROM BEGINNING OF THE LIST
b. DELETE NODE FROM END OF THE LIST
c. DELETE NODE AFTER SPECIFIC NODE
*/
#include<iostream>

#define GGMU 0
#define SIZE 100

template <class T>
struct Nodel31
{
    T data;
    Nodel31* next;
};
template <class T>
class LinkedList1
{
private:
    Nodel31<T>* start;
public:
    LinkedList1() { 
        start = NULL; 
    }
    void insAtStart(T item)
    {
        Nodel31<T>* temp = start;
        start = new Nodel31<T>();
        start->data = item;
        start->next = temp;
    }
    void delAtStart()
    {
        Nodel31<T>* temp = start;
        start = start->next;
        delete temp;
    }
    void insAtEnd(T item)
    {
        if (start->next == NULL)
        {
            start = new Nodel31<T>();
            start->data = item;
            start->next = NULL;
        }
        else
        {
            Nodel31<T>* preptr = start;
            while (preptr->next != NULL) preptr = preptr->next;
            Nodel31<T>* ptr=new Nodel31<T>();
            preptr->next = ptr;
            ptr->data = item;
            ptr->next = NULL;
        }
    }
    void delAtEnd()
    {
        if (start->next == NULL)
            delAtStart();
        else
        {
            Nodel31<T>* ptr, * preptr;
            ptr = start;
            preptr = new Nodel31<T>();
            while (ptr->next != NULL)
            {
                preptr = ptr;
                ptr = ptr->next;
            }
            preptr->next = NULL;
            delete ptr;
        }
    }
    void insertAfter(T item, T after)
    {
        if (!start)
        {
            std::cout << "List empty" << std::endl;
            return;
        }
        Nodel31<T>* ptr = start;
        while (ptr->data != after)
        {
            ptr = ptr->next;
            if (!ptr) {
                std::cout << "No such element" << std::endl;
                return;
            }
        }
        Nodel31<T>* temp = ptr->next;
        ptr->next = new Nodel31<T>();
        ptr->next->data = item;
        ptr->next->next = temp;
    }
    void deleteAfter(T after)
    {
        if (!start)
        {
            std::cout << "List empty" << std::endl;
            return;
        }
        Nodel31<T>* ptr = start;
        while (ptr->data != after)
        {
            ptr = ptr->next;
            if (!ptr) {
                std::cout << "No such element" << std::endl;
                return;
            }
        }
        Nodel31<T>* p=new Nodel31<T>();
        ptr->next = ptr->next->next;
        delete p;
    }
    void insertBefore(T item, T before)
    {
        if (!start)
        {
            std::cout << "List empty" << std::endl;
            return;
        }
        Nodel31<T>* ptr = start, * preptr = start;
        while (ptr->data != before)
        {
            preptr = ptr;
            ptr = ptr->next;
            if (!ptr) {
                std::cout << "No such element" << std::endl;
                return;
            }
        }
        Nodel31<T>* temp = new Nodel31<T>;
        temp->data = item;
        temp->next = ptr;
        preptr->next = temp;
    }
    void print()
    {
        Nodel31<T>* p = start;
        while (p != NULL)
        {
            std::cout << p->data;
            p = p->next;
        }
        std::cout << std::endl;
    }
};
int mainl33(){
    LinkedList1<int> list;

    list.insAtStart(1); list.insAtStart(0);
    list.insAtEnd(4); list.insertAfter(3, 1);
    list.insertBefore(2, 3);
    list.print();

    list.delAtStart();
    list.delAtEnd();
    list.deleteAfter(2);
    list.print();

    return GGMU;
}