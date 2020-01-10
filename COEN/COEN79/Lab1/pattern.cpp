//
//  Pattern functionality pattern.cpp
//
//  Display the following pattern using C++ string and setw()
//  0123456789      9876543210  
//      0123456789      9876543210
//          (etc.)
//
//  Lab 1
//
//  Tamir Enkhjargal
//  Santa Clara University
//  January 2020
//

//  Including necessary libraries, iomanip for setw() function
#include <iostream>
#include <iomanip>
using namespace std;

int main(int argc, const char * argv[]) {

    //  Set the strings 0-9 and 9-0
    string first = "0123456789";
    string second = "9876543210";

    //  First line
    cout << first;
    cout << setw(20) << second << endl;

    //  Second line
    cout << setw(12) << first;
    cout << setw(22) << second << endl;

    //  Third line
    cout << setw(14) << first;
    cout << setw(24) << second << endl;

    //  Fourth line
    cout << setw(16) << first;
    cout << setw(26) << second << endl;

    //  Fifth line
    cout << setw(18) << first;
    cout << setw(28) << second << endl;

    return 0;
}

