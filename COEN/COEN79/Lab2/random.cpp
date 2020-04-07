//
//  random.cpp
//  lab2
//
//  Created by tenkhjar on 1/16/20.
//  Copyright © 2020 SCU. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include "random.h"

using namespace std;

namespace coen79_lab2 {
    // Constructor needs four parameters in this order. Simple assignment from argc
    rand_gen::rand_gen(int seed, int multiplier, int increment, int modulus) {
        this->seed = seed;
        this->multiplier = multiplier;
        this->increment = increment;
        this->modulus = modulus;
    }
    
    // Assign new seed from argc
    void rand_gen::set_seed(int newSeed) {
        this->seed = newSeed;
    }
    
    // Calculate next seed using equation (m * s + i) % mod
    int rand_gen::next() {
        int temp;
        temp = (this->multiplier * this->seed + this->increment) % this->modulus;
        this->seed = temp;
        return temp;
    }
    
    // Print information in an orderly fashion
    void rand_gen::print_info() const {
        cout << "Seed: " << this->seed;
        cout << " Multiplier: " << this->multiplier;
        cout << " Increment: " << this->increment;
        cout << " Modulus: " << this->modulus << endl << endl;
    }
}
