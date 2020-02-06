//
// sequence.cpp
// lab3
//
// Created by tenkhjar on 1/23/20
// Copyright 2020 SCU. All rights reserved.
//

#include <cassert>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "sequence1.h"

using namespace std;

namespace coen79_lab3 {
    
    sequence::sequence() {
        this->length = 0;
        this->cur = 0;
    }

    
    void sequence::start() {
       cur = 0;
    }
    
    void sequence::end() {
        cur = length-1;
    }
    
    void sequence::last() {
        cur = CAPACITY-1;
        
    }
    
    void sequence::advance() {
        assert(is_item());
        if(cur < length)
            cur++;
    }
    
    void sequence::retreat() {
        if(cur > 0) {
            cur--;
        }
    }
    
    void sequence::insert(const value_type& entry) {
        assert(size() < CAPACITY);
        if(length == 0) {
            data[length] = entry;
            cur = 0;
        }
        else {
            for (int i = length; i >= cur+1; --i) {
                data[i] = data[i-1];
             }
            data[cur] = entry;
          }
        length++;
    }

    void sequence::attach(const value_type& entry) {
        assert(size() < CAPACITY);
        if(!is_item()) {
            data[length] = entry;
        }
        else {
            for(int i = length; i > cur+1; --i) {
                data[i]=data[i-1];
            }
            data[cur+1] = entry;
            cur++;
        }
        length++;
    }
    
    void sequence::remove_current() {
        assert(is_item());
        for(int i = cur+1; i < length; ++i){
            data[i-1]=data[i];
        }
        length--;
    }
    
    void sequence::insert_front(const value_type& entry) {
        assert(size() < CAPACITY);
        cur=0;
        insert(entry);
        length++;
    }
    
    void sequence::attach_back(const value_type& entry) {
        assert(size() < CAPACITY);
        data[length] = entry;
        length++;
    }
   
    void sequence::remove_front() {
        assert(is_item());
        for(int i = 0; i < length-1; ++i)
            data[i]=data[i+1];
        length--;
    }
    
    void sequence::operator +=(const sequence& rhs){
        assert((length + rhs.length) < CAPACITY);
        size_type tmp = rhs.length;
        for(int i = 0; i < tmp; i++) {
            data[length++] = rhs.data[i];
        }
    }

    sequence::size_type sequence::size() const {
        return length;
    }
    
    bool sequence::is_item() const {
        if(cur < length)
            return true;
        return false;
    }

    sequence::value_type sequence::current() const {
        assert(is_item());
        return data[cur];
    }
    
    sequence::value_type sequence::operator[] (int index) const {
        assert(index < length);
        return data[index];
    }
    
    double sequence::mean() const {
        double sum=0.0;
        for(int i = 0; i < length; ++i) {
            sum += data[i];
        }
        return sum/size();
    }

    double sequence::standardDeviation() const {    
        double stdev = 0.0;
        for(int i = 0; i < length; ++i) {
            stdev += pow(data[i] - mean(), 2);
        }
        return sqrt(stdev/length); 
    }
    
    sequence operator+(const sequence& lhs, const sequence& rhs){
        assert((lhs.size() + rhs.size()) <= sequence::CAPACITY);
        sequence(tmp);
        tmp += lhs;
        tmp += rhs;
        return tmp;
    }
    
    sequence::value_type summation(const sequence& s) {
        double sum = 0.0;
        for(int i = 0; i < s.size(); ++i) {
            sum += s.data[i];
        }
        return sum;
    }   
}
