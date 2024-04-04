/*
Mahmood Nseer (Computer science)
Have a nice day ^-^
*/
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int DigitsSpace(int Val)
{
	long temp = Val;
	int Distance = 0;
	while (temp != 0)
	{
		temp = temp / 10;
		Distance++;
	}
	return Distance;
}
void MakeSpasce(int Distance, int Remove)
{
	Distance -= Remove;
	for (int _N = 0; _N < Distance; _N++)
	{
		cout << " ";
	}
}
void MakeBreaks(int L, char ASCII)
{
	for (int _N = 0; _N < L; _N++)
	{
		cout << ASCII;
	}
}
class list;
class Node
{
	friend list;
	Node *Prv;
	Node *Next;
	string Data;
	string Language;

public:
	Node();
	~Node();

private:
};
Node::Node()
{
	Prv = NULL;
	Next = NULL;
	Data = "N/N";
	Language = "N/N";
}
Node::~Node()
{
	//~list
}
class list
{
public:
	list();
	~list();
	int Spasce(int ID); // Display spaces between words like a table
	void AddBack(string word, string Language);
	void AddFront(string word, string Language);
	void VisualPrint(bool Reverse);
	void DelFront();
	void DelBack();
	void Sort();
	int CountLanguage(string word);
	int Search(string word);
	bool SpeSearch(string word, string Language); // SpeSearch
	void AddInOrder(string word, string Language);
	void RemoveWord(string word);
	bool operator==(list &Copy);

private:
	bool _Soft;
	void addBefore(Node *N, string word, string Language);
	void DelBefore(Node *N);
	bool Status()
	{
		return Header->Next != Trailer && Trailer->Prv != Header && Trailer->Prv != NULL && Header->Next != NULL;
	}
	Node *Header;
	Node *Trailer;
	int Size;
};
int list::Spasce(int ID)
{
	int Val = 0;
	int Distance = 0;
	Node *MaxWord = Header->Next;
	bool OneTIme = true;
	if (ID == 1)
	{
		Distance = 4; // Word default
	}
	else
	{
		Distance = 8; // Language default
	}
	while (MaxWord)
	{

		if (ID == 1)
		{
			Val = MaxWord->Data.length();
		}
		else
		{
			Val = MaxWord->Language.length();
		}
		if (Val > Distance)
		{
			Distance = Val;
		}
		MaxWord = MaxWord->Next;
	}
	return Distance;
}
bool list::operator==(list &Eq)
{
	Node *Temp = Eq.Header->Next;
	Node *This = this->Header->Next;
	bool Not = false;
	while (Eq.Trailer != Temp && This != Trailer)
	{
		if (This->Data != Temp->Data)
		{
			return false;
		}
		if (This->Language != Temp->Language)
		{
			return false;
		}
		This = This->Next;
		Temp = Temp->Next;
	}
	if (This == Trailer && Temp == Eq.Trailer)
	{
		return true;
	}
	return false;
}
void list::AddInOrder(string word, string Language)
{
	if (!this->SpeSearch(word, Language))
	{
		if (!_Soft)
		{
			this->Sort(); // I don't think this method is correct all time calling method Sort so i put boolean "_Soft"
		}
		Node *FactorWord = Header->Next;
		bool found = true;
		while (FactorWord && FactorWord != Header && FactorWord != Trailer && found)
		{
			if (FactorWord->Data > word)
			{
				found = false;
				this->addBefore(FactorWord, word, Language);
			}
			FactorWord = FactorWord->Next;
		}
		if (found) // if word last then ASCII CODE number in list, Will not passing ("if (FactorWord->Data > word)")
		{
			AddBack(word, Language);
		}
		_Soft = true;
	}
}
void list::addBefore(Node *N, string word, string Language)
{
	this->_Soft = false;
	Node *NewNode = new Node();
	NewNode->Data = word;
	NewNode->Language = Language;
	//
	NewNode->Prv = N->Prv;
	NewNode->Next = N;
	N->Prv->Next = NewNode; // HEADER
	N->Prv = NewNode;
	Size++;
}
int list::CountLanguage(string Language)
{
	int _N = 0;
	if (Status())
	{
		Node *SpecWord = Header->Next;
		while (SpecWord)
		{
			if (SpecWord->Language == Language)
			{
				_N++;
			}
			SpecWord = SpecWord->Next;
		}
	}
	return _N;
}
int list::Search(string word)
{
	if (Status())
	{
		int _N = 0;
		Node *SpecWord = Header->Next;
		while (SpecWord)
		{
			_N++;
			if (SpecWord->Data == word)
			{
				return _N;
			}
			SpecWord = SpecWord->Next;
		}
		return false;
	}
}
bool list::SpeSearch(string word, string Language)
{
	Node *SpecWord = Header->Next;
	while (SpecWord)
	{
		if (SpecWord->Data == word && SpecWord->Language == Language)
		{
			return true;
		}
		SpecWord = SpecWord->Next;
	}
	return false;
}
void list::Sort()
{
	if (Status())
	{
		this->_Soft = true;
		Node *FactorWord;
		Node *SpecWord = Header->Next;
		bool Stop = true;
		while (SpecWord != Header && SpecWord != Trailer && SpecWord)
		{
			FactorWord = Header->Next;
			while (FactorWord != Header && FactorWord != Trailer && FactorWord)
			{
				if (FactorWord->Data > SpecWord->Data)
				{
					string Data = FactorWord->Data;
					string Language = FactorWord->Language;
					FactorWord->Data = SpecWord->Data;
					FactorWord->Language = SpecWord->Language;
					//
					SpecWord->Data = Data;
					SpecWord->Language = Language;
				}
				FactorWord = FactorWord->Next;
			}
			SpecWord = SpecWord->Next;
		}
	}
}
void list::DelBefore(Node *N)
{
	if (Status())
	{
		Node *DelNode = N;
		//
		DelNode->Next->Prv = DelNode->Prv;
		DelNode->Prv->Next = DelNode->Next;
		delete DelNode;
		this->Size--;
	}
}
void list::AddFront(string word, string Language)
{
	if (!this->SpeSearch(word, Language))
	{
		addBefore(Header->Next, word, Language);
	}
}
void list::AddBack(string word, string Language)
{
	if (!this->SpeSearch(word, Language))
	{
		addBefore(Trailer, word, Language);
	}
}
list::list()
{
	Size = 0;
	Header = new Node();
	Trailer = new Node();
	Header->Next = Trailer;
	Trailer->Prv = Header;
	Header->Prv = NULL;
	Trailer->Next = NULL;
	_Soft = false;
}
void list::VisualPrint(bool Reverse) // perfect
{

	if (Status())
	{
		cout << "\n";
		Node *VisualSort = NULL;
		if (Reverse)
		{
			VisualSort = Trailer->Prv;
		}
		else
		{
			VisualSort = Header->Next;
		}
		int SPW = Spasce(1);
		int SPL = Spasce(2);
		cout << "\n+";
		MakeBreaks(1 + SPW, '=');
		cout << "+";
		MakeBreaks(2 + SPL, '=');
		cout << "+\n";
		//
		cout << "| Word";
		MakeSpasce(SPW, 4);
		//
		cout << "| Language";
		MakeSpasce(SPL, 8);
		cout << " |\n+";
		MakeBreaks(1 + SPW, '=');
		cout << "+";
		MakeBreaks(2 + SPL, '=');
		cout << "+\n";
		while (VisualSort != Trailer && VisualSort != Header)
		{
			cout << "| " << VisualSort->Data;
			MakeSpasce(SPW, VisualSort->Data.length());
			cout << "| " << VisualSort->Language;
			MakeSpasce(SPL, VisualSort->Language.length());
			if (Reverse)
			{
				VisualSort = VisualSort->Prv; // R
			}
			else
			{
				VisualSort = VisualSort->Next;
			}
			//---down---
			cout << " |\n+";
			MakeBreaks(1 + SPW, '-');
			cout << "+";
			MakeBreaks(2 + SPL, '-');
			cout << "+\n";
		}
		//---down---
		cout << "| Size:";
		cout << this->Size;
		MakeSpasce(SPW + SPL, DigitsSpace(this->Size) + 2); //+5 Size:
		cout << "|\n+";
		MakeBreaks(4 + SPW + SPL, '=');
		cout << "+\n";
	}
}
void list::DelFront()
{
	if (Status())
	{
		DelBefore(Header->Next);
	}
}
void list::RemoveWord(string word)
{
	if (Status())
	{
		Node *DelNode = Header->Next;
		/*
		while (DelNode && DelNode->Data != word)//best way
		{
			DelNode = DelNode->Next;
		}
		if (DelNode && DelNode->Data == word)
		{
			DelNode->Prv->Next = DelNode->Next;
			DelNode->Next->Prv = DelNode->Prv;
			delete DelNode;
		}
		*/
		int Factor = this->Search(word);
		for (int _N = 0; _N < Factor - 1; _N++)
		{
			DelNode = DelNode->Next;
		}
		if (DelNode && DelNode->Data == word) // Safe
		{
			DelNode->Prv->Next = DelNode->Next;
			DelNode->Next->Prv = DelNode->Prv;
			delete DelNode;
		}
		this->Size--;
	}
}
void list::DelBack()
{
	if (Status())
	{
		DelBefore(Trailer->Prv);
	}
}
list::~list()
{
	int _N = 0;
	cout << "\n";
	while (Status())
	{
		this->DelBack();
	}
	Trailer->Prv = NULL;
	delete this->Trailer;
	Header->Next = NULL;
	delete this->Header;
}
void ReadFile(list *PonterHI, string File, int Level123)
{
	ifstream InputFile;
	InputFile.open(File);
	if (InputFile.is_open())
	{
		while (!InputFile.eof())
		{
			string word;
			string Lang;
			InputFile >> word;
			InputFile >> Lang;
			if (!PonterHI->SpeSearch(word, Lang))
			{
				if (Level123 == 1)
				{
					PonterHI->AddFront(word, Lang);
				}
				else if (Level123 == 2)
				{
					PonterHI->AddBack(word, Lang);
				}
				else
				{
					PonterHI->AddInOrder(word, Lang);
				}
			}
		}
	}
}
int main()
{
	list X;
	cout << "list [X]";
	ReadFile(&X, "Word1.txt", 1); // add files addFront
	ReadFile(&X, "Word2.txt", 2); // add files addBack
	cout << "\nPrint normally";
	X.VisualPrint(false);
	cout << "How many words are there in this language Japanese [" << X.CountLanguage("Japanese") << "]";
	cout << "\nHow many words are there in this language Arabic   [" << X.CountLanguage("Arabic") << "]";
	cout << "\nHow many words are there in this language English  [" << X.CountLanguage("English") << "]";
	cout << "\nDelete from the front";
	X.DelFront();
	cout << "\nDelete from the back";
	X.DelBack();
	X.VisualPrint(false);
	cout << "AddInOrder";
	X.AddInOrder("arrow", "English"); // soft
	cout << "\nAddInOrder";
	X.AddInOrder("friend", "English");
	cout << "\nNumber of the node: arrow [" << X.Search("arrow") << "]";
	cout << "\nNumber of the node: friend [" << X.Search("friend") << "]";
	cout << "\nPrint normally";
	X.VisualPrint(false);
	list Y;
	cout << "list [Y]";
	ReadFile(&Y, "Word1.txt", 1); // add files addFront
	Y.Sort();
	cout << "\nPrint normally";
	Y.VisualPrint(false);
	// Special cases
	list Z;
	cout << "list [Z]";
	Z.Sort();
	Z.Search("");
	Z.DelBack();
	Z.DelBack();
	Z.DelFront();
	Z.DelFront();
	Z.AddBack("hello", "English");
	Z.AddFront("hello", "English");
	Z.RemoveWord("hello");
	Z.RemoveWord("");
	ReadFile(&Z, "Word2.txt", 3); // add files AddInOrder
	// Z.AddFront("wast", "English");//soft==false
	cout << "\nPrint normally";
	Z.VisualPrint(false);
	//
	Z.AddInOrder("nice", "English"); // soft==true
	Z.AddInOrder("nice", "English"); // soft==true
	cout << "Print normally";
	Z.VisualPrint(false);
	//
	list M;
	list N;
	ReadFile(&M, "Word1.txt", 1); // add files addFront
	ReadFile(&N, "Word1.txt", 2); // add files AddBack
	M.AddBack("yeah", "English");
	N.AddFront("yeah", "English");
	cout << "list [M & N]";
	cout << "\nEqual " << (M == N);
	M.AddInOrder("No", "English");
	N.AddInOrder("No", "English");
	cout << "\nEqual " << (M == N);
	M.AddBack("love", "English");
	N.AddFront("love", "English");
	cout << "\nEqual " << (M == N);
	M.VisualPrint(false);
	M.VisualPrint(true);
	N.VisualPrint(false);
	N.VisualPrint(true);
	cout << "How many words are there in this language Japanese [" << N.CountLanguage("Japanese") << "]";
	cout << "\nHow many words are there in this language Arabic [" << N.CountLanguage("Arabic") << "]";
	cout << "\nHow many words are there in this language English [" << N.CountLanguage("English") << "]";
	char a[200];
	cin >> a;
}
// [December 4, 2020]