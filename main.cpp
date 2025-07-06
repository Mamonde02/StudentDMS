#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "auth.h"
#include "student.h"
using namespace std;

// Color codes for terminal output
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

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
            addStudents();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            searchStudents();
            break;
        case 4:
            editStudents();
            break;
        case 5:
            deleteStudents();
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
