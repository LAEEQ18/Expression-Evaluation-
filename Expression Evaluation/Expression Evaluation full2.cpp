// Stack by using tamplate.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<conio.h>
#include<stdio.h>
#include<iostream>
#define MAXSTACKSIZE 50
using namespace std;
template <class T>
class Stack
{
public:
	Stack()
	{
		top = -1;
		nodes = new T[MAXSTACKSIZE];
	}
	int empty()
	{
		if (top < 0)
			return 1;
		return 0;
	}
	T pop(void)
	{
		T x = NULL;
		if (!empty())
		{
			x = nodes[top--];
			return x;
		}
		cout << "Stack is underflow...";
		return x;
	}
	int push(T x)
	{
		if (top < MAXSTACKSIZE)
		{
			nodes[++top] = x;
			return 1;
		}
		cout << "Stack overflow in push...";
		return 0;
	}
	T peek()
	{
		T x = NULL;
		if (!empty())
		{
			x = nodes[top];
			return x;
		}
		cout << "Stack underflow...";
		return x;
	}
	~Stack()
	{
		delete nodes;
	}
private:
	int top;
	T *nodes;
};

#include "stdafx.h"
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<iostream>
class ExpressionEvaluation
{
public:



	//here user input prifix expression
	void InputPrifix()
	{
		cout << "Enter Pri fix expression: ";
		fgets(infixexp, 50, stdin);
	}




	//input postfix
	void InputPostFix()
	{

		cout << "Enter Post Fix expression: ";
		//cin >> postfixexp;
		fgets(postfixexp, 50, stdin); // get a whole input line
		/*
		for (int i = 0; i < 50; i++)
		{
		char c = postfixexp[i];
		if (!(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || (c>'0' && c < '9')||(c==' ')||(c=='.')))
		{
		postfixexp[++i] = '$';
		break;
		}
		}*/
	}


	

	int isdigitin(int i)
	{
		char x = infixexp[i];
		if (x >= '0' && x <= '9')
			return 1;
		else
			return 0;
	}

	int getNext(int n)
	{
		while (postfixexp[n] == ' ') n++;
		return n;
	}
	int getNextin(int n)
	{
		while (infixexp[n] == ' ') n++;
		return n;
	}

	int pre(char c)
	{
		switch (c)
		{
		case'^': return 0;
		case'*':return 2;
		case'/':return 1;
		case'+':return 3;
		case'-':return 3;

		}

	}

	int prcd(char c1, char c2)
	{
		if (c1 == '(' || c2 == '(')
			return 0;
		if (c1 == '^' && c2 == '^')
			return 0;
		int a = pre(c1);
		int b = pre(c2);
		if (a <= b)
			return 1;
		else
			return 0;
	}

	void ConvertInfixToPostfix()
	{
		int i = 0, j = 0;
		while (1)
		{
			i = getNextin(i);
			if (infixexp[i] == '\n')
				break;
			else if (isdigitin(i) || (infixexp[i] == '-' && isdigitin(i + 1)) || infixexp[i] == '.')
			{
				requiredexp[j] = infixexp[i];
				j++;
				i++;
			}
			else
			{
				if (infixexp[i] == ')')
				{
					while (s2.peek() != '(')
					{
						char c = s2.pop();
						requiredexp[j] = ' ';
						j++;
						requiredexp[j] = c;
						j++;
					}
					s2.pop();
					i++;
				}
				if (infixexp[i] == '\n')
					break;
				while (!s2.empty() && prcd(s2.peek(), infixexp[i]))
				{
					char c = s2.pop();
					requiredexp[j] = ' ';
					j++;
					requiredexp[j] = c;
					j++;
				}
				s2.push(infixexp[i]);
				i++;
				requiredexp[j] = ' ';
				j++;

			}
		}
		while (!s2.empty())
		{
			char c = s2.pop();
			requiredexp[j] = ' ';
			j++;
			requiredexp[j] = c;
			j++;
		}
		cout << requiredexp;
	}



	int pushFullOperand(int n)
	{
		int neg = 0;
		float operandbeforepoint = 0, operandafterpoint = 0, fulloperand = 0;
		if (postfixexp[n] == '-')
		{
			neg = 1;
			n++;
		}
		int count = 0;
		while ((postfixexp[n] >= '0' && postfixexp[n] <= '9') || (postfixexp[n] == '.'))
		{
			if (postfixexp[n] == '.' || count > 0)
			{
				if (count > 0)
				{
					operandafterpoint *= 10;
					operandafterpoint += postfixexp[n] - '0';
					n++;
					count++;
				}
				else
				{
					count++;
					n++;
				}
			}
			else
			{
				operandbeforepoint *= 10;
				operandbeforepoint += postfixexp[n] - '0';
				n++;
			}
		}

		float tmp = 0;
		for (; count > 0; count--)
		{
			tmp = operandafterpoint / 10;
		}
		fulloperand = operandbeforepoint + tmp;
		if (neg == 1)
			fulloperand = -fulloperand;
		s1.push(fulloperand);
		n++;
		return n;
	}


	int isdigit(int i)
	{
		char x = postfixexp[i];
		if (x >= '0' && x <= '9')
			return 1;
		else
			return 0;
	}

	//evaluate postfix
	void EvaluatePostfix()
	{

		int i = 0;

		while (1)
		{
			i = getNext(i);
			if (postfixexp[i] == '\n')
				break;
			else if (isdigit(i) || (postfixexp[i]=='-'&&isdigit(i+1)))
			{
				i = pushFullOperand(i);
			}
			else
			{
				float v1, v2;
				float res;
				v2 = s1.pop();
				v1 = s1.pop();
				switch (postfixexp[i])
				{
				case '+':
				{
							res = v1 + v2;
							break;
				}
				case '-':
				{
							res = v1 - v2;
							break;
				}
				case '*':
				{
							res = v1 * v2;
							break;
				}
				case '/':
				{
							res = v1 / v2;
							break;
				}
				case '^':
				{
							res = pow(v1, v2);
							break;
				}
				}
				s1.push(res);
				i++;
			}

		}
		cout << "Result is: " << s1.pop() << "\n\n";
	}



private:
	char postfixexp[50], infixexp[50], requiredexp[50];
	Stack<float> s1;
	Stack<char> s2;
};
#include "stdafx.h"
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<iostream>
using namespace std;
void main()
{
	ExpressionEvaluation exp;

	exp.InputPrifix();
	exp.ConvertInfixToPostfix();
	cout << endl<<endl;
	exp.InputPostFix();
	exp.EvaluatePostfix();



}