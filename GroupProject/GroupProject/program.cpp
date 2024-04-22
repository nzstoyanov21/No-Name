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
    loggedIn();
    }

