#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <sstream>
#include "auth.h"

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

string getMaskedPassword() // auth.cpp
{
    string password;
    char ch;

    while ((ch = getch()) != '\r')
    { // Enter key in Windows
        if (ch == '\b')
        { // Handle backspace
            if (!password.empty())
            {
                password.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

void registerAdmin() // auth.cpp
{
    string username, password;

    cout << "\n--- Register New Admin ---\n";
    cout << "Enter new username: ";
    cin >> username;
    cout << "Enter new password: ";
    cin >> password;

    ofstream file("admins.txt", ios::app);
    file << username << "," << password << "\n";
    file.close();

    cout << "New admin account created.\n";
}

bool verifyCredentials(const string &inputUser, const string &inputPass) // auth.cpp
{
    ifstream file("admins.txt");
    if (!file)
    {
        cout << "Cannot open admins.txt\n";
        return false;
    }

    string line;
    while (getline(file, line))
    {
        size_t commaPos = line.find(',');
        if (commaPos == string::npos)
            continue;

        string fileUser = line.substr(0, commaPos);
        string filePass = line.substr(commaPos + 1);

        if (inputUser == fileUser && inputPass == filePass)
        {
            return true;
        }
    }

    return false;
}

bool login() // auth.cpp
{
    string username;
    int attempts = 3;

    cout << "=============================\n";
    cout << BLUE << "  Admin Login System\n";
    cout << RESET;
    cout << "=============================\n";
    cout << "New admin? press 1 to Register here.\n";
    cout << "1. Register New Admin\n";
    cout << "2. Login with Existing Admin\n";
    cout << "Enter your choice (1 or 2): ";
    int choice;
    cin >> choice;

    if (choice == 1)
    {
        registerAdmin();
        return true;
    }
    else if (choice != 2)
    {
        cout << "Invalid choice. Exiting...\n";
        return false;
    }

    while (attempts > 0)
    {
        // initial back..
        int backOption;
        cout << "\n--- Admin Login ---\n";
        cout << "Type 'back' or '0' to return to the main menu.\n";

        cout << "Enter username: ";
        cin >> username || backOption;

        cout << "Enter password: ";
        string password = getMaskedPassword();
        // cin >> password;

        if (backOption == 0 || username == "back")
        {
            cout << "Returning to main menu...\n";
            return false;
        }

        if (verifyCredentials(username, password))
        {
            cout << GREEN << "\nLogin successful!\n"
                 << RESET;
            return true;
        }
        else
        {
            attempts--;
            cout << RED << "\nInvalid credentials. You have " << attempts << " attempts left.\n"
                 << RESET;
            if (attempts == 0)
            {
                cout << RED << "Too many failed attempts. Exiting...\n"
                     << RESET;
                return false;
            }
        }
    }

    return false;
}