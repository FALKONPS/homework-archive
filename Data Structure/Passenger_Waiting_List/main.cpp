/*
Mahmood Nseer(Computer Science)
Have a nice day ^^
*/
#include <iostream>
#include <string>
using namespace std;
class Node;
class list;
class Passenger;
bool thisNumber(char WhatThis)
{
	if ((WhatThis < '0' || WhatThis > '9'))
	{
		return false;
	}
	return true;
}
class DataTime
{
public:
	string TimeReady;
	unsigned long long TimeLong;
	unsigned long long ReturnTimeNumber()
	{
		return TimeLong;
	}
	DataTime(string Time)
	{
		TimeReady = TimeCutNumber(Time);
		TimeLong = stoull(TimeReady);
	}
	DataTime()
	{
		TimeLong = 9999999999;
		TimeReady = "9999999999";
	}
	string TimeCutNumber(string Time)
	{
		string TimeReady;
		//2001 7 28 12:55 
		//2001 97 23 90 55
		//0123 45 67 89 01
		int _N = 0;
		for (; _N < Time.length(); _N++)
		{
			if (Time[_N] != ' ')
			{
				if (thisNumber(Time[_N]))
				{
					while (thisNumber(Time[_N]))
					{
						if (_N != 0)
						{
							if (_N < Time.length() - 1)
							{
								if (!thisNumber(Time[_N - 1]) && !thisNumber(Time[_N + 1]))
								{
									TimeReady += "0";
								}
							}
							else if (_N == Time.length() - 1)
							{
								if (!thisNumber(Time[_N - 1]) && !thisNumber(Time[_N + 1]))
								{
									TimeReady += "0";
								}
							}
						}
						TimeReady += Time[_N];
						_N++;
					}
					_N--;
				}
			}
		}
		return TimeReady;
	}

	string TimeToNumber()
	{
		//2001 97 23 90 55
		//0123 45 67 89 01
		string OUTput;
		OUTput += TimeReady.substr(0, 4);
		OUTput += " ";
		OUTput += TimeReady.substr(4, 2);
		OUTput += " ";
		OUTput += TimeReady.substr(6, 2);
		OUTput += " ";
		OUTput += TimeReady.substr(8, 2);
		OUTput += ":";
		OUTput += TimeReady.substr(10, 2);
		return OUTput;
	}

};
class Passenger
{
public:
	Passenger()//Header,Trailer
	{
		this->Name = "Undefined";
		this->Rank = 0;
	}
	Passenger(string Name, int Rank, string Time)
	{
		this->Name = Name;
		this->Rank = Rank;
		DataTime TimeInput(Time);
		TimeAndData = TimeInput;
	}
private:
	friend list;
	friend Node;
	string Name;
	DataTime TimeAndData;
	int Rank;
};
class list;
class Node
{
	friend list;
	Node* Prv;
	Node* Next;
	Passenger DataPassenger;
public:
	Node(Passenger Data);
	Node();
	~Node();
private:
};
Node::Node()
{
	Prv = NULL;
	Next = NULL;
}
Node::Node(Passenger Data)
{
	DataPassenger = Data;
	Prv = NULL;
	Next = NULL;
}
Node::~Node()
{
}
class list
{
public:
	list();
	~list();
	void deqeueFront();
	void enqueue(Passenger Data);
	string TopFront()
	{
		if (Status())
		{
			return  Header->Next->DataPassenger.Name;
		}
		else
		{
			return "There are no names on the queue";
		}
	}
	void Pr();
	bool Status()
	{
		return Header->Next != Trailer;
	}
	int Size()
	{
		return Passengers;
	}
private:
	int Passengers;
	Node* Header;
	Node* Trailer;
	void addBefore(Node* N, Passenger informations);//add before a node
	void DelBefore(Node* N);
	void PushDataforward(Passenger informations);
	void PushDataBack(Passenger informations);
};
void list::addBefore(Node* N, Passenger informations)
{
	Node* NewNode = new Node();
	NewNode->Next = N;
	NewNode->Prv = N->Prv;
	N->Prv->Next = NewNode;
	N->Prv = NewNode;
	NewNode->DataPassenger = informations;
	Passengers++;
}
void list::DelBefore(Node* N)
{
	if (Status())
	{
		Node* DelNode = N;
		DelNode->Next->Prv = DelNode->Prv;
		DelNode->Prv->Next = DelNode->Next;
		delete DelNode;
		this->Passengers--;
	}
}
void list::PushDataforward(Passenger Data)
{
	addBefore(Header->Next, Data);
}
void list::PushDataBack(Passenger Data)
{
	addBefore(Trailer, Data);
}
void list::deqeueFront()
{
	if (Status())
	{
		DelBefore(Header->Next);
	}
	else
	{
		cout << "\nThere are no passengers on the waiting list";
	}
}
list::list()
{
	Passengers = 0;
	Header = new Node();
	Trailer = new Node();
	Header->Next = Trailer;
	Trailer->Prv = Header;
}

