#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;


void print(string str)
{
    fstream newfile;

    newfile.open(str, ios::in);
    if (newfile.is_open()) {
        string tp;
        while (getline(newfile, tp)) {
            cout << tp << endl;
        }
        newfile.close();
    }
}