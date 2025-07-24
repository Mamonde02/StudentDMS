#include <iostream>
#include <fstream>
#include <vector>
#include "utils.h"
#include <sstream>
#include <string>

using namespace std;

void displayMenu(int &choice)
{
    cout << GREEN << "\n--- Student Database Menu from utils ---\n"
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
}
