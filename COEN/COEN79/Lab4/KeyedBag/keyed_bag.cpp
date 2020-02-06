//
//  keyed_bag.cpp
//  Lab 4
//
//  Created by tenkhjar on 1/30/20
//  Copyright 2020 SCU. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <cstdlib>      // Provides size_t declaration
#include <cmath>
#include "keyed_bag.h"

using namespace std;

namespace coen79_lab4 {

    // Constructor: initializes an empty keyed_bag
    keyed_bag::keyed_bag() {
        for(int i = 0; i < CAPACITY; i++) {
            keys[i] = '\0';
            data[i] = NULL;
        }
        used = 0;       
    }

    // Empties all data and keys
    void keyed_bag::erase() {
        for(int i = 0; i < used; i++) {             // Iterate from 0 to used
            keys[i] = '\0';                         // reset keys
            data[i] = NULL;                         // reset data
        }
        used = 0;                                   // then used = 0
    }
    
    // Search for a key, then delete data and key [true], or don't find anything [false]
    bool keyed_bag::erase(const key_type& key) {
        assert(used > 0);                           // Check if array is not empty
        for(int i = 0; i < used; i++) {             // Loop through array
            if(keys[i] == key) {                    // If we find the key
                for(int j = i; j < used-1 ; j++) {  // Loop through and shift array left by one
                    keys[j] = keys[j+1];            // Left key     <--     Right key
                    data[j] = data[j+1];            // Left data    <--     Right data
                }
                used--;
                return true;                        // Return true if we found a key
            }
        }
        return false;                               // Return false if we didn't find key value
    }
    
    // A new copy of entry has been added to data[] and corresponding key to key[]
    void keyed_bag::insert(const value_type& entry, const key_type& key) {
        assert((size() < CAPACITY) && (has_key(key) == false));     // Check if key doesn't exist already
        keys[used] = key;                           // If key doesn't exist, then put to end of arrays
        data[used] = entry;                         //     key[] and data[]
        used++;
    }
    
    // Each item and key in addend bag has been added to `this` bag
    void keyed_bag::operator+=(const keyed_bag& addend) {
        assert(size() + addend.size() <= CAPACITY);                 // Check if both bags don't exceed CAPACITY
        for(int i = 0; i < addend.used; i++) {      // Iterate through addend
            if( !has_key(addend.keys[i]) ) {        // Check if key in addend doesn't exist in `this` bag
                keys[used] = addend.keys[i];        // If doesn't exist, then add the data from addend
                data[used] = addend.data[i];        //     to end of `this` bag's data[] and key[]
                used++;
            }
        }
    }

    // Return if the desired key exists or not
    bool keyed_bag::has_key(const key_type& key) const {
        for(int i = 0; i < used; i++) {             // Iterate through 0 to used
            if(keys[i] == key) {                    // If we find a match in keys
                return true;                        // Return true
            }
        }
        return false;                               // If we don't find, return false
    }
    
    // Returns data value corresponding to given key
    keyed_bag::value_type keyed_bag::get(const key_type& key) const {
        assert(has_key(key));                       // First check if key exists
        for(int i = 0; i < used; i++) {             // Iterate through 0 to used  
            if(keys[i] == key) {                    // If we find the key
                return data[i];                     // Return the data at i
            }
        }
        return NULL;                                
    }
    
    // Returns total number of items in `this` bag
    keyed_bag::size_type keyed_bag::size() const {
        return used;
    }

    // Returns total number of times target is in data[]
    keyed_bag::size_type keyed_bag::count(const value_type& target) const {
        size_type count = 0;                        // Temporary counter
        for(int i = 0; i < used; i++) {             // Iterate from 0 to used
            if(data[i] == target) {                 // If we find target in data[]
                count++;                            // increment count
            }
        }
        return count;
    }
    
    // Checks if there is any duplicate key in another bag `otherBag`
    bool keyed_bag::hasDuplicateKey(const keyed_bag& otherBag) const {
        for(int i = 0; i < otherBag.used; ++i) {    // Iterate from 0 to otherBag.used
            if( has_key(otherBag.keys[i]) ) {       // call has_key on otherBag's key[] per i
                return true;                        // return true on first time we find match
            }
        }
        return false;
    }
    
    // Nonmember function
    // Returns a new keyed bag that is the union of bag b1 and bag b2
    keyed_bag operator+(const keyed_bag& b1, const keyed_bag& b2) {
        assert((b1.size()+b2.size()) <= keyed_bag::CAPACITY);       // Check if b1 + b2 sizes is smaller than CAP
        keyed_bag temp;                             // Make temporary bag
        temp += b1;                                 // Call += operator overloaded function on b1
        temp += b2;                                 // Call += operator overloaded function on b2
        return temp;                                // Return new bag object
    }
}

