//3. Evaluate the postfix expression
//BB

#include <iostream>
#define SIZE 100

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
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}
int evaluate(string c) {
    int  operandA, operandB;
    Stack<int> s;
    for (int i = 0; i < c.length(); i++) {
        if (c[i] >= '0' && c[i] <= '9') s.push(c[i] - '0');
        else if (isOperator(c[i])) {
            operandA = s.pop();
            operandB = s.pop();
            switch (c[i]) {
            case '+':                
                s.push(operandA + operandB);
                break;
            case '-':
                s.push(operandB - operandA);
                break;
            case '*':
                s.push(operandB * operandA);
                break;
            case '/':
                s.push(operandB / operandA);
                break;
            default:
                break;
            }
        }
    }
    int res = s.pop();
    return res;
}
int mainl13() {
    try {
        string exp;
        cout << "Enter your valid postfix expression with integers: \n";
        cin >> exp;
        cout << "The evaluated expression is " << evaluate(exp);
    }
    catch (const char* err) {
        std::cout << err;
    }
    return 0;
}


