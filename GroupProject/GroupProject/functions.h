#pragma once

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <map>
#include <string>

// Structure to hold account information
struct Account {
    std::string password;
    int number;
};

// Function declarations
void saveAccounts(const std::map<std::string, Account>& accounts);
void loadAccounts(std::map<std::string, Account>& accounts);
void accountScreen();
#endif