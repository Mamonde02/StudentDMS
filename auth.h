#ifndef AUTH_H
#define AUTH_H
#include <string>

bool login();
bool verifyCredentials(const std::string &inputUser, const std::string &inputPass);
std::string getMaskedPassword();
void registerAdmin();

#endif