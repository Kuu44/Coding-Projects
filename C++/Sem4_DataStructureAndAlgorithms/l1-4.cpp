//4. Check the paired parenthesis in mathematical expression Due:

#include <iostream>
#define SIZE 100
#define GGMU 0

using namespace std;

template<class T>
class Stack {
private:
    T stack[SIZE];
    int top;
public:
    Stack() {
        top = -1;
    }
    void push(T item)
    {
        if (top >= SIZE - 1) throw("\nStack Overflow");
        else stack[++top] = item;
    }
    T pop()
    {
        if (top < 0) throw("Stack UnderFlow");
        else return stack[top--];
    }
    bool isEmpty() {
        return (top == -1);
    }
    bool isFull() {
        return (top >= (SIZE - 1));
    }
    int giveTop() {
        return top;
    }
    T getTop() {
        return stack[top];
    }
};
char pairOf(char c) {
    return (c == ')') ? '(' : (c == '}') ? '{' : '[';
}
string check(string exp) {
    Stack <char> s;
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') s.push(exp[i]);
        else if ((exp[i] == ')' || exp[i] == '}' || exp[i] == ']') && !s.isEmpty()) 
            if (s.getTop() == pairOf(exp[i])) s.pop();        
    }
    if (s.isEmpty()) return "balanced parenthesis\n";
    else return "unpaired parenthesis\n";
}
int mainl14() {
    try {
        string p;
        cout << "Enter an expression: ";
        cin >> p;
        cout << "The expression has " << check(p);
    }
    catch (const char* err) {
        cout << err;
    }
    return GGMU;
}



