#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

struct Student
{
    int id;
    string name;
    int age;
};

// error handling for invalid input
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

// Parse a line into a Student object
Student parseStudent(const string &line)
{
    stringstream ss(line);
    string idStr, name, ageStr;
    getline(ss, idStr, ',');
    getline(ss, name, ',');
    getline(ss, ageStr);

    return {stoi(idStr), name, stoi(ageStr)};
}

// Read all students from file
vector<Student> readAllStudents()
{
    vector<Student> students;
    ifstream inFile("students.txt");
    string line;

    while (getline(inFile, line))
    {
        if (!line.empty())
        {
            students.push_back(parseStudent(line));
        }
    }

    inFile.close();
    return students;
}

// Write all students to file (overwrite)
void writeAllStudents(const vector<Student> &students)
{
    ofstream outFile("students.txt");
    for (const auto &s : students)
    {
        outFile << s.id << "," << s.name << "," << s.age << "\n";
    }
    outFile.close();
}

// Add new student

void addStudent()
{
    vector<Student> students = readAllStudents();
    Student s;

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

// Display all students
void displayStudents()
{
    vector<Student> students = readAllStudents();
    cout << "\n--- All Students ---\n";
    for (const auto &s : students)
    {
        cout << "ID: " << s.id << ", Name: " << s.name << ", Age: " << s.age << endl;
    }
}

// Search student by ID
void searchStudent()
{
    // int searchId = getValidInt("Enter ID to search: ");
    vector<Student> students = readAllStudents();
    Student s;
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
                cout << "Student Found: ID: " << s.id << ", Name: " << s.name << ", Age: " << s.age << endl;
                found = true;
                break;
            }
        }

        if (!found)
            cout << "Student not found with ID: " << s.id << ".\n";
    }
}

// Edit student by ID
void editStudent()
{
    // int editId = getValidInt("Enter ID to edit: ");
    vector<Student> students = readAllStudents();
    Student s;
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

// Delete student by ID
void deleteStudent()
{
    // int deleteId = getValidInt("Enter ID to delete: ");
    vector<Student> students = readAllStudents();
    bool found = false;

    Student s;
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

        vector<Student> updatedStudents;
        for (const auto &s : students)
        {
            if (s.id == stoi(input))
            {
                found = true;
            }
            else
            {
                updatedStudents.push_back(s);
            }
        }

        if (found)
        {
            writeAllStudents(updatedStudents);
            cout << "Student deleted successfully.\n";
        }
        else
        {
            // cout << "Student ID not found.\n";
            cout << "Student not found with ID: " << s.id << ".\n";
        }
    }
}

int main()
{
    int choice;

    do
    {
        cout << "\n--- Student Database Menu ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by ID\n";
        cout << "4. Edit Student by ID\n";
        cout << "5. Delete Student by ID\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            editStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
