// 1. Perform push and pop operations in stack

#include <iostream> 
#define SIZE 100

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
};
int mainl11()
{
	Stack<int> x;
	int a;
	try {
		for (int i = 0; i < SIZE; i++)
		{
			std::cout << "Enter item 0 to exit) ::";
			std::cin >> a;
			while(a) x.push(a);
		}
		std::cout << "Popping out elements...";
		while (x.giveTop())
		{
			std::cout << ' ' << x.pop();
		}
		std::cout << '\n';
	}
	catch(const char* err){
		std::cout << err;
	}
	return 0;
}