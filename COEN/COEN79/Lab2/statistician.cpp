//
//  statistician.cpp
//  lab2
//
//  Created by tenkhjar on 1/16/20.
//  Copyright © 2020 SCU. All rights reserved.
//

#include <cassert>          // Provides assert
#include <stdio.h>          // Provides istream class
#include "statistician.h"

using namespace std;

namespace coen79_lab2 {

    // Constructor calls reset()
    statistician::statistician() {
        this->reset();
    }

    // next() function updates all private variables
    void statistician::next(double r) {
        this->last = r;
        if (this->max < r) {
            this->max = r;
        }
        if (this->min > r) {
            this->min = r;
        }
        this->len++;
        this->summ += r;
    }
    
    // Simple length assignment
    int statistician::length() const {
        return this->len;
    }
    
    // Simple sum assignment
    double statistician::sum() const {
        return this->summ;
    }
    
    // Calculate mean with sum and length
    double statistician::mean() const {
        assert(this->len > 0);
        return this->summ/this->len;
    }
    
    // Simple minimum assignment
    double statistician::minimum() const {
        assert(this->len > 0);
        return this->min;
    }
    
    // Simple maximum assignment
    double statistician::maximum() const {
        assert(this->len > 0);
        return this->max;
    }
    
    // Set numbers to zero, except minimum to INT_MAX
    void statistician::reset() {
        this->len = 0;
        this->summ = 0;
        this->min = INT_MAX;
        this->max = 0;
        this->last = 0;
    }
    
    // Friend function to add up length, sum and last. Find new min and max from both.
    statistician operator + (const statistician &s1, const statistician &s2) {
        statistician temp(s1);
        temp.len += s2.len;
        temp.summ += s2.summ;
        temp.min = (temp.min < s2.min) ? temp.min : s2.min;
        temp.max = (temp.max > s2.max) ? temp.max : s2.max;
        temp.last += s2.last;
        return temp;
    }
    
    // Friend function to multiply sum, min, max, and last. Return statistician object.
    statistician operator * (double scale, const statistician &s) {
        statistician temp(s);
        temp.summ *= scale;
        temp.min *= scale;
        temp.max *= scale;
        temp.last *= scale;
        return temp;
    }
    
    // Compare two statistician objects. They are both length 0 (true) or share all other variables (length, sum, min, max) (true). If not all match, then false.
    bool operator == (const statistician &s1, const statistician &s2) {
        if (s1.length() == 0 && s2.length() == 0)
            return true;
        else if (s1.length() == s2.length() && s1.sum() == s2.sum() && s1.minimum() == s2.minimum() && s1.maximum() == s2.maximum()) {
            return true;
        }
        else {
            return false;
        }
    }
}
