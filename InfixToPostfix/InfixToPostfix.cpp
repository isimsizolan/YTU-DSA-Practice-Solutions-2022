#include <iostream>
#include <stdio.h>

/*Stack*/
#define MAX_STACK_SIZE 100

struct Stack {
	int s[MAX_STACK_SIZE];
	int Top;
} _stack;
bool IsEmpty()
{
	return _stack.Top == -1 ? true : false;
}
bool IsFull()
{
	return _stack.Top == MAX_STACK_SIZE ? true : false;
}
int Pop()
{
	if (!IsEmpty()) {
		return _stack.s[_stack.Top--];
	}
}
void Push(int data)
{
	if (!IsFull()) {
		_stack.s[++_stack.Top] = data;
	}
}
int Top()
{
	return _stack.s[_stack.Top];
}
int Precedence(char c)
{
	switch (c)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	default:
		return -1;
	}
}
bool IsOperand(char c)
{
	return (c <= 'z' && c >= 'a');
}
void infixToPostfix(char* exp)
{
	for (int i = 0; i < strlen(exp); i++)
	{
		if (IsOperand(exp[i]))
			printf("%c", exp[i]);
		else
		{
			while (!IsEmpty() && Precedence(exp[i]) <= Precedence(Top()))
				printf("%c", Pop());
			Push(exp[i]);
		}
	}
	while (!IsEmpty())
	{
		printf("%c", Pop());	
	}
}
int main()
{
	char exp[] = "a+b*(c+d)";
	infixToPostfix(exp);
	return 0;
}