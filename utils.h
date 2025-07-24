#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[0m"

void displayMenu(int &choice);
int getValidInt(const std::string &prompt);

#endif
