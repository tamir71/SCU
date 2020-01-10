//
//  Convert functionality convert.cpp
//
//  "Convert to uppercase and display all the words from an input file with length of at least 10 characters. All punctuation marks are removed and do not contribute to the words' length. The name of the file to be read should be read in as a command line argument."
//
//  Lab 1
//
//  Tamir Enkhjargal
//  Santa Clara University
//  January 2020
//

//  Including necessary libraries. fstream for file functionality

#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, const char * argv[]) {

    //  Checking for file name input
    if(argc != 2) {
        cout << "Please enter a text file. Usage ./convert text.txt\n";
        return 1;
    }
    
    //  Creating variables, and bringing in file name
    string tempstring;
    string word = "";
    string filename(argv[1]);

    //  Creating a file pointer and opening file
    ifstream in_file;
    in_file.open(filename);
    
    //  While the file pointer has not hit EOF
    while(in_file && in_file.peek() != EOF) {
        word = "";
        in_file >> tempstring;                          //  Take word from in_file into tempstring
        for(int i = 0; i < tempstring.length(); i++) {  //  Parse through the word, by each character
            if(isalnum(tempstring[i])) {                //  Check if actually a letter/number
                word += toupper(tempstring[i]);         //  Add to word and set to upper
            }
        }
        if(word.length() >= 10) {                       //  If the total word is 10 characters+
            cout << word << endl;                       //  Print word
        }
    }

    return 0;
}

