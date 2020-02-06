//
//  polynomial.cpp
//  Lab 4
//
//  Created by tenkhjar on 1/30/20
//  Copyright 2020 SCU. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <cmath>
#include "polynomial.h"
#include<fstream>
#include<cassert>
#include<climits>

using namespace std;

namespace coen79_lab4 {
    
    // Constructor: creates a polynomial of all zero coefficients except for c with specified exponent
    polynomial::polynomial(double c = 0.0, unsigned int exponent = 0) {
        assert(exponent <= MAXIMUM_DEGREE);
        for(int i = 0; i < CAPACITY; i++) {
            data[i] = 0;
        }
        data[exponent] = c;
    }

    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        data[exponent] = coefficient;
    }
    
    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        data[exponent] += amount;
    }

    void polynomial::clear() {
        for(int i = 0; i < CAPACITY; i++) {
            data[i] = 0;
        }
    }
    
    polynomial polynomial::antiderivative() const {
        assert(degree() < MAXIMUM_DEGREE);
        polynomial a(0,0);
        a.data[0] = 0;
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {
            a.data[i+1] = (data[i]/(i+1));
        }
        return a;
    }
    
    unsigned int polynomial::degree() const {
        for ( int i=CAPACITY-1;i>=0;--i){
            if(data[i]!=0){
                return i;
            }
        }
        return 0; //return highest degree in polynomial
    }
    /*
    polynomial::antiderivative() const {
        
    }
    */
    double polynomial::coefficient(unsigned int exponent) const{
        if(exponent>MAXIMUM_DEGREE){
            return 0;
        }
        else {
            return data[exponent]; //return value in exponent
        }
    }
    
    double polynomial::eval(double x) const {
        for ( int i=0; i<CAPACITY;++i){
            if(data[i]==x){
                return data[i]; //return value
            }
        }
        return NULL;//else null
    }
    
    
    
    double polynomial::definite_integral(double x0,double x1) const {
        polynomial b;
        b=antiderivative();
        
        double upper=0.0;
        double lower=0.0;
        for ( int i=0;i<MAXIMUM_DEGREE;++i){
            upper+=(b.data[i] * pow(x0,i)); //evaluate sum of upper bound
            lower+=(b.data[i]*pow(x1,i));//evaluate sum of lower bound
        }
        return upper-lower;//return difference
        }
    
    polynomial poly::derivative() const {
        polynomial c;
        for ( int i=1; i<MAXIMUM_DEGREE;++i){
            c.data[i-1]=(data[i]*i); //compute derivative
        }
        return c;
    }
    
    bool polynomial::is_zero() const {
        //if entire array is 0
        for ( int i=0; i<MAXIMUM_DEGREE;++i){
            if(data[i]!=0){
                return false;
            }
        }
        return true; //polynomial is all zero
    }
    
    unsigned int polynomial::next_term(unsigned int e) const {
        for ( int i =e+1; e<CAPACITY;++i){
            if(data[i]!=0){
                    return i; //get next term
        }
        }
     return 0;
    }
    
    unsigned int polynomial::previous_term(unsigned int e ) const {
        for ( int i=e-1;i>=0;--i){
            if(data[i]!=0){
                return i;//get previous term that is not zero
            }
        }
        return 0;
    }
    double polynomial::operator()(double x) const{
        return eval(x); //return eval
    }
    
    polynomial operator+(const poly& p1, const poly& p2){
       
        polynomial result;
        for ( int i=0; i<polynomial::CAPACITY;++i){
            result.data[i]=p1.data[i]+p2.data[i];
        }  //addiction operator
         
        return result;
    }
    
    polynomial operator-(const poly& p1, const poly& p2){
        polynomial result;
        for ( int i=0; i<polynomial::CAPACITY;++i){
            result.data[i]=abs(p1.data[i]-p2.data[i]);
        }  //difference of p1 and p2
        return result;
    }
    
    polynomial operator*(const poly& p1, const poly& p2){
        assert(p1.degree()+p2.degree()<=polynomial::MAXIMUM_DEGREE);
        polynomial result;
        for ( int i=0; i<polynomial::CAPACITY;++i){
            for ( int j=0; j<polynomial::CAPACITY;++j){
                result.data[i+j]+=(p1.data[i]*p2.data[j]);
            }
        }  //multiplication of pl and p2
       
        return result;
    }
    
    std::ostream& operator <<(ostream& out, const polynomial& p){
       
        for ( int i=p.degree();i>=0;--i){
            if( i>1){
                out<<p.data[i] +'x^'+i+' '; //output and show degree
             }
            else if (i==1){
                out<<p.data[i]+'x'+ ' ';//output and show x
            }
            else if(i==0){
                out<<p.data[i]; //output number
            }
        }
        return out; //need to return out b/c ostream
    }
}

