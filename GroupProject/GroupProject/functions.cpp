#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "functions.h"
using namespace std;


// Function to save accounts to a file
void saveAccounts(const map<std::string, Account>& accounts) {
    ofstream outFile("accounts.txt");
    for (const auto& pair : accounts) {
        outFile << pair.first << " " << pair.second.password << " " << pair.second.number << endl;
    }
    outFile.close();
}

// Function to load accounts from a file
void loadAccounts(map<string, Account>& accounts) {
    ifstream inFile("accounts.txt");
    string username, password;
    int number;

    while (inFile >> username >> password >> number) {
        accounts[username] = { password, number };
    }
    inFile.close();
}

void accountScreen() {
    map<string, Account> accounts;
    loadAccounts(accounts); // Load existing accounts

    string username, password;
    int number;
    char choice;

    cout << "1. Create Account\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice) {
    case '1': // Create an account
        cout << "Enter username: ";
        cin >> username;
        if (accounts.find(username) != accounts.end()) {
            cout << "Error: Account with this username already exists!\n";
            accountScreen();
            break;
        }
        else {
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter a number: ";
            cin >> number;

            accounts[username] = { password, number };
            saveAccounts(accounts); // Save accounts whenever a new account is created
            cout << "Account created successfully!\n";
            accountScreen();
            break;
        }

    case '2': // Login
        cout << "Enter username: ";
        cin >> username;
        if (accounts.find(username) == accounts.end()) {
            cout << "Error: No account found with this username!\n";
            accountScreen();
            break;
        }
        else {
            cout << "Enter password: ";
            cin >> password;
            if (accounts[username].password == password) {
                cout << "Login successful!\n";
                cout << "Number associated with this account: " << accounts[username].number << "\n";
                accountScreen();
                break;
            }
            else {
                cout << "Error: Incorrect password!\n";
                accountScreen();
                break;
            }
        }
        break;

    case '3': // Exit
        cout << "Exiting program...\n";
        break;

    default:
        cout << "Invalid choice. Please enter a valid option.\n";
        accountScreen();
        break;
    }
}
