// lab_9.2_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці

using namespace std;

enum Specialnist { physics, math, programming, pedagogy, numerical_methods };
string specialnistStr[] = { "physics","math", "programming","pedagogy", "numerical_methods" };

struct Student
{
    string surname;
    double GPA;
    Specialnist specialnist;
    unsigned physics;
    unsigned math;
    union
    {
        unsigned prog;
        unsigned numrical_methods;
        unsigned pedagogy;
    };
};

void Create(Student* p, const int N);
void Print(Student* p, const int N);
void SortStudent(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSort(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string surname, const  Specialnist specialnist, const unsigned course);

int main() {
    cout << "N :";
    int N;
    cin >> N;
    Student* p = new Student[N];
    Specialnist specialnist;
    int ispec;
    double GPA;
    string surname;
    int found;
    int menuItem;

    do
    {
        cout << endl << endl << endl;
        cout << "Actions:" << endl << endl;
        cout << " [1] - Create info about student" << endl;
        cout << " [2] - Print info about student" << endl;
        cout << " [3] - Sort student " << endl << endl;
        cout << " [4] - IndexSort student " << endl << endl;
        cout << " [5] - PrintIndexSort student " << endl << endl;
        cout << " [6] - BinSearch student " << endl << endl;
        cout << " [0] - End program" << endl << endl;
        cout << "Choose : "; cin >> menuItem;
        cout << endl << endl << endl;

        switch (menuItem) {
        case 1:
            Create(p, N);
            break;
        case 2:
            Print(p, N);
            break;
        case 3:
            SortStudent(p, N);
            break;
        case 4:
            IndexSort(p, N);
            break;
        case 5:
            PrintIndexSort(p, IndexSort(p, N), N);
            break;
        case 6:
            cout << "Enter key:" << endl;
            cout << " Specialnist (0 - KN, 1 - IT, 2 - WB, 3 - CA, 4 - RI):";
            cin >> ispec;
            specialnist = (Specialnist)ispec;
            cin.get();
            cin.sync();
            cout << " Surname : "; getline(cin, surname);
            cout << endl;
            cout << " GPA: "; cin >> GPA;
            cout << endl;
            found = BinSearch(p, N, surname, specialnist, GPA);
            if (found != -1)
                cout << "Found student  " << found + 1 << endl;
            else
                cout << "No Found" << endl;
            break;
        case 0:
            break;
        default:
            cout << "Try again "
                "Enter a number - the number of the selected menu item" << endl;
        }

    } while (menuItem != 0);


    return 0;
}



void Create(Student* p, const int N)
{
    int specialnist;

    for (int i = 0; i < N; i++)
    {
        cout << "Student № " << i + 1 << ":" << endl;
        cin.get();
        cin.sync();
        cout << " Surname : "; getline(cin, p[i].surname);
        cout << " GPA: "; cin >> p[i].GPA;
        cout << " Specialnist(0 - KN, 1 - IT, 2 - WB, 3 - CA, 4 - RI) :";
        cin >> specialnist;
        cout << " Assessment in physics : "; cin >> p[i].physics;
        cout << "Assessment in math    : "; cin >> p[i].math;
        p[i].specialnist = Specialnist(specialnist);

        switch (p[i].specialnist) {
        case physics:
            cout << "Assessment in programming: "; cin >> p[i].prog;
            break;
        case math:
            cout << "Assessment in numerical methods:"; cin >> p[i].numrical_methods;
            break;
        case programming:
        case pedagogy:
        case numerical_methods:
            cout << "Assessment in pedagogy: "; cin >> p[i].pedagogy;
            break;

        }
        cout << endl;
    }
}


void Print(Student* p, const int N)
{
    cout << "========================================================================================================"
        << endl;
    cout << "| № | Surname | GPA | Spec | Score in PH | Score in MATH | Score in prog | Score in numerical methods | Score in pedagogy |"
        << endl;
    cout << "--------------------------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(1) << right << i + 1 << " ";
        cout << "| " << setw(9) << left << p[i].surname
            << "| " << setw(4) << right << p[i].GPA << " "
            << "| " << setw(14) << left << specialnistStr[p[i].specialnist]
            << "| " << setw(6) << right << p[i].physics << " "
            << "| " << setw(10) << left << p[i].math << " ";
        switch (p[i].specialnist)
        {
        case physics:
            cout << "| " << setw(13) << right << p[i].prog << " " << "|" << setw(14) << "|" << setw(13) << "|";
            break;
        case math:
            cout << "|" << setw(16) << right << fixed << "|" << setw(13) << left << p[i].numrical_methods << "|" << setw(11) << right << " " << " |";
            break;
        case programming:
        case pedagogy:
        case numerical_methods:
            cout << "|" << setw(17) << right << fixed << "| " << setw(12) << left << " " << "| " << setw(11) << right << p[i].pedagogy << "|";
            break;
        }
        cout << endl;
    }
    cout << "=========================================================================================================="
        << endl;
    cout << endl;
}





void SortStudent(Student* p, const int N)
{
    Student temp;
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; i++)
        {
            if ((p[j].specialnist > p[j + 1].specialnist) || (p[j].specialnist == p[j + 1].specialnist && p[j].GPA > p[j + 1].GPA) || (p[j].specialnist == p[j + 1].specialnist && p[j].GPA == p[j + 1].GPA && p[j].surname > p[j + 1].surname))
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;

            }
        }
    }

}


int* IndexSort(Student* p, const int N)
{
    int* I = new int[N];
    for (int i = 0; i < N; i++)
        I[i] = i;
    int i, j, value;
    for (i = 1; i < N; i++)
    {
        value = I[i];
        for (j = i - 1;
            j >= 0 && ((p[I[j]].specialnist > p[value].specialnist) ||
                (p[I[j]].specialnist == p[value].specialnist &&
                    p[I[j]].GPA > p[value].GPA) || (p[I[j]].specialnist == p[value].specialnist && p[I[j]].GPA == p[value].GPA && p[I[j]].surname > p[value].surname));
            j--)
        {
            I[j + 1] = I[j];
        }
        I[j + 1] = value;

    }
    return I;
}



void PrintIndexSort(Student* p, int* I, const int N)
{
    cout << "=========================================================================="
        << endl;
    cout << "| № | Surname | GPA | Spec | Score in PH | Score in MATH | Score in prog | Score in numerical methods | Score in pedagogy |"
        << endl;
    cout << "--------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << setw(1) << right << i + 1 << " ";
        cout << "| " << setw(10) << left << p[I[i]].surname
            << "| " << setw(2) << right << p[I[i]].GPA << " "
            << "| " << setw(15) << left << specialnistStr[p[I[i]].specialnist]
            << "| " << setw(6) << right << p[I[i]].physics << " "
            << "| " << setw(10) << left << p[I[i]].math << " "
            << "| " << setw(6) << right << p[I[i]].numrical_methods << " "
            << "| " << setw(6) << right << p[I[i]].prog << " "
            << "| " << setw(6) << right << p[I[i]].pedagogy << " ";
        cout << endl;
    }
    cout << "=========================================================================="
        << endl;
    cout << endl;
}

int BinSearch(Student* p, const int N, const string surname, const  Specialnist specialnist, const unsigned course)
{

    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;
        if (p[m].surname == surname && p[m].specialnist == specialnist && p[m].GPA == course)
        {
            return m;
        }
        if ((p[m].specialnist < specialnist) || (p[m].GPA < course) || (p[m].specialnist == specialnist && p[m].GPA == course && p[m].surname < surname))
        {
            L = m + 1;
        }
        else
        {
            R = m - 1;
        }
    } while (L <= R);

    return -1;

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
