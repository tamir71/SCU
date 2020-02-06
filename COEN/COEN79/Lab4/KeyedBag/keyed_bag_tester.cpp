//
//  COEN 79
//  --- Behnam Dezfouli, COEN, SCU ---
//

#include <iostream>
#include "keyed_bag.h"

using namespace std;
using coen79_lab4::keyed_bag;

void Insert(const int val, const string& key, keyed_bag& kb) {
    cout << "Inserting "<<val<<" with key \""<<key<<"\"." << endl;
    kb.insert(val, key);
}

void Erase(const string& key, keyed_bag& kb) {
    cout << "Erasing \""<< key <<"\"." << endl;
    kb.erase(key);
}

void Get(const string & key, const keyed_bag& kb) {
    cout << "Value for \""<<key<<"\": " << kb.get(key) << endl;
}

void Has(const string & key, const keyed_bag& kb) {
    cout << "Has "<<key<<": " << kb.has_key(key) << endl;
}

void Count(const int val, const keyed_bag& kb) {
    cout << "Number of "<< val <<"'s in the bag: " << kb.count(val) << endl;
}

void bSize(const keyed_bag& kb) {
    cout << "Bag size: " << kb.size() << endl;
}

int main(int argc, char const *argv[]) {
    keyed_bag kb1, kb2;

    Insert(5,"five",kb1);
    Insert(3,"three",kb1);
    Insert(1,"one",kb1);
    Get("one", kb1);
    Get("three", kb1);
    Get("five", kb1);
    Has("five", kb1);
    Has("two", kb1);
    bSize(kb1);
    Erase("five", kb1);
    bSize(kb1);
    Has("five", kb1);
    Has("three", kb1);
    Insert(-8, "neg_eight", kb1);
    bSize(kb1);
    Has("neg_eight", kb1);
    Get("neg_eight", kb1);
    Count(9, kb1);
    Count(1, kb1);
    Insert(1, "ONE", kb1);
    Count(1, kb1);
    Insert(7,"seven",kb1);
    Insert(9,"nine",kb1);
    Insert(11,"eleven",kb1);
    bSize(kb1);
    Erase("eleven",kb1);
    bSize(kb1);
    Erase("ONE",kb1);
    bSize(kb1);

    // Do some stuff with bag 2.
    Insert(1,"1",kb2);
    Insert(2,"2",kb2);
    Insert(3,"3",kb2);
    Insert(4,"4",kb2);
    Insert(5,"5",kb2);

    // Testing add.
    keyed_bag kb3;
    kb3 = kb1+kb2;
    bSize(kb3);
    Has("1",kb3);
    Has("one",kb3);
    Has("turkey",kb3);
    Count(1,kb3);
    Count(9,kb3);
    Count(-5,kb3);
    Get("three",kb3);
    cout << "Erasing all of kb2." << endl;
    kb2.erase();
    bSize(kb2);
    Insert(22,"I'm feelin'", kb2);
    Get("I'm feelin'", kb2);

    return 0;
}
