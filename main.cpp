#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    int age;
};

// Save a student to the file
void saveStudentToFile(const Student& s) {
    ofstream outFile("students.txt", ios::app); // append mode
    if (outFile.is_open()) {
        outFile << s.id << "," << s.name << "," << s.age << "\n";
        outFile.close();
        cout << "Student saved to file successfully!\n";
    } else {
        cout << "Failed to open file.\n";
    }
}

// Add a new student and save to file
void addStudent() {
    Student s;
    cout << "Enter student ID: ";
    cin >> s.id;
    cin.ignore();
    cout << "Enter student name: ";
    getline(cin, s.name);
    cout << "Enter student age: ";
    cin >> s.age;

    saveStudentToFile(s);
}

// Read and display all students from file
void displayStudents() {
    ifstream inFile("students.txt");
    string line;
    cout << "\n--- All Students ---\n";
    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.rfind(',');
        if (pos1 != string::npos && pos2 != string::npos) {
            string id = line.substr(0, pos1);
            string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string age = line.substr(pos2 + 1);
            cout << "ID: " << id << ", Name: " << name << ", Age: " << age << endl;
        }
    }
    inFile.close();
}

// Search a student by ID from file
void searchStudent() {
    ifstream inFile("students.txt");
    int searchId;
    cout << "Enter ID to search: ";
    cin >> searchId;

    string line;
    bool found = false;
    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.rfind(',');
        if (pos1 != string::npos && pos2 != string::npos) {
            int id = stoi(line.substr(0, pos1));
            string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string age = line.substr(pos2 + 1);

            if (id == searchId) {
                cout << "Student Found: ID: " << id << ", Name: " << name << ", Age: " << age << endl;
                found = true;
                break;
            }
        }
    }
    if (!found) {
        cout << "Student not found.\n";
    }
    inFile.close();
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
