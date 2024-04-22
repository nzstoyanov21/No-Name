#pragma once

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <map>
#include <string>
#include <vector>

// Structure to hold account information
struct Account {
    std::string password;
    int highScore = 0;
    std::string username;
};

// Function declarations
void saveAccounts(const std::map<std::string, Account>& accounts);

void loadAccounts(std::map<std::string, Account>& accounts);

void accountScreen();

int random(int min, int max);

void shuffle(char arr[], std::string array[][3], int arrsize);

void questions(std::string questions[][3], char answers[], int& score, int numberOfQuestions, int points);

void clear();

void test();

bool compare(const Account& a, const Account& b);

void sortAccounts(const std::map<std::string, Account>& accounts, std::vector<Account>& sortedAccounts);

void statistics();

void loggedIn();
#endif
