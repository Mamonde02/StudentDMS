// student.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include "student.h"
#include <sstream>
#include <string>

using namespace std;

int getValidInt(const string &prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        cin >> value;
        if (!cin.fail())
        {
            cin.ignore(); // clear newline from buffer
            return value;
        }
        else
        {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();             // clear error flag
            cin.ignore(10000, '\n'); // discard invalid input
        }
    }
}

void writeAllStudents(const vector<Studentfrom> &students) //
{
    ofstream outFile("students.txt");
    for (const auto &s : students)
    {
        outFile << s.id << "," << s.name << "," << s.age << "\n";
    }
    outFile.close();
}

Studentfrom parseStudentfromstudent(const string &line)
{
    stringstream ss(line);
    string idStr, name, ageStr;
    getline(ss, idStr, ',');
    getline(ss, name, ',');
    getline(ss, ageStr);

    return {stoi(idStr), name, stoi(ageStr)};
}

// Read all students from file
vector<Studentfrom> readAllStudentsfromstudent()
{
    vector<Studentfrom> students;
    ifstream inFile("students.txt");
    string line;

    while (getline(inFile, line))
    {
        if (!line.empty())
        {
            students.push_back(parseStudentfromstudent(line));
        }
    }

    inFile.close();
    return students;
}

void displayStudents()
{
    vector<Studentfrom> students = readAllStudentsfromstudent();
    cout << "\n--- All Students from student.cpp file ---\n";
    for (const auto &s : students)
    {
        cout << "ID: " << s.id << ", Name: " << s.name << ", Age: " << s.age << endl;
    }
}

void addStudents()
{
    vector<Studentfrom> students = readAllStudentsfromstudent();
    Studentfrom s;

    string input;

    // ID input with 'back' option
    while (true)
    {
        cout << "Enter student ID (or type 'back' to return): from student.cpp file\n";
        cin >> input;
        if (input == "back" || input == "0")
            return;

        try
        {
            s.id = stoi(input);
        }
        catch (...)
        {
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        // Check for duplicate ID
        bool duplicate = false;
        for (const auto &student : students)
        {
            if (student.id == s.id)
            {
                cout << "A student with this ID already exists.\n";
                duplicate = true;
                break;
            }
        }

        if (!duplicate)
            break;
    }
    //

    cin.ignore(); // Clear newline after entering ID

    // Name input
    while (true)
    {
        cout << "Enter student name (or type 'back' to return): ";
        getline(cin, s.name);
        if (s.name == "back" || s.name == "0")
            return;
        if (!s.name.empty())
            break;
        cout << "Name cannot be empty.\n";
    }

    // Age input
    while (true)
    {
        cout << "Enter student age (or type 'back' to return): ";
        cin >> input;
        if (input == "back" || input == "0")
            return;

        try
        {
            s.age = stoi(input);
            if (s.age < 1 || s.age > 120)
                throw out_of_range("Invalid age");
            break;
        }
        catch (...)
        {
            cout << "Please enter a valid age between 1 and 120.\n";
        }
    }

    // Save student to file
    ofstream outFile("students.txt", ios::app);
    outFile << s.id << "," << s.name << "," << s.age << "\n";
    outFile.close();

    cout << "Student added successfully!\n";
}

void searchStudents()
{
    // int searchId = getValidInt("Enter ID to search: ");
    vector<Studentfrom> students = readAllStudentsfromstudent();
    Studentfrom s;
    string input;

    // ID input with 'back' option
    while (true)
    {
        cout << "Enter student ID (or type 'back' to return): ";
        cin >> input;
        if (input == "back" || input == "0")
            return;

        try
        {
            s.id = stoi(input);
        }
        catch (...)
        {
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        bool found = false;
        for (const auto &s : students)
        {
            if (s.id == stoi(input))
            {
                cout << "Student Found: ID: from student.cpp file" << s.id << ", Name: " << s.name << ", Age: " << s.age << endl;
                found = true;
                break;
            }
        }

        if (!found)
            cout << "Student not found with ID: " << s.id << ".\n";
    }
}

void editStudents() //
{
    // int editId = getValidInt("Enter ID to edit: ");
    vector<Studentfrom> students = readAllStudentsfromstudent();
    Studentfrom s;
    string input;

    // ID input with 'back' option
    while (true)
    {
        cout << "Enter student ID (or type 'back' to return): from student.cpp file\n";
        cin >> input;
        if (input == "back" || input == "0")
            return;

        try
        {
            s.id = stoi(input);
        }
        catch (...)
        {
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }
        bool found = false;

        for (auto &s : students)
        {
            if (s.id == stoi(input))
            {
                cout << "Editing student: " << s.name << endl;
                cout << "Enter new name: ";
                getline(cin, s.name);
                while (s.name.empty())
                {
                    cout << "Name cannot be empty. Enter new name: ";
                    getline(cin, s.name);
                }

                s.age = getValidInt("Enter new age: ");
                while (s.age < 1 || s.age > 120)
                {
                    cout << "Age must be between 1 and 120.\n";
                    s.age = getValidInt("Enter new age: ");
                }

                found = true;
                break;
            }
        }

        if (found)
        {
            writeAllStudents(students);
            cout << "Student record updated.\n";
        }
        else
        {
            // cout << "Student ID not found in the database.\n";
            cout << "Student not found with ID: " << s.id << ".\n";
        }
    }
}
