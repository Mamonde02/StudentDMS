// student.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include "student.h"
#include <sstream>
#include <string>

using namespace std;

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
