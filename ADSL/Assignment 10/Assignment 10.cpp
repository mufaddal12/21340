#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class Student
{
    int roll;
    char name[20];
    char div;
    char add[20];

public:
    void input();
    void display();
    int getRoll() { return roll; }
};

void Student::input()
{
    cout << "Roll     : ";
    cin >> roll;
    cout << "Name     : ";
    cin.ignore();
    cin.getline(name, 20);
    cout << "Division : ";
    cin >> div;
    cout << "Address  : ";
    cin.ignore();
    cin.getline(add, 20);
}

void Student::display()
{
    cout << "Roll     : " << roll << endl;
    cout << "Name     : " << name << endl;
    cout << "Division : " << div << endl;
    cout << "Address  : " << add << endl;
    cout << endl;
}

void write(Student s, string fname = "Student.dat")
{
    fstream fout(fname, ios::binary | ios::app);
    fout.write((char *)&s, sizeof(s));
    fout.close();
}

void displayRecs()
{
    fstream fin("Student.dat", ios::binary | ios::in);
    Student s;
    while (fin.read((char *)&s, sizeof(s)))
    {
        s.display();
    }
}

void searchRec(int roll)
{
    fstream fin("Student.dat", ios::binary | ios::in);
    Student s;
    bool flag = false;
    while (fin.read((char *)&s, sizeof(s)) && !flag)
    {
        if (roll == s.getRoll())
        {
            flag = true;
            break;
        }
    }
    fin.close();
    if (flag)
        s.display();
    else
        cout << "No record of roll " << roll << " found\n";
}

void deleteRec(int roll)
{
    fstream fin("Student.dat", ios::binary | ios::in);
    Student s;
    bool flag = false;
    while (fin.read((char *)&s, sizeof(s)) && !flag)
    {
        if (roll != s.getRoll())
        {
            write(s, "temp.dat");
        }
    }
    remove("Student.dat");
    rename("temp.dat", "Student.dat");
}

int main()
{
    Student s;
    int op;
    int roll;
    do
    {
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search for Object\n";
        cout << "4. Display all Objects\n";
        cout << "0. Exit\n";
        cout << "  Option : ";
        cin >> op;
        cout << endl;
        switch (op)
        {
        case 1:
            s.input();
            write(s);
            break;
        case 2:
            cout << " Roll : ";
            cin >> roll;
            cout << endl;
            deleteRec(roll);
            break;
        case 3:
            cout << " Roll : ";
            cin >> roll;
            cout << endl;
            searchRec(roll);
            break;
        case 4:
            displayRecs();
            break;
        }
        cout << endl;
    } while (op);

    return 0;
}