//
//  Counter functionality counter.cpp
//
//  "Count the number of alphanumeric characters and non-alphanumeric characters from the standard input (cin). Spaces (' ') should not be counted toward either type of character."
//
//  Lab 1
//
//  Tamir Enkhjargal
//  Santa Clara University
//  January 2020
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {

    //  Setting variables, alphacount for alphanumeric characters, nonalcount for non-alphanumeric chars
    string sentence = "";
    int alphacount = 0;
    int nonalcount = 0;

    //  Prompt user for a new string
    cout << "Enter a string\n";
    //  Get the full string/sentence and input to sentence variable
    getline(cin, sentence);

    //  For loop that loops character by character
    for(int i = 0; i < sentence.length(); i++) {
        if(sentence[i] != ' ') {                    // 'Delimiting' space character
            if(isalnum(sentence[i])) {              //  If alphanumeric, alphcount++
                alphacount++;
            }
            else {                                  //  If non-alphanumeric, nonalcount++
                nonalcount++;
            }
        }
    }
    
    //  Print out sentence + alphacount + nonalcount
    cout << sentence << " has " << alphacount << " alphanumeric characters and " << nonalcount << " non-alphanumeric characters\n";

    return 0;
}

