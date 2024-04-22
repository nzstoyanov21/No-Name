#pragma once

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <map>
#include <string>

// Structure to hold account information
struct Account {
    std::string password;
    int highScore=0;
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

#endif