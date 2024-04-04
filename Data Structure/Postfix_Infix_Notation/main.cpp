#include <iostream>
#include <string>
#include <math.h>
/*
Mahmood Nseer(Computer Science)
11926849
Have a Nice Day
*/
using namespace std;
template <class T>
class List;
template <class T>
// Node Data
class Node
{
private:
	T data;
	Node<T> *Next;
	friend List<T>;

public:
	Node()
	{
		Next = NULL;
		data = T{}; // Like null
	}
};
template <class T>
// Singly Linked List
class List
{
private:
	Node<T> *Head;

public:
	List();
	int Size;
	void AddFront(T);
	bool empty()
	{
		return Head;
	}
	~List();
	T Front();
	void RemoveFront();
};
template <class T>
List<T>::List()
{
	Head = NULL;
	Size = 0;
}
template <class T>
List<T>::~List()
{
	while (Head)
	{
		this->RemoveFront();
	}
}
template <class T>
void List<T>::RemoveFront()
{
	if (Head)
	{
		Node<T> *p = Head;
		Head = Head->Next;
		delete p;
		Size--;
	}
}
template <class T>
void List<T>::AddFront(T val)
{
	Node<T> *NewNode = new Node<T>;
	NewNode->data = val;
	NewNode->Next = NULL;
	NewNode->Next = Head;
	Head = NewNode;
	Size++;
}
template <class T>
T List<T>::Front()
{
	if (Head)
	{
		return Head->data;
	}
	return T{}; // Like null
}
bool thisNumber(char WhatThis);
// Stack
template <class T>
class LinStack
{
public:
	LinStack();
	LinStack(T);
	~LinStack();
	void push(T val);
	bool empty()
	{
		return Stack.empty();
	}
	void pop();
	T top();

private:
	List<T> Stack;
};
template <class T>
void LinStack<T>::push(T val)
{
	this->Stack.AddFront(val);
}
template <class T>
void LinStack<T>::pop()
{
	this->Stack.RemoveFront();
}
template <class T>
T LinStack<T>::top()
{
	return this->Stack.Front();
}
template <class T>
LinStack<T>::LinStack()
{
	// ZZz
}
template <class T>
LinStack<T>::LinStack(T Val)
{
	this->Stack(Val);
}
template <class T>
LinStack<T>::~LinStack()
{
	this->Stack.~List();
}
// tool
bool thisNumber(char WhatThis)
{
	if ((WhatThis < '0' || WhatThis > '9'))
	{
		return false;
	}
	return true;
}
bool thisCharacter(char WhatThis)
{
	if ((WhatThis < 'a' || WhatThis > 'z') && (WhatThis < 'A' || WhatThis > 'Z')) // out range
	{
		return false;
	}
	return true;
}
// end tool
template <typename T>
T InputFrom2(int From, int to)
{
	T InputUser;
	bool Brack = false;
	do
	{
		if (Brack)
		{
			cout << "\nWrong value,Try again:";
		}
		cin >> InputUser;
		Brack = true;
	} while (!(From < InputUser && InputUser < to));
	return InputUser;
}
// logic
char ReturnLogic(char ValI, char ValII, int &_N) // fix char to string ,
{
	if (ValI == '=' && ValII == '=')
	{
		_N++;
		return '~';
	}
	else if (ValI == '>' && ValII == '=')
	{
		_N++;
		return '@';
	}
	else if (ValI == '<' && ValII == '=')
	{
		_N++;
		return '#';
	}
	else if (ValI == '!' && ValII == '=')
	{
		_N++;
		return '$';
	}
	else if (ValI == '|' && ValII == '|')
	{
		_N++;
		return '|';
	}
	else if (ValI == '&' && ValII == '&')
	{
		_N++;
		return '&';
	}
	else if (ValI == '>')
	{
		return '>';
	}
	else if (ValI == '<')
	{
		return '<';
	}
	else
	{
		return ValI;
	}
}
string LogicalConverter(char Practical) //~ == @ >= # <= $!= ||| &&&,char to string
{
	if (Practical == '@')
	{
		return ">=";
	}
	else if (Practical == '#')
	{
		return "<=";
	}
	else if (Practical == '~')
	{
		return "==";
	}
	else if (Practical == '$')
	{
		return "!=";
	}
	else if (Practical == '&')
	{
		return "&&";
	}
	else if (Practical == '|')
	{
		return "||";
	}
	else if (Practical == '>')
	{
		return ">";
	}
	else if (Practical == '<')
	{
		return "<";
	}
	else
	{
		return "<Something is missing>";
	}
}
bool Logic(char Practical)
{
	if (Practical == '=' || Practical == '>' || Practical == '<' || Practical == '|' || Practical == '&' || Practical == '!' || Practical == '$' || Practical == '@' || Practical == '#' || Practical == '~')
	{
		return true;
	}
	return false;
}
// end logic
bool condition(char Practical)
{
	if (Practical == '^' || Practical == ')' || Practical == '(' || Practical == '*' || Practical == '/' || Practical == '%' || Practical == '+' || Practical == '-')
	{
		return true;
	}
	return false;
}
// Priorities
int Rank(char Practical)
{
	if (Practical == '^')
	{
		return 1;
	}
	else if (Practical == '/' || Practical == '*' || Practical == '%')
	{
		return 2;
	}
	else if (Practical == '+' || Practical == '-')
	{
		return 3;
	}
	else if (Practical == '<' || Practical == '>' || Practical == '@' || Practical == '#')
	{
		return 4;
	}
	else if (Practical == '=' || Practical == '~' || Practical == '!' || Practical == '$') //$'!=',~'=='
	{
		return 5;
	}
	else if (Practical == '&')
	{
		return 6;
	}
	else if (Practical == '|')
	{
		return 7;
	}
	else if (Practical == '(')
	{
		return 8;
	}
	return 0;
	// Not return mater
}
float PostfixResult(string Infix)
{
	if (Infix.size())
	{
		LinStack<float> StackResult;
		string Postfix, Number;
		float Result = -999, Val;
		int LenInfx = Infix.length();
		for (int _N = 0; _N < LenInfx; _N++)
		{
			if (Infix[_N] != ' ')
			{
				if (thisNumber(Infix[_N]))
				{

					while (thisNumber(Infix[_N]) || Infix[_N] == '.')
					{
						if (Infix[_N] == '.' && thisNumber(Infix[_N - 1]))
						{
							Number += Infix[_N];
						}
						else
						{
							Number += Infix[_N];
						}
						_N++;
					}
					StackResult.push(stof(Number));
					Number.clear();
					_N--;
				}
				else if (thisCharacter(Infix[_N]))
				{
					Postfix += Infix[_N];
					return 0;
				}
				else if (condition(Infix[_N]))
				{
					Result = 0.0f;
					Val = StackResult.top();
					StackResult.pop();
					if (Infix[_N] == '+')
					{
						Result += StackResult.top();
						Result += Val;
					}
					else if (Infix[_N] == '-')
					{
						Result = StackResult.top();
						Result -= Val;
					}
					else if (Infix[_N] == '/')
					{
						Result = StackResult.top();
						Result = Result / Val;
					}
					else if (Infix[_N] == '*')
					{
						Result = StackResult.top();
						Result *= Val;
					} //
					else if (Infix[_N] == '%')
					{
						Result = StackResult.top();
						Result = fmod(Result, Val);
					}
					else if (Infix[_N] == '^')
					{
						Result = pow(StackResult.top(), Val);
					}
					StackResult.pop();
					StackResult.push(Result);
				}
				else if (Logic(Infix[_N]))
				{
					if (Infix[_N] != '>' && !Logic(Infix[_N + 1]) && Infix[_N] != '<')
						StackResult.pop();
					Val = StackResult.top();
					StackResult.pop();
					Result = StackResult.top();
					StackResult.pop();
					if (Infix[_N] == '=' && Infix[_N + 1] == '=')
					{
						Result = Result == Val;
						_N++;
					}
					else if (Infix[_N] == '>' && Infix[_N + 1] == '=')
					{
						Result = Result >= Val;
						_N++;
					}
					else if (Infix[_N] == '<' && Infix[_N + 1] == '=')
					{
						Result = Result <= Val;
						_N++;
					}
					else if (Infix[_N] == '!' && Infix[_N + 1] == '=')
					{
						Result = Result != Val;
						_N++;
					}
					else if (Infix[_N] == '|' && Infix[_N + 1] == '|')
					{
						Result = Result || Val;
						_N++;
					}
					else if (Infix[_N] == '&' && Infix[_N + 1] == '&')
					{
						Result = Result && Val;
						_N++;
					}
					else if (Infix[_N] == '>')
					{
						Result = Result > Val;
					}
					else if (Infix[_N] == '<')
					{
						Result = Result < Val;
					}
					else if (Infix[_N] == '!')
					{
						Result = Result != Val;
					}
					StackResult.push(Result);
				}
			}
		}
		return StackResult.top();
	}
	return 0;
}
string InfixTOPostfix(string Infix)
{
	string Postfix = "Undefined";
	if (Infix.size())
	{
		Postfix.clear();
		LinStack<char> Stack;
		while (Infix.back() == ' ') // clear Infix
		{
			Infix.pop_back();
		}
		int LenInfx = Infix.length();
		for (int _N = 0; _N < LenInfx; _N++)
		{
			if (Infix[_N] != ' ')
			{
				if (thisNumber(Infix[_N])) // 0-9.9~
				{
					while (thisNumber(Infix[_N]) || Infix[_N] == '.')
					{

						if (Infix[_N] == '.' && thisNumber(Infix[_N - 1]))
						{
							Postfix += Infix[_N];
						}
						else
						{
							Postfix += Infix[_N];
						}
						_N++;
					}
					Postfix += " ";
					_N--;
					bool NumberANDBrackets = true;
					bool Brackets = false;
					// like 5(10)  5*(10) but cant be like that (5)3
					for (int _NI = _N + 1; _NI < LenInfx && NumberANDBrackets && !(Brackets && NumberANDBrackets); _NI++)
					{
						if (Infix[_NI] != ' ')
						{
							if (Infix[_NI] != '(')
							{
								NumberANDBrackets = false;
							}
							else
							{
								Brackets = true;
							}
						}
					}
					if (NumberANDBrackets && Brackets)
					{
						if (Rank('*') >= Rank(Stack.top()))
						{
							while (Rank('*') >= Rank(Stack.top()) && Stack.empty())
							{
								if (Logic(Stack.top()))
								{
									Postfix += LogicalConverter(Stack.top()); // like ~,&,| to != ,&&,||
								}
								else
								{
									Postfix += Stack.top();
									Postfix += " ";
								}
								Stack.pop();
							}
							Stack.push('*');
						}
						//
					}
					// end ()()
				}
				else if (condition(Infix[_N]) || Logic(Infix[_N])) //!=,==,=>,>,<,<=,&&,||,-,+,/,*
				{
					if (!Stack.empty())
					{
						if (Logic(Infix[_N]))
						{
							Stack.push(ReturnLogic(Infix[_N], Infix[_N + 1], _N));
						}
						else
						{
							Stack.push(Infix[_N]);
						}
					}
					else if (Infix[_N] == ')')
					{

						while (Stack.empty() && Stack.top() != '(')
						{
							if (Logic(Stack.top()))
							{
								Postfix += LogicalConverter(Stack.top());
							}
							else
							{
								Postfix += Stack.top();
								Postfix += " ";
							}
							Stack.pop();
						}
						Stack.pop(); //(
						bool NumberANDBrackets = true;
						bool Brackets = false;
						if (Infix[_N] == ')')
						{
							for (int _NI = _N + 1; _NI < LenInfx && NumberANDBrackets && !(Brackets && NumberANDBrackets); _NI++)
							{
								if (Infix[_NI] != ' ')
								{
									if (Infix[_NI] != '(')
									{
										NumberANDBrackets = false;
									}
									else
									{
										Brackets = true;
									}
								}
							}
						}
						if (NumberANDBrackets && Brackets)
						{
							Stack.push('*');
						}
					}
					else if (Rank(Infix[_N]) < Rank(Stack.top()) || Infix[_N] == '(')
					{
						if (Logic(Infix[_N]))
						{
							Stack.push(ReturnLogic(Infix[_N], Infix[_N + 1], _N));
						}
						else
						{
							Stack.push(Infix[_N]);
						}
					}
					else if (Rank(Infix[_N]) >= Rank(Stack.top()))
					{
						while (Rank(Infix[_N]) >= Rank(Stack.top()) && Stack.empty())
						{
							if (Infix[_N] != ' ')
							{
								if (Logic(Stack.top()))
								{
									Postfix += LogicalConverter(Stack.top()); // like ~,&,| to != ,&&,||
								}
								else
								{
									Postfix += Stack.top();
									Postfix += " ";
								}
								Stack.pop();
							}
						}
						if (Logic(Infix[_N]))
						{
							Stack.push(ReturnLogic(Infix[_N], Infix[_N + 1], _N));
						}
						else
						{
							Stack.push(Infix[_N]);
						}
					}
				}
				else if (thisCharacter(Infix[_N])) // A-Z,a-z
				{
					Postfix += Infix[_N];
					Postfix += " ";
				}
				if (_N + 1 == LenInfx)
				{
					while (Stack.empty())
					{
						if (Logic(Stack.top()))
						{
							Postfix += LogicalConverter(Stack.top());
						}
						else
						{
							Postfix += Stack.top();
						}
						Postfix += " ";
						Stack.pop();
					}
					while (Postfix.back() == ' ') // clear Postfix
					{
						Postfix.pop_back();
					}
				}
			}
		}
	}
	return Postfix;
}
string PostfixToInfix(string Infix)
{
	if (Infix.size())
	{
		LinStack<string> Stack;
		bool Two = false;
		string CharFix, Equation, Number, TempEquation;
		int LenInfx = Infix.length();
		for (int _N = 0; _N < LenInfx; _N++)
		{
			if (Infix[_N] != ' ')
			{
				if (thisNumber(Infix[_N]))
				{
					while (thisNumber(Infix[_N]) || Infix[_N] == '.')
					{
						if (Infix[_N] == '.' && thisNumber(Infix[_N - 1]))
						{
							Number += Infix[_N];
						}
						else
						{
							Number += Infix[_N];
						}
						_N++;
					}
					Stack.push(Number);
					Number.clear();
					_N--;
				}
				else if (thisCharacter(Infix[_N]))
				{
					CharFix = Infix[_N];
					Stack.push(CharFix);
				}
				else if (condition(Infix[_N]) || Logic(Infix[_N]))
				{
					Equation += '(';
					TempEquation = Stack.top();
					Stack.pop();
					Equation += Stack.top();
					Stack.pop();
					if (Logic(Infix[_N]))
					{
						if (Infix[_N] == '=' && Infix[_N + 1] == '=')
						{
							Equation += "==";
							_N++;
						}
						else if (Infix[_N] == '>' && Infix[_N + 1] == '=')
						{
							Equation += ">=";
							_N++;
						}
						else if (Infix[_N] == '<' && Infix[_N + 1] == '=')
						{
							Equation += "<=";

							_N++;
						}
						else if (Infix[_N] == '!' && Infix[_N + 1] == '=')
						{
							Equation += "!=";
							_N++;
						}
						else if (Infix[_N] == '|' && Infix[_N + 1] == '|')
						{
							Equation += "||";
							_N++;
						}
						else if (Infix[_N] == '&' && Infix[_N + 1] == '&')
						{
							Equation += "&&";
							_N++;
						}
						else if (Infix[_N] == '>')
						{
							Equation += ">";
						}
						else if (Infix[_N] == '<')
						{
							Equation += "<";
						}
					}
					else
					{
						Equation += Infix[_N];
					}
					Equation += TempEquation;
					Equation += ')';
					Stack.push(Equation);
					Equation.clear();
				}
			}
		}
		return Stack.top();
	}
	return "Undefined";
}

