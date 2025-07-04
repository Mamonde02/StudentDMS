#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

struct Studentfrom
{
    int id;
    std::string name;
    int age;
};

// Function declarations
Studentfrom parseStudentfromstudent(const std::string &line);
std::vector<Studentfrom> readAllStudentsfromstudent();
void writeAllStudents(const std::vector<Studentfrom> &students);
void displayStudents();
void addStudents();
void searchStudents();

#endif