void list::enqueue(Passenger Data)
{
	Node* Node__ = this->Header->Next;
	bool Eq = false;
	if (!this->Status())
	{
		this->PushDataforward(Data);
	}
	else
	{
		while (Node__ != this->Trailer && !Eq)
		{
			if (Data.Rank > Node__->DataPassenger.Rank)
			{
				addBefore(Node__, Data);
				Eq = true;
			}
			else if (Data.Rank < Node__->DataPassenger.Rank)
			{
				while (!(Data.Rank > Node__->DataPassenger.Rank) && Node__ != this->Trailer)
				{
					if (Data.Rank == Node__->DataPassenger.Rank)
					{
						goto qq;//I can write that code here ,But this is a shortcut save a lot of time and bugs^^
					}
					Node__ = Node__->Next;
				}
				addBefore(Node__, Data);
				Eq = true;
			}
			else if (Data.Rank == Node__->DataPassenger.Rank)
			{
			qq:
				while (Data.Rank == Node__->DataPassenger.Rank && Data.TimeAndData.ReturnTimeNumber() > Node__->DataPassenger.TimeAndData.ReturnTimeNumber() && Node__ != this->Trailer)
				{
					Node__ = Node__->Next;
				}
				addBefore(Node__, Data);
				Eq = true;
			}
			Node__ = Node__->Next;
		}
	}


}
void list::Pr()
{
	Node* Node__ = this->Header->Next;
	while (Node__ != Trailer)
	{
		cout << "\nName:" << Node__->DataPassenger.Name;
		cout << "| Rank:" << Node__->DataPassenger.Rank;
		cout << ":" << Node__->DataPassenger.TimeAndData.TimeToNumber();
		Node__ = Node__->Next;
	}
}
Passenger InformationsPassenger()
{
	string Name, Time;
	int Rank;
	cout << "\nName:";
	cin.ignore();
	getline(cin, Name);
	cout << "\nNumber of flights:";
	cin >> Rank;
	cout << "\nData(Year Month Day Hours:Minutes) ex[2020-12-31 23:59]:";
	cin.ignore();
	getline(cin, Time);
	return Passenger(Name, Rank, Time);
}
list::~list()
{
	while (this->Status())
	{
		deqeueFront();
	}
	delete Header;
	delete Trailer;

}
//end
void Display()
{
	cout << "1 - Add a passenger to the waiting list.\n"
		<< "2 - Display the passenger with highest priority.\n"
		<< "3 - Remove passenger from the waiting list(the one with highest priority).\n"
		<< "4 - Display the number of passengers on the waiting list.\n"
		<< "5 - Exit.\n"
		<< "6 - Show menu.\n"
		<< "7 - Display All Queue.\n"
		<< "8 - Generate probabilities.\n";
}
int main()
{
	Display();
	list Waiting;

	int InputUse = 0;
	while (true)
	{
		cin >> InputUse;
		switch (InputUse)
		{
		case 1:
			Waiting.enqueue(InformationsPassenger());
			break;
		case 2:
			cout << "\n:" << Waiting.TopFront();
			break;
		case 3:
			Waiting.deqeueFront();
			break;
		case 4:
			cout << "\nWaiting:" << Waiting.Size();
			break;
		case 5:
			return 0;
			break;
		case 6:
			Display();
			break;
		case 7:
			Waiting.Pr();
			break;
		case 8:
			for (int _N = 0; _N < 9; _N++)
			{
				string TimeS = "2020-" + to_string(((rand() % 12) + 1)) + "-" + to_string(((rand() % 31) + 1)) + " " + to_string(((rand() % 23) + 1)) + ":" + to_string(((rand() % 60) + 1));
				Waiting.enqueue(Passenger(to_string(_N), ((rand() % 10) + 1), TimeS));
			}
			Waiting.Pr();
			cout << "\nWaiting:" << Waiting.Size();
			break;
		default:
			cout << "\nValue not found,Try again.";
			break;
		}
		cout << "\nPress[6] to Show menu:";
	}
}