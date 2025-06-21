#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    int age;
};

vector<Student> students;

void addStudent() {
    Student s;
    cout << "Enter student ID: ";
    cin >> s.id;
    cin.ignore();
    cout << "Enter student name: ";
    getline(cin, s.name);
    cout << "Enter student age: ";
    cin >> s.age;

    students.push_back(s);
    cout << "Student added successfully!\n";
}

void displayStudents() {
    cout << "\n--- All Students ---\n";
    for (const auto& s : students) {
        cout << "ID: " << s.id << ", Name: " << s.name << ", Age: " << s.age << endl;
    }
}

void searchStudent() {
    int searchId;
    cout << "Enter ID to search: ";
    cin >> searchId;

    for (const auto& s : students) {
        if (s.id == searchId) {
            cout << "Student Found: ID: " << s.id << ", Name: " << s.name << ", Age: " << s.age << endl;
            return;
        }
    }
    cout << "Student not found.\n";
}

int main() {
    int choice;

    do {
        cout << "\n--- Student Database Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
