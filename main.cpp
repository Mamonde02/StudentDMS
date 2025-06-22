#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct Student {
    int id;
    string name;
    int age;
};

// Parse a line into a Student object
Student parseStudent(const string& line) {
    stringstream ss(line);
    string idStr, name, ageStr;
    getline(ss, idStr, ',');
    getline(ss, name, ',');
    getline(ss, ageStr);

    return { stoi(idStr), name, stoi(ageStr) };
}

// Read all students from file
vector<Student> readAllStudents() {
    vector<Student> students;
    ifstream inFile("students.txt");
    string line;

    while (getline(inFile, line)) {
        if (!line.empty()) {
            students.push_back(parseStudent(line));
        }
    }

    inFile.close();
    return students;
}

// Write all students to file (overwrite)
void writeAllStudents(const vector<Student>& students) {
    ofstream outFile("students.txt");
    for (const auto& s : students) {
        outFile << s.id << "," << s.name << "," << s.age << "\n";
    }
    outFile.close();
}

// Add new student
void addStudent() {
    Student s;
    cout << "Enter student ID: ";
    cin >> s.id;
    cin.ignore();
    cout << "Enter student name: ";
    getline(cin, s.name);
    cout << "Enter student age: ";
    cin >> s.age;

    ofstream outFile("students.txt", ios::app);
    outFile << s.id << "," << s.name << "," << s.age << "\n";
    outFile.close();

    cout << "Student added successfully!\n";
}

// Display all students
void displayStudents() {
    vector<Student> students = readAllStudents();
    cout << "\n--- All Students ---\n";
    for (const auto& s : students) {
        cout << "ID: " << s.id << ", Name: " << s.name << ", Age: " << s.age << endl;
    }
}

// Search student by ID
void searchStudent() {
    int searchId;
    cout << "Enter ID to search: ";
    cin >> searchId;

    vector<Student> students = readAllStudents();
    bool found = false;
    for (const auto& s : students) {
        if (s.id == searchId) {
            cout << "Student Found: ID: " << s.id << ", Name: " << s.name << ", Age: " << s.age << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Student not found.\n";
}

// Edit student by ID
void editStudent() {
    int editId;
    cout << "Enter ID to edit: ";
    cin >> editId;

    vector<Student> students = readAllStudents();
    bool found = false;

    for (auto& s : students) {
        if (s.id == editId) {
            cout << "Editing student: " << s.name << endl;
            cin.ignore();
            cout << "Enter new name: ";
            getline(cin, s.name);
            cout << "Enter new age: ";
            cin >> s.age;
            found = true;
            break;
        }
    }

    if (found) {
        writeAllStudents(students);
        cout << "Student record updated.\n";
    } else {
        cout << "Student ID not found.\n";
    }
}

// Delete student by ID
void deleteStudent() {
    int deleteId;
    cout << "Enter ID to delete: ";
    cin >> deleteId;

    vector<Student> students = readAllStudents();
    bool found = false;

    vector<Student> updatedStudents;
    for (const auto& s : students) {
        if (s.id == deleteId) {
            found = true;
        } else {
            updatedStudents.push_back(s);
        }
    }

    if (found) {
        writeAllStudents(updatedStudents);
        cout << "Student deleted successfully.\n";
    } else {
        cout << "Student ID not found.\n";
    }
}

int main() {
    int choice;

    do {
        cout << "\n--- Student Database Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Edit Student by ID\n";
        cout << "5. Delete Student by ID\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: editStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting program.\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
