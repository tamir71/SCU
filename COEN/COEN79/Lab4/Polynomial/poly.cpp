//
//  polynomial.cpp
//  Lab 4
//
//  Created by tenkhjar on 1/30/20
//  Copyright 2020 SCU. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <cmath>                // For pow()
#include "poly.h"
#include <climits>              // For UINT_MAX
#include <iomanip>

using namespace std;

namespace coen79_lab4 {
    
    // Constructor: creates a polynomial of all zero coefficients except for c with specified exponent
    polynomial::polynomial(double c, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        for(int i = 0; i < CAPACITY; i++) {
            data[i] = 0;
        }
        data[exponent] = c;
    }
    
    // Sets the coefficient for the specified exponent
    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        data[exponent] = coefficient;
    }
    
    // Adds amount to existing coefficient at exponent
    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        data[exponent] += amount;
    }

    // All coefficients of `this` polynomial are set to zero
    void polynomial::clear() {
        for(int i = 0; i < CAPACITY; i++) {
            data[i] = 0;
        }
    }
    
    // Return value is the antiderivative of the polynomial
    polynomial polynomial::antiderivative() const {
        assert(degree() < MAXIMUM_DEGREE);          // Need to check that highest non-zero coef exponent is smaller than 29
        polynomial a(0,0);                          // Create a temporary polynomial
        a.data[0] = 0;                              // that is completely empty
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {   // antiderivative is reversed chain rule
            a.data[i+1] = (data[i]/(i+1));
        }
        return a;
    }
    
    // Returns coefficient at specified exponent
    double polynomial::coefficient(unsigned int exponent) const {
        if(exponent > MAXIMUM_DEGREE)               // If exponent over 29, then return 0
            return 0;
        else
            return data[exponent];                  // Return coefficient at exponent
    }
    
    // Returns the value of the definite integral from x0 to x1
    double polynomial::definite_integral(double x0, double x1) const {
        double upper, lower = 0.0;                 // Initialize doubles
        polynomial a;                               // Temporary polynomial
        a = antiderivative();                       // Call antiderivative function on `this`
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {   // For each iteration i, calculate value with input x0/x1
            lower += (a.data[i] * pow(x0,i));       // Calculate each lower bound with input x0
            upper += (a.data[i] * pow(x1,i));       // Calculate each upper bound with input x1
        }
        return upper - lower;                       // Subtract definite of upper - lower
    }
    
    // Returns the highest exponent with a nonzero coefficient
    unsigned int polynomial::degree() const {
        for(int i = CAPACITY-1; i >= 0; i--) {  // Start from highest exponent then move down
            if(data[i] != 0)
                return i;
        }
        return 0;                               // If we have empty polynomial, return 0
    }
    
    // Returns the polynomial of the first derivative of polynomial `this`
    polynomial polynomial::derivative() const {
        polynomial a;                                   // Temporary polynomial
        for(int i = 1; i < MAXIMUM_DEGREE; ++i) {       // Start at 1 because exponent 0 becomes 0
            a.data[i-1] = (data[i] * i);                // Chain rule. Use ++i in loop because last exponent OOB
        }
        return a;
    }
    
    // Returns the value of the polynomial for given x
    double polynomial::eval(double x) const {
        double sum = 0.0;
        for(int i = 0; i < CAPACITY; i++) {
            sum += (data[i] * pow(x, i));
        }
        return sum;
    }

    // Returns true when polynomial is all zero
    bool polynomial::is_zero() const {
        for(int i = 0; i < MAXIMUM_DEGREE; i++) {
            if(data[i] != 0) {
                return false;                   // Return false upon seeing nonzero value
            }
        }
        return true;                            // Return true when all coefficients are zero
    }
    
    // Returns the next exponent that is larger than e with nonzero coefficient
    unsigned int polynomial::next_term(unsigned int e) const {
        for(int i = e+1; e < MAXIMUM_DEGREE; i++) {       // Start at e+1 until CAPACITY-1
            if(data[i] != 0)                        // If there is a nonzero coef exponent, return i
                    return i;                       // returns next term i
        }
        return 0;                                   // If e is highest exponent, then return 0
    }
    
    // Returns the next exponent that is smaller than e with nonzero coefficient
    unsigned int polynomial::previous_term(unsigned int e ) const {
        for(int i = e-1; i >= 0; i--) {             // Start at e-1 until 0
            if(data[i] != 0)                        // If there is a nonzero coef exponent, return i
                return i;                           // returns previous term i
        }
        return UINT_MAX;                            // If e is the smallest exponent, return UINT_MAX
    }

    // Same as eval member function
    double polynomial::operator()(double x) const {
        return eval(x);                             // Just call eval function
    }
    
    /* NON MEMBER BINARY OPERATORS */

    // Returns a polynomial with each coefficient equal to p1+p2
    polynomial operator+(const polynomial& p1, const polynomial& p2) {
        polynomial tmp;                                                 // Temporary polynomial
        for(int i = 0; i < polynomial::CAPACITY; i++)                   // Iterate through 0 to CAPACITY
            tmp.assign_coef(p1.coefficient(i)+p2.coefficient(i), i);    // Call coefficient() function on p1 and p2
        return tmp;
    }
    
    // Returns a polynomial with each coefficient equal to p1-p2
    polynomial operator-(const polynomial& p1, const polynomial& p2) {
        polynomial tmp;
        for(int i = 0; i < polynomial::CAPACITY; i++)
            tmp.assign_coef(p1.coefficient(i)-p2.coefficient(i), i);    // Call coefficient() function on p1 and p2
        return tmp;
    }
    
    // Returns a polynomial with each polynomial multiplication
    polynomial operator*(const polynomial& p1, const polynomial& p2) {
        assert( (p1.degree() + p2.degree()) <= polynomial::MAXIMUM_DEGREE);  // Highest degree of p1 and p2 smaller than 29
        polynomial tmp;                                                      // Temporary polynomial
        for(int i = 0; i <= p1.degree(); i++)
            for(int j = 0; j <= p2.degree(); j++)
                tmp.add_to_coef(p1.coefficient(i)*p2.coefficient(j), i+j); // Assign temp.data[i+j] = p1.data[i]*p2.data[i]
        return tmp;
    }
    
    // Nonmember output function
    // The polynomial is printed to ostream which has specific formatting
    std::ostream& operator<<(ostream& out, const polynomial& p) {
        unsigned int i = p.degree();
        streamsize s = out.precision();
        out << fixed;
        out << setprecision(1);
        for(int i = p.degree(); i >= 0; i--) {              // Start at highest exponent and move down calling previous_term()
            if(p.degree() == 0) 
                out << p.coefficient(0);
            else if(p.coefficient(i) != 0) {        
                if(i == p.degree())                             // At highest exponent
                    out << p.coefficient(i) << "x^" << i << ' ';   // Print as `(-/+)ax^i `
                else if(i < p.degree() && i > 1) {              // If not highest and not first coefficient
                    if(p.coefficient(i) < 0)
                        out << "- ";                            // If negative add `- `
                    else    
                        out << "+ ";                            // If positive add `+ `
                    out << fabs(p.coefficient(i)) << "x^" << i << ' ';   // print `ax^i `
                }
                else if(i == 1) {
                    if(p.coefficient(i) < 0)
                        out << "- ";                            // If negative add `- `
                    else
                        out << "+ ";                            // If positive add `+ `
                    out << fabs(p.coefficient(i)) << "x ";             // print `ax `
                }
                else if(i == 0) {
                    if(p.coefficient(i) < 0)
                        out << "- ";                            // If negative add `- `
                    else
                        out << "+ ";                            // If positive add `+ `
                    out << fabs(p.coefficient(i));                    // print `a`
                }
            }
        }
        out.unsetf(ios_base::floatfield);
        out << setprecision(s);
        return out;
    }
}

