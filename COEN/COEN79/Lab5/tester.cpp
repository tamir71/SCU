// FILE: main.cpp
// To test string class
//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//

#include <iostream>
#include "mystring.h"

using std::cout;
using std::cin;
using std::endl;
using coen79_lab5::string;

std::string boolString(bool b) {
	return (b) ? "true" : "false";
}

int main(int argc, char const *argv[]) {
	string s1, s2("Hello, World!"), s3(s2);
     cout << "s1: " << s1 << endl;
     cout << "s2: " << s2 << endl;
     cout << "s3: " << s3 << endl;
    
     cout << "*** += operator tests ***" << endl;
     cout << "s1 length: " << s1.length() << endl;
     s1 += string("A");
     cout << "s1: " << s1 << endl;
     cout << "s1 length: " << s1.length() << endl;
     s1 += "B";
     cout << "s1: " << s1 << endl;
     cout << "s1 length: " << s1.length() << endl;
     s1 += 'C';
     cout << "s1: " << s1 << endl;
     cout << "s1 length: " << s1.length() << endl;
    
     cout << "*** [] operator test ***" << endl;
     cout << "s1[0]: " << s1[0] << endl;
     cout << "s1[1]: " << s1[1] << endl;
     cout << "s1[2]: " << s1[2] << endl;
    
     cout << "*** = operator test ***" << endl;
     s2 = string("= Test 1 Success");
     cout << "s2: " << s2 << endl;
     cout << "s2: " << (s2 = string("= Test 2 Success")) << endl;
    
     string A("A"), B("B");
     cout << "*** logical operator tests ***" << endl;
     cout << "A == A: " << boolString(A == A) << endl;
     cout << "A == B: " << boolString(A == B) << endl;
     cout << "A != A: " << boolString(A != A) << endl;
     cout << "A != B: " << boolString(A != B) << endl;
     cout << "A > A: " << boolString(A > A) << endl;
     cout << "A > B: " << boolString(A > B) << endl;
     cout << "B > A: " << boolString(B > A) << endl;
     cout << "A >= A: " << boolString(A >= A) << endl;
     cout << "A >= B: " << boolString(A >= B) << endl;
     cout << "B >= A: " << boolString(B >= A) << endl;
     cout << "A < A: " << boolString(A < A) << endl;
     cout << "A < B: " << boolString(A < B) << endl;
     cout << "B < A: " << boolString(B < A) << endl;
     cout << "A <= A: " << boolString(A <= A) << endl;
     cout << "A <= B: " << boolString(A <= B) << endl;
     cout << "B <= A: " << boolString(B <= A) << endl;
    
     cout << "*** + operator tests ***" << endl;
     cout << "A + B: " << (A + B) << endl;
     cout << "A + C: " << (A + "C") << endl;
     cout << "B + A: " << (B + A) << endl;

     cout << "*** >> operator test ***" << endl;
     cout << "Please enter a word: ";
     cin >> s1;
     cout << "You entered: " << s1 << endl;

	// Testing new functions.

	// Character constructor test.
	cout << "*** Single character constructor test ***" << endl;
	string C('C');
	cout << "C: " << C << endl;
	// Insertion tests.
	cout << "*** insert tests ***" << endl;
	s1 = "ABCD";
	cout << "s1: " << s1 << endl;
	s1.insert("-",0);
	cout << "s1: " << s1 << endl;
	s1.insert("*",3);
	cout << "s1: " << s1 << endl;
	s1.insert(".",s1.length());
	cout << "s1: " << s1 << endl;
	// Deleteion tests.
	cout << "*** dlt tests ***" << endl;
	s1 = "1112233445555";
	cout << "s1: " << s1 << endl;
	s1.dlt(0,3);
	cout << "s1: " << s1 << endl;
	s1.dlt(2,2);
	cout << "s1: " << s1 << endl;
	s1.dlt(s1.length()-4,4);
	cout << "s1: " << s1 << endl;
	// Replace test
	cout << "*** replace tests ***" << endl;
	s1 = "abc";
	cout << "s1: " << s1 << endl;
	s1.replace('z',0);
	cout << "s1: " << s1 << endl;
	s1.replace('y',1);
	cout << "s1: " << s1 << endl;
	s1.replace('x',2);
	cout << "s1: " << s1 << endl;
	s1 = "ABCDEFGHIJKLMNOP";
	s2 = "123";
	s1.replace(s2, 0);
	cout << "s1: " << s1 << endl;
	s1.replace(s2, 5);
	cout << "s1: " << s1 << endl;
	s1.replace(s2, s1.length() - s2.length());
	cout << "s1: " << s1 << endl;

	cout << "*** count tests ***" << endl;
	s1 = "ABBCCCDDDD";
	cout << "s1: " << s1 << endl;
	cout << "Num A's: " << s1.count('A') << endl;
	cout << "Num B's: " << s1.count('B') << endl;
	cout << "Num C's: " << s1.count('C') << endl;
	cout << "Num D's: " << s1.count('D') << endl;
	cout << "Num E's: " << s1.count('E') << endl;

	cout << "*** search tests ***" << endl;
	cout << "s1: " << s1 << endl;
	cout << "First A: " << s1.search('A') << endl;
	cout << "First B: " << s1.search('B') << endl;
	cout << "First C: " << s1.search('C') << endl;
	cout << "First D: " << s1.search('D') << endl;
	cout << "First E: " << s1.search('E') << endl;
	s1 = "ABCDEFGHIJKLMNOP";
	cout << "s1: " << s1 << endl;
	cout << "Location of \"ABC\": " << s1.search(string("ABC")) << endl;
	cout << "Location of \"GHI\": " << s1.search(string("GHI")) << endl;
	cout << "Location of \"NOP\": " << s1.search(string("NOP")) << endl;
	cout << "Location of \"XYZ\": " << s1.search(string("XYZ")) << endl;

	return 0;
}
