#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
#include "../StaticLibrary/functions.h"
#include "../StaticLibrary/front-end.h"
using namespace std;


int main() {
    string address = "../TextFiles(Front-end)/quizPort.txt";
    print(address);
    accountScreen(); //Lets the user log into their account or create a new one. This will save their statistics for the next time they want to use our platform.



    cout << setw(130) << "1. Test Your Knowledge   2. Leaderboard\n";
    cout << setw(119) << "Choose an option: ";
    int userInput;
    cin >> userInput;
    switch (userInput) {
    case 1: {
        clear();
        test();
        break;
    }
    case 2: {
        clear();
        cout << "WIP";
        break;
    }
    }

}
