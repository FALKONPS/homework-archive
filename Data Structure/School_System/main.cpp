/*
Mahmood Nseer(Computer Science)
Have a Nice Day ^-^
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
#define Rate 100.0f // Exam Rate
#define IndexCS 100 // array
void MakeSpasce(int Distance, int Remove);
void MakeBreaks(int L, char ASCII);
template <typename T>
T InputFrom2(int, int);
class Node;
class school;
class student
{
private:
    long ID;
    string Name;
    string Address;
    vector<float> grades;
    vector<float> weightGrades; // form me^^
    student *Next;
    friend school;
    friend Node;

public:
    student(int ID, string Name, string Address)
    {
        this->ID = ID;
        this->Name = Name;
        this->Address = Address;
        Next = NULL;
    }
    ~student() //-_-
    {
        Next = NULL;
        cout << "\nstudent destructor is called\n";
    }
};
class Node // the node represents a class in school
{
private:
    friend school;
    int ID;
    int NoOfExams;
    student *t; // an array of students is allocated dynamically
    Node *Next;

public:
    int NoOfStudents;
    Node()
    {
        NoOfExams = 0;
        ID = 0;
        NoOfStudents = 0;
        t = NULL;
        Next = NULL;
    }
    ~Node()
    {
        student *Before = t;
        while (t)
        {
            Before = t;
            t = t->Next;
            Before->grades.erase(Before->grades.begin(), Before->grades.end());
            Before->weightGrades.erase(Before->weightGrades.begin(), Before->weightGrades.end());
            delete Before;
            cout << "\n"
                 << "~Node~\n";
        }
    }

    void NewNode(int ID, string Name, string Address);
};
void Node::NewNode(int ID, string Name, string Address)
{
    student *_Node = new student(ID, Name, Address);
    if (t == NULL)
    {
        t = _Node;
    }
    else
    {
        bool Break = true;
        student *Before = t;
        while (t && Break)
        {
            if (Before->Next == NULL)
            {
                Break = false;
            }
            if (Break)
            {
                Before = Before->Next;
            }
        }
        Before->Next = _Node;
    }
}
class school
{
private:
    string Name;
    Node *Head;
    int n; // number of classes in school

public:
    school(string Name);
    ~school()
    {
        Node *Before = Head;
        while (Head)
        {
            Before = Head;
            Head = Head->Next;
            delete Before;
            cout << "\n~CLass~\n";
        }
    }
    bool GetStatus()
    {
        if (Head)
        {
            return true;
        }
        return false;
    }
    // Visual
    void VFXStudents(student *Students, int CounterlD, int CounterName, int CounterAddress);
    int Spasce(int ID); // Display spaces between words like a table
    int DigitsSpace();
    int MM(long Val);                   // Counter Digits of the number
    int DisplayIDClass();               // A list of existing student classes
    int DisplayIDStudents();            // A list of Students in the school
    void DisplayByStudent(string Name); // Display information by student name
    void DisplayAllSchool();            // Display all students' information
    void DisplayByClass(int ClassID);   // Display information for students in a class
    // Services
    void NewClassNode(const string PathFile);          // Create a new class of students
    void DelNode(int ClassID);                         // Delete a class of students
    void AddStudent(int ClassID, student *NewStudent); // Add a student to a class
    void DelStudent(int ClassID);                      // Remove a student from the class
    void SortStudents(int ClassID);                    // Alphabetical order
    void MaximumAverage(int ClassID);                  // Best student in a class
    float AverageStudent(int ID);                      // Average student score for all courses
    void CertainExam(int ClassID, const int examID);   // Add exam marks to students
    //_
    float AverageWeight(int ID, const Node *ClassFound); //_MaximumAverage
    bool IDRepClass(int ClassID);                        // Class ID repeat check
    bool IDRep(int ID);                                  // Students ID repeat check
    void _Swap(student *InI, student *InII);             // Switch students
    student *StudentData();                              // Enter new data of the type of "student"
};
school::school(string Name)
{
    this->Name = Name;
    Head = NULL;
    n = 0;
}
int school::Spasce(int ID)
{
    int Val = 0;
    int Distance = 0;
    Node *Class = Head;
    student *Student = Class->t;

    while (Class)
    {
        while (Student)
        {
            if (ID == 1)
            {
                Val = Student->Name.length();
            }
            else
            {
                Val = Student->Address.length();
            }
            if (Distance < Val)
            {
                Distance = Val;
            }
            if (Student)
            {
                Student = Student->Next;
            }
        }
        Class = Class->Next;
        if (Class)
        {
            Student = Class->t;
        }
    }
    return Distance;
}
int school::DigitsSpace()
{
    int Distance = 0;
    Node *Class = Head;
    student *Student = Class->t;
    while (Class)
    {
        while (Student)
        {
            int temp = MM(Student->ID);
            if (Distance < temp)
            {
                Distance = temp;
            }
            Student = Student->Next;
        }
        Class = Class->Next;
        if (Class)
        {
            Student = Class->t;
        }
    }
    return Distance;
}
int school::DisplayIDClass()
{
    if (Head)
    {
        Node *IDClass = Head;
        int Input = 1;
        bool B_Input = false;
        int _N = 1;
        int _NClass[IndexCS] = {0};
        while (IDClass)
        {
            _NClass[_N] = IDClass->ID;
            cout << "\n"
                 << _N << "-" << IDClass->ID;
            IDClass = IDClass->Next;
            _N++;
        }
        cout << "\nChoose the class ID:";
        Input = InputFrom2<int>(0, _N); // cin
        if (Input > 0)                  // Warning C6385 -_-
        {
            return _NClass[Input];
        }
    }
    return -9;
}
int school::MM(long Val)
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
int school::DisplayIDStudents()
{
    if (Head)
    {
        Node *IDClass = Head;
        int Input = 0;
        bool NotStudent = false, B_Input = false;
        int _N = 1;
        long _NStudent[IndexCS];
        _NStudent[0] = 999;
        student *Student = Head->t;
        while (IDClass)
        {
            if (Student)
            {
                NotStudent = true;
                while (Student)
                {
                    _NStudent[_N] = Student->ID;
                    cout << "\n"
                         << _N << "-[ ";
                    cout << Student->ID;
                    cout << "] ClassID:[" << IDClass->ID << "]";
                    _N++;
                    Student = Student->Next;
                }
            }
            IDClass = IDClass->Next;
            if (IDClass)
            {
                Student = IDClass->t;
            }
        }
        if (NotStudent)
        {
            cout << "\nChoose the ID Student:";
            Input = InputFrom2<int>(0, _N); // cin
            if (Input > 0)
            {
                return _NStudent[Input];
            }
        }
        else
        {
            cout << "There are no students registered!,Enter new students\n";
        }
    }
    return 0;
}
bool school::IDRepClass(int ClassID)
{
    Node *_IDClass = Head;
    while (_IDClass)
    {
        if (_IDClass->ID == ClassID)
        {
            return true;
        }
        _IDClass = _IDClass->Next;
    }
    return false;
}
bool school::IDRep(int ID)
{
    student *Student = Head->t;
    Node *Class = Head;
    while (Class)
    {
        Student = Class->t;
        while (Student)
        {
            if (Student->ID == ID)
            {
                return true;
            }
            Student = Student->Next;
        }
        Class = Class->Next;
    }
    return false;
}
void school::_Swap(student *First, student *Sec)
{
    vector<float> grades = First->grades;
    vector<float> weightGrades = First->weightGrades;
    int ID = First->ID;
    First->Name.swap(Sec->Name);
    First->Address.swap(Sec->Address);
    First->ID = Sec->ID;
    First->grades = Sec->grades;
    First->weightGrades = Sec->weightGrades;
    Sec->ID = ID;
    Sec->grades = grades;
    Sec->weightGrades = weightGrades;
}
void school::DelStudent(int ID)
{
    if (IDRep(ID))
    {
        if (Head)
        {
            Node *ClassFound = Head;
            student *temp = NULL;
            bool Break = true; // break

            student *SearchStudent = NULL;
            student *BeforeStudent = NULL;
            while (ClassFound && Break)
            {
                SearchStudent = ClassFound->t;
                if (SearchStudent) // may be NULL
                {
                    if (SearchStudent->ID == ID)
                    {
                        ClassFound->NoOfStudents--;
                        temp = ClassFound->t;
                        ClassFound->t = ClassFound->t->Next;
                        delete temp;
                        Break = false;
                    }
                    else
                    {
                        while (SearchStudent && Break)
                        {
                            if (SearchStudent->ID == ID)
                            {
                                Break = false;
                                BeforeStudent->Next = SearchStudent->Next;
                                delete SearchStudent;
                                ClassFound->NoOfStudents--;
                            }
                            else
                            {
                                BeforeStudent = SearchStudent;
                                SearchStudent = SearchStudent->Next;
                            }
                        }
                    }
                }
                ClassFound = ClassFound->Next;
                if (Break)
                {
                    SearchStudent = ClassFound->t;
                }
            }
        }
    }
    else
    {
        cout << "Student ID not found\n";
    }
}
void school::DelNode(int ID)
{
    if (IDRepClass(ID))
    {
        if (Head)
        {
            Node *ClassHead = Head;
            bool Break = true;    // break
            bool NoClass = false; // break
            Node *SearchClass = NULL;
            Node *BeforeClass = NULL;
            SearchClass = ClassHead;
            while (ClassHead && Break)
            {
                if (SearchClass) // may be NULL
                {
                    NoClass = true;
                    if (SearchClass->ID == ID)
                    {

                        Head = SearchClass->Next;
                        delete SearchClass;
                        Break = false;
                    }
                    else
                    {
                        while (SearchClass && Break)
                        {
                            if (SearchClass->ID == ID)
                            {
                                Break = false;
                                BeforeClass->Next = SearchClass->Next;
                                delete SearchClass;
                            }
                            else
                            {
                                BeforeClass = SearchClass;
                                SearchClass = SearchClass->Next;
                            }
                        }
                    }
                    this->n--;
                }
                if (Break)
                {
                    ClassHead = ClassHead->Next;
                    SearchClass = ClassHead;
                }
                if (!NoClass)
                {
                    cout << "There is no school classes\n";
                }
            }
        }
    }
    else
    {
        cout << "class ID not found\n";
    }
}
void school::AddStudent(const int ClassID, student *NewStudent)
{
    if (NewStudent)
    {
        if (Head)
        {
            student *_NewStudent = Head->t;
            student *TempHead = Head->t;
            Node *ClassFound = Head;
            bool found = false; // break
            while (ClassFound && !found)
            {
                if (ClassFound->ID == ClassID)
                {
                    found = true; // found
                    if (!IDRep(NewStudent->ID))
                    {
                        found = false;
                        ClassFound->NoOfStudents++;
                        TempHead = ClassFound->t;
                        NewStudent->Next = ClassFound->t;
                        ClassFound->t = NewStudent;
                        if (ClassFound->NoOfExams > 0)
                        {
                            int CounterName = Spasce(1);
                            int CounterlD = DigitsSpace();
                            int CounterAddress = Spasce(0);
                            int NiceLook = CounterName + CounterlD + CounterAddress + 37;
                            for (int _N = 1; _N <= ClassFound->NoOfExams; _N++)
                            {
                                cout << "\n";
                                string NameExam;
                                cout << "\nThere is an exam for this class. Please enter the score";
                                cout << "\nExam Scores";
                                float grades = 0.f;
                                float Markweight = TempHead->weightGrades[0];
                                cout << "\nMark weight is:[" << Markweight << "]\n";
                                MakeBreaks(NiceLook, '=');
                                cout << "\n";
                                VFXStudents(NewStudent, CounterlD, CounterName, CounterAddress);
                                MakeBreaks(NiceLook, '-');
                                cout << "\n";
                                cout << "Grades:";
                                grades = InputFrom2<float>(-1, Markweight + 1); // cin
                                MakeBreaks(NiceLook, '-');
                                cout << "\n";
                                NewStudent->grades.push_back(grades);
                                NewStudent->weightGrades.push_back(Markweight);
                            }
                        }
                    }
                    else
                    {
                        cout << "ID already exists\n";
                    }
                }
                if (!found)
                {
                    ClassFound = ClassFound->Next;
                }
            }
        }
    }
}
void school::SortStudents(int ClassID)
{
    bool _Stop = true;
    Node *ClassFound = Head;
    bool found = false; // break
    while (ClassFound && !found)
    {
        if (ClassFound->ID == ClassID)
        {
            found = true;
            if (ClassFound->t)
            {
                student *Current = ClassFound->t;
                while (Current)
                {
                    student *Before = ClassFound->t;
                    _Stop = true; // break
                    while (Before && _Stop)
                    {
                        if (Current->Name < Before->Name && Current->Name != "\0")
                        {
                            _Swap(Current, Before);
                            _Stop = false; // break
                        }
                        if (_Stop) // break
                        {
                            Before = Before->Next;
                        }
                    }
                    if (_Stop) // break
                    {
                        Before = ClassFound->t;
                        Current = Current->Next;
                    }
                }
            }
            else
            {
                cout << "classroom is empty\n";
            }
        }
        if (!found)
        {
            ClassFound = ClassFound->Next;
        }
    }
}
void school::CertainExam(int ClassID, int examID)
{
    if (Head)
    {
        student *Student = NULL;
        Node *ClassFound = Head;
        bool Break, BreakN = Break = false; // Break
        // bool;//Break
        while (ClassFound && !Break)
        {
            if (ClassFound->ID == ClassID)
            {
                Break = true; // found
                if (ClassFound->t)
                {
                    BreakN = true;
                    ClassFound->NoOfExams++;
                    this->SortStudents(ClassID);
                    Student = ClassFound->t;
                }
            }
            if (!Break)
            {
                ClassFound = ClassFound->Next;
            }
        }
        if (BreakN)
        {
            if (Break)
            {
                string NameExam;
                if (examID == 1)
                {
                    NameExam = "First";
                }
                else if (examID == 2)
                {
                    NameExam = "Second";
                }
                else if (examID == 3)
                {
                    NameExam = "Final";
                }
                else
                {
                    NameExam = "undefined";
                }
                int CounterName = Spasce(1);
                int CounterlD = DigitsSpace();
                int CounterAddress = Spasce(0);
                int NiceLook = CounterName + CounterlD + CounterAddress + 37;
                cout << "\n";
                MakeBreaks(NiceLook, '=');
                cout << "\nExam Scores : " << NameExam;
                float Markweight, grades = Markweight = 0.f;
                cout << "\nMark weight:";
                cin >> Markweight;
                while (Student)
                {
                    MakeBreaks(NiceLook, '=');
                    cout << "\n";
                    VFXStudents(Student, CounterlD, CounterName, CounterAddress);
                    MakeBreaks(NiceLook, '-');
                    cout << "\nGrades:";
                    grades = InputFrom2<float>(-1, Markweight + 1); // cin
                    Student->grades.push_back(grades);
                    Student->weightGrades.push_back(Markweight);
                    Student = Student->Next;
                    cout << "\n";
                }
                MakeBreaks(NiceLook, '=');
            }
            else
            {
                cout << "Classrooms ID not found\n";
            }
        }
        else
        {
            cout << "classroom is empty\n";
        }
    }
}
void school::NewClassNode(const string PathFile)
{
    fstream InputFile;
    InputFile.open(PathFile);
    if (InputFile.is_open())
    {
        Node *NewClass = new Node;
        Node *before;
        int ID;
        int NoOfStudents;
        InputFile >> ID;
        InputFile >> NoOfStudents;
        if (!IDRepClass(ID))
        {
            if (!Head)
            {
                this->Head = NewClass;
                this->Head->ID = ID;
            }
            else
            {
                NewClass->ID = ID;
                before = Head;
                bool Break = true; // break
                while (before && Break)
                {
                    if (before->Next == NULL)
                    {
                        before->Next = NewClass;
                        Break = false;
                    }
                    if (Break) // break
                    {
                        before = before->Next;
                    }
                }
            }
            InputFile.seekg(0);
            string Temp;
            InputFile >> Temp;
            InputFile >> Temp;
            Temp.clear();
            NewClass->NoOfStudents = NoOfStudents;
            while (!InputFile.eof())
            {
                int ID = 0;
                string Address = "\0";
                string Name = "\0";
                InputFile >> ID;
                InputFile >> Name;
                InputFile >> Address;
                NewClass->NewNode(ID, Name, Address);
            }
            n++;
            cout << "The files were successfully accessed!\n";
        }
        else
        {
            cout << "Classroom ID already exists!\n";
        }
        InputFile.close();
    }
    else
    {
        cout << "The file path is wrong!\n";
    }
}
float school::AverageWeight(int ID, const Node *ClassFound)
{
    student *before = ClassFound->t;
    while (before)
    {
        if (before->ID == ID)
        {
            float _grades = 0.f;
            float Avg = 0.f;
            int Size = int(before->grades.size());

            for (int _N = 0; _N < Size; _N++)
            {

                _grades += before->grades[_N];
                Avg += before->weightGrades[_N];
            }
            return ((_grades / Avg) * Rate); // Rate=100
        }
        before = before->Next;
    }
    return -9.9f;
}
float school::AverageStudent(int ID)
{
    if (ID)
    {
        bool Br = true;
        if (Head)
        {
            Node *ClassFound = Head;
            while (ClassFound && Br)
            {
                student *Student = ClassFound->t;
                while (Student && Br)
                {
                    if (Student->ID == ID)
                    {
                        Br = false;
                        if (ClassFound->t)
                        {

                            if (ClassFound->NoOfExams != 0)
                            {
                                float _grades = 0.f;
                                float Avg = 0.f;
                                int Size = Student->grades.size();

                                for (int _N = 0; _N < Size; _N++)
                                {
                                    _grades += Student->grades[_N];
                                    Avg += Student->weightGrades[_N];
                                }
                                return ((_grades / Avg) * Rate); // Rate=100
                            }
                            else
                            {
                                cout << "There is no exam for this class\n";
                            }
                        }
                        else
                        {
                            cout << "classroom is empty\n";
                        }
                    }
                    Student = Student->Next;
                }
                ClassFound = ClassFound->Next;
                if (ClassFound)
                {
                    Student = ClassFound->t;
                }
            }
        }
    }
    return 0;
}
void school::MaximumAverage(int ClassID)
{
    if (Head)
    {
        student *before = Head->t;
        Node *ClassFound = Head;
        bool Break = true; // break
        while (ClassFound && Break)
        {
            if (ClassFound->ID == ClassID)
            {
                if (ClassFound->t)
                {
                    if (ClassFound->NoOfExams != 0)
                    {
                        float Max, ISmax = Max = AverageWeight(before->ID, ClassFound);
                        if (ClassFound->NoOfExams > 0)
                        {
                            before = ClassFound->t;
                            student *Nice = ClassFound->t;
                            while (before)
                            {
                                ISmax = AverageWeight(before->ID, ClassFound);
                                if (Max < ISmax)
                                {
                                    Nice = before;
                                    Max = ISmax;
                                }
                                before = before->Next;
                            }
                            if (Nice) // Null
                            {
                                int CounterName = Spasce(1);
                                int CounterlD = DigitsSpace();
                                int CounterAddress = Spasce(0);
                                int NiceLook = CounterName + CounterlD + CounterAddress + 37;
                                MakeBreaks(NiceLook, '=');
                                cout << "\n";
                                VFXStudents(Nice, CounterlD, CounterName, CounterAddress);
                                cout << "Average [ " << Max << " ]\n";
                                MakeBreaks(NiceLook, '=');
                                cout << "\n";
                            }
                        }
                    }
                    else
                    {
                        cout << "There is no exam for this class\n";
                    }
                }
                else
                {
                    cout << "classroom is empty\n";
                }
                Break = false;
            }
            if (Break)
            {
                ClassFound = ClassFound->Next;
            }
        }
    }
}
void school::DisplayByStudent(string Name)
{
    if (Head)
    {

        student *Student = Head->t;
        Node *ClassFound = Head;
        int Index = 0;
        bool Brack = true; // break
        while (ClassFound)
        {
            if (ClassFound)
            {
                Student = ClassFound->t;
                while (Student)
                {
                    if (Student->Name == Name)
                    {
                        int CounterName = Spasce(1);
                        int CounterlD = DigitsSpace();
                        int CounterAddress = Spasce(0);
                        int NiceLook = CounterName + CounterlD + CounterAddress + 37;
                        if (Brack)
                        {
                            cout << "search result\n";
                            Brack = false;
                        }
                        MakeBreaks(NiceLook, '=');
                        cout << "\n";

                        VFXStudents(Student, CounterlD, CounterName, CounterAddress);
                        if (Student->grades.size() != 0)
                        {
                            MakeBreaks(NiceLook, '-');
                            cout << "\nGrades:";
                            for (int _N = 0; _N < Student->grades.size(); _N++)
                            {
                                cout << "\n"
                                     << _N + 1 << ".[" << Student->grades[_N] << "/" << Student->weightGrades[_N] << "]";
                            }
                            cout << "\nAverage:[" << this->AverageWeight(Student->ID, ClassFound) << "%]\n";
                        }
                        MakeBreaks(NiceLook, '=');
                        cout << "\n";
                    }
                    Student = Student->Next;
                }
            }
            ClassFound = ClassFound->Next;
        }
    }
}
void school::DisplayByClass(int ClassID)
{
    if (Head)
    {

        student *Student = Head->t;
        Node *ClassFound = Head;
        bool Brack = true; // break
        while (ClassFound && Brack)
        {
            if (ClassFound->ID == ClassID)
            {
                Brack = false;
                if (ClassFound->t)
                {
                    int CounterName = Spasce(1);
                    int CounterlD = DigitsSpace();
                    int CounterAddress = Spasce(0);
                    int NiceLook = CounterName + CounterlD + CounterAddress + 37;
                    while (Student)
                    {
                        MakeBreaks(NiceLook, '=');
                        cout << "\n";
                        VFXStudents(Student, CounterlD, CounterName, CounterAddress);
                        if (Student->grades.size() != 0)
                        {
                            MakeBreaks(NiceLook, '-');
                            cout << "\nGrades:";
                            for (int _N = 0; _N < Student->grades.size(); _N++)
                            {
                                cout << "\n"
                                     << _N + 1 << ".[" << Student->grades[_N] << "/" << Student->weightGrades[_N] << "]";
                            }
                            cout << "\nAverage:[" << this->AverageWeight(Student->ID, ClassFound) << "%]\n";
                            MakeBreaks(NiceLook, '=');
                            cout << "\n";
                        }
                        else
                        {
                            MakeBreaks(NiceLook, '=');
                            cout << "\n";
                        }
                        Student = Student->Next;
                    }
                }
                else
                {
                    cout << "classroom is empty\n";
                }
            }
            if (Brack)
            {
                ClassFound = ClassFound->Next;
                if (ClassFound)
                {
                    Student = ClassFound->t;
                }
            }
        }
    }
}
void MakeBreaks(int L, char ASCII)
{
    for (int _N = 0; _N < L; _N++)
    {
        cout << ASCII;
    }
}
student *school::StudentData()
{
    string Name;
    string Addr;
    int ID;
    bool VII = false;
    cout << "\nEnter the student ID:";
    do
    {
        if (VII)
        {
            cout << "\nthis ID already exists,Enter another ID";
        }
        cin >> ID;
        VII = true;
    } while (IDRep(ID));
    cout << "\nEnter the student Name:";
    cin.ignore();
    getline(cin, Name);
    cout << "\nEnter the student Address:";
    getline(cin, Addr);
    return new student(ID, Name, Addr);
}
void school::DisplayAllSchool()
{
    if (Head)
    {
        Node *Classrooms = Head;
        student *Students;
        int CounterName = Spasce(1);
        int CounterlD = DigitsSpace();
        int CounterAddress = Spasce(0);
        int NiceLook = CounterName + CounterlD + CounterAddress + 37;
        while (Classrooms)
        {
            Students = Classrooms->t;
            if (Students)
            {
                MakeBreaks(NiceLook, '=');
                cout << "\nClass:[" << Classrooms->ID << "] Student number[" << Classrooms->NoOfStudents << "]\n";
                while (Students)
                {
                    MakeBreaks(NiceLook, '-');
                    cout << "\n";
                    VFXStudents(Students, CounterlD, CounterName, CounterAddress);
                    Students = Students->Next;
                }
            }
            else
            {
                MakeBreaks(NiceLook, '=');

                cout << "\nID Class[ " << Classrooms->ID << " ][ Empty ]!\n";
            }
            MakeBreaks(NiceLook, '=');
            cout << "\n";
            Classrooms = Classrooms->Next;
        }
    }
    else
    {
        cout << "There are no classrooms!\n";
    }
}
void school::VFXStudents(student *Students, int CounterlD, int CounterName, int CounterAddress)
{
    // ID
    cout << "Students id:[ ";
    cout << Students->ID;
    MakeSpasce(CounterlD + 1, MM(Students->ID));
    cout << "]";
    // END ID
    // NAME
    cout << "Name:[ ";
    cout << Students->Name;
    MakeSpasce(CounterName + 1, Students->Name.length());
    cout << "]";
    // END NAME
    // Address
    cout << "Address:[ ";
    cout << Students->Address;
    MakeSpasce(CounterAddress + 1, Students->Address.length());
    cout << "]\n";
    // END Address
}
void DiplayServers()
{
    cout << "\n1.Create a new class";
    cout << "\n2.Reading students' exam scores";
    cout << "\n3.Compute students' average";
    cout << "\n4.New student";
    cout << "\n5.Remove student:";
    cout << "\n6.Remove class";
    cout << "\n7.Alphabetical order";
    cout << "\n8.Maximum average student";
    cout << "\n9.Display student";
    cout << "\n10.Display Class";
    cout << "\n11.Display School";
    cout << "\n12.Exit";
    cout << "\n13.Show the services menu";
    cout << "\n14.Help";
    cout << "\n15.Manual entry ID and information\n";
}
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
void MakeSpasce(int Distance, int Remove)
{
    Distance -= Remove;
    for (int _N = 0; _N < Distance; _N++)
    {
        cout << " ";
    }
}
int main(void)
{
    string Name;
    cout << "Enter the name of the school:";
    getline(cin, Name);
    school Scl(Name);
    int InputUser = 13;
    bool LVL = true;
    string InputUserString = "E:\\Test.txt";
    cout << "\nWelcome to the console School " + Name;
    DiplayServers();
    while (InputUser != 12)
    {
        int UserApp = 0;
        int InputUserApp = 0;
        cin >> InputUser;
        if (Scl.GetStatus() || InputUser == 1)
        {
            switch (InputUser)
            {
            case 1:
                cout << "\nEnter your file path:\n";
                cin.ignore();
                getline(cin, InputUserString);
                Scl.NewClassNode((InputUserString + ".txt"));
                break;
            case 2:

                if (LVL)
                {
                    cout << "1.First.\n";
                    cout << "2.Second.\n";
                    cout << "3.Final\n";
                    cout << "4.else\n";
                    cout << "Choose the exam title:";
                    UserApp = InputFrom2<int>(0, 5);
                    InputUserApp = Scl.DisplayIDClass();
                }
                else
                {
                    cout << "Enter the address of the Class ID\n";
                    cin >> InputUserApp;
                    cout << "Enter the exam ID\n";
                    cin >> UserApp;
                }
                Scl.CertainExam(InputUserApp, UserApp);
                break;
            case 3:
                if (LVL)
                {
                    InputUserApp = Scl.DisplayIDStudents();
                }
                else
                {
                    cout << "Enter the address of the Student ID\n";
                    cin >> InputUserApp;
                }
                cout << Scl.AverageStudent(InputUserApp) << "\n";
                break;
            case 4:
                cin.ignore();
                Scl.AddStudent(Scl.DisplayIDClass(), Scl.StudentData());
                break;
            case 5:
                if (LVL)
                {
                    InputUserApp = Scl.DisplayIDStudents();
                }
                else
                {
                    cout << "Enter the address of the Student ID\n";
                    cin >> InputUserApp;
                }
                Scl.DelStudent(InputUserApp);
                break;
            case 6:
                if (LVL)
                {
                    InputUserApp = Scl.DisplayIDClass();
                }
                else
                {
                    cout << "Enter the address of the Class ID\n";
                    cin >> InputUserApp;
                }
                Scl.DelNode(InputUserApp);
                break;
            case 7:
                if (LVL)
                {
                    InputUserApp = Scl.DisplayIDClass();
                }
                else
                {
                    cout << "Enter the address of the Class ID\n";
                    cin >> InputUserApp;
                }
                Scl.SortStudents(InputUserApp);
                break;
            case 8:
                if (LVL)
                {
                    InputUserApp = Scl.DisplayIDClass();
                }
                else
                {
                    cout << "Enter the address of the Class ID\n";
                    cin >> InputUserApp;
                }
                Scl.MaximumAverage(InputUserApp);

                break;
            case 9:
                cout << "Search using the student's name:";
                cin.ignore();
                getline(cin, InputUserString);
                Scl.DisplayByStudent(InputUserString);
                break;
            case 10:
                Scl.DisplayByClass(Scl.DisplayIDClass());
                break;
            case 11:
                Scl.DisplayAllSchool();
                break;
            case 12:
                return 0;
                break;
            case 13:
                DiplayServers();
                break;
            case 14:
                cout << "Youtube video:https://youtu.be/-S_EcV17qD8";
                break;
            case 15:
                if (LVL)
                {
                    LVL = false;
                    cout << "Deactivate\n";
                }
                else
                {
                    cout << "Activation\n";
                    LVL = true;
                }
                break;
            default:
                cout << "Wrong value,Try again:\n";
                break;
            }
            cout << "\nPress[13] to Show menu:";
        }
        else
        {
            cout << "\nThere are no students and no classes, Press [1] to access the student and classroom contents file.";
        }
    }
}