void Display()
{
	cout << "\n1 - Convert infix to postfixand give the result of postfix evaluation"
		 << "\n2 - Convert postfix to infix"
		 << "\n3 - Exit\n";
}
bool YorN()
{
	char YN;

	cout << "\nDo you want to use the previous equation? Y/N:";
	cin >> YN;
	while (true)
	{
		if (YN == 'Y' || YN == 'y')
		{
			return true;
		}
		else if (YN == 'n' || YN == 'N')
		{
			return false;
		}
		else
		{
			cout << "\nRetry The value is incorrect!:Y/N:";
			cin >> YN;
		}
	}
}
int main()
{
	// Note**
	// using Browser console F12 or google to check the result
	//(10)(10) ,10(10)means multiply and (0-10) means negative
	string Infix, Postfix = "1 2 + 4 *";
	Display();
	int UsetInput = 0;
	bool YES = false, YES2 = false;
	while (UsetInput != 3)
	{
		UsetInput = InputFrom2<int>(0, 5);
		switch (UsetInput)
		{
		case 1:
			if (YES2)
			{

				if (YorN())
				{
					Postfix = InfixTOPostfix(Infix);
					cout << "\nPostfix:[ " << Postfix << " ]";
				}
				else
				{
					cout << "\nEnter the equation:";
					cin.ignore(); // ignore \n
					getline(cin, Infix);
					Postfix = InfixTOPostfix(Infix);
					cout << "\nPostfix:[ " << Postfix << " ]";
				}
			}
			else
			{
				cout << "\nEnter the equation:";
				cin.ignore(); // ignore \n
				getline(cin, Infix);
				Postfix = InfixTOPostfix(Infix);
				cout << "\nPostfix:[ " << Postfix << " ]";
			}
			cout << "\nResult :[ " << PostfixResult(Postfix) << " ]";
			YES = true;
			break;
		case 2:
			if (YES)
			{
				if (YorN())
				{
					Infix = PostfixToInfix(Postfix);
					cout << "\nInfix  :[ " << Infix;
				}
				else
				{
					cout << "\nEnter the equation:";
					cin.ignore(); // ignore \n
					getline(cin, Postfix);
					Infix = PostfixToInfix(Postfix);
					cout << "\nInfix  :[ " << Infix;
				}
			}
			else
			{
				cout << "\nEnter the equation:";
				cin.ignore(); // ignore \n
				getline(cin, Postfix);
				Infix = PostfixToInfix(Postfix);
				cout << "\nInfix  :[ " << Infix << " ]";
			}
			YES2 = true;
			break;
		case 4:
			Display();
			break;
		default:
			break;
		}
		if (UsetInput != 3)
		{
			cout << "\nPress key 4 to show menu:";
		}
	}
	system("pause");
}