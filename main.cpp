#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "auth.h"
using namespace std;

// Color codes for terminal output
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

// Function to get a masked password input
// This function will not echo the characters typed by the user
#ifdef _WIN32
#include <conio.h> // For getch() on Windows
#else
#include <termios.h>
#include <unistd.h>
char getch()
{
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

// string getMaskedPassword() // auth.cpp
// {
//     string password;
//     char ch;

//     while ((ch = getch()) != '\r')
//     { // Enter key in Windows
//         if (ch == '\b')
//         { // Handle backspace
//             if (!password.empty())
//             {
//                 password.pop_back();
//                 cout << "\b \b";
//             }
//         }
//         else
//         {
//             password += ch;
//             cout << '*';
//         }
//     }
//     cout << endl;
//     return password;
// }

struct Student
{
    int id;
    string name;
    int age;
};

// void registerAdmin() // auth.cpp
// {
//     string username, password;

//     cout << "\n--- Register New Admin ---\n";
//     cout << "Enter new username: ";
//     cin >> username;
//     cout << "Enter new password: ";
//     cin >> password;

//     ofstream file("admins.txt", ios::app);
//     file << username << "," << password << "\n";
//     file.close();

//     cout << "New admin account created.\n";
// }

// bool verifyCredentials(const string &inputUser, const string &inputPass) // auth.cpp
// {
//     ifstream file("admins.txt");
//     if (!file)
//     {
//         cout << "Cannot open admins.txt\n";
//         return false;
//     }

//     string line;
//     while (getline(file, line))
//     {
//         size_t commaPos = line.find(',');
//         if (commaPos == string::npos)
//             continue;

//         string fileUser = line.substr(0, commaPos);
//         string filePass = line.substr(commaPos + 1);

//         if (inputUser == fileUser && inputPass == filePass)
//         {
//             return true;
//         }
//     }

//     return false;
// }

// bool login() //
// {
//     string username;
//     int attempts = 3;

//     cout << "=============================\n";
//     cout << BLUE << "  Admin Login System\n";
//     cout << RESET;
//     cout << "=============================\n";
//     cout << "New admin? press 1 to Register here.\n";
//     cout << "1. Register New Admin\n";
//     cout << "2. Login with Existing Admin\n";
//     cout << "Enter your choice (1 or 2): ";
//     int choice;
//     cin >> choice;

//     if (choice == 1)
//     {
//         registerAdmin();
//         return true;
//     }
//     else if (choice != 2)
//     {
//         cout << "Invalid choice. Exiting...\n";
//         return false;
//     }

//     while (attempts > 0)
//     {
//         // initial back..
//         int backOption;
//         cout << "\n--- Admin Login ---\n";
//         cout << "Type 'back' or '0' to return to the main menu.\n";

//         cout << "Enter username: ";
//         cin >> username || backOption;

//         cout << "Enter password: ";
//         string password = getMaskedPassword();
//         // cin >> password;

//         if (backOption == 0 || username == "back")
//         {
//             cout << "Returning to main menu...\n";
//             return false;
//         }

//         if (verifyCredentials(username, password))
//         {
//             cout << GREEN << "\nLogin successful!\n"
//                  << RESET;
//             return true;
//         }
//         else
//         {
//             attempts--;
//             cout << RED << "\nInvalid credentials. You have " << attempts << " attempts left.\n"
//                  << RESET;
//             if (attempts == 0)
//             {
//                 cout << RED << "Too many failed attempts. Exiting...\n"
//                      << RESET;
//                 return false;
//             }
//         }
//     }

//     return false;
// }

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
    if (!login())
    {
        cout << "\nExiting...\n";
        return 0;
    }

    int choice;

    do
    {
        cout << GREEN << "\n--- Student Database Menu ---\n"
             << RESET << endl;
        cout << RED << "1. Add Student\n"
             << RESET;
        cout << BLUE << "2. Display All Students\n"
             << RESET;
        cout << YELLOW << "3. Search Student by ID\n";
        cout << RESET;
        cout << GREEN << "4. Edit Student by ID\n";
        cout << RESET;
        cout << RED << "5. Delete Student by ID\n";
        cout << RESET;
        cout << GREEN << "6. Exit\n";
        cout << RESET;
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
            // cout << "Invalid choice. Try again.\n";
            cout << "Invalid choice. Press enter to continue...\n";
            cin.ignore();
            cin.get();
        }
    } while (choice != 6);

    return 0;
}
