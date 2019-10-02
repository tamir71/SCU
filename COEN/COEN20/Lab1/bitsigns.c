/*  Lab 1, 8-bit Binary Numbers
 *  Tamir Enkhjargal
 *
 *  Creating three functions to implement functionality of switching between signed and unsigned
 *  decimal numbers to binary representations.
 *
 */

#include <stdio.h>          // Calling libraries

/* Function prototypes */

int32_t     Bits2Signed(int8_t bits[8]);				// Convert array of bits to signed int
uint32_t    Bits2Unsigned(int8_t bits[8]);				// Convert array of bits to unsigned int
void        Increment(int8_t bits[8]);					// Add 1 to value represented by bit pattern
void        Unsigned2Bits(uint32_t n, int8_t bits[8]);	// Opposite of Bits2Unsigned

/*-------------------------*/

/* Bits to Signed Function */

int32_t Bits2Signed(int8_t bits[8]) {
    int32_t retValue = Bits2Unsigned(bits);				// Call Bits2Unsigned which gives you a value from 0 to 255
    if(retValue > 127) {								// and then adjust for rollover and the range becomes -128 to +127
		retValue -= 256;
	}
	return retValue;									// Return our signed value
}

/*-------------------------*/

/* Bits to Unsigned Function */

uint32_t Bits2Unsigned(int8_t bits[8]) {
    uint32_t retValue = 0;								// Create retValue variable
    int i;

    for(i = 7; i >= 0; i--) {							// Using the code from the hint, create a loop to essentially
        retValue = 2*retValue + bits[i];				// determine the unsigned value using "polynomial expansion"
    }
    
    return retValue;									// Return our unsigned value
}

/*-------------------------*/

/* Increment Function */

void Increment(int8_t bits[8]) {
    int i;
    for(i = 0; i < 8; i++) {							// Loop through our whole bit array, if necessary
        if(bits[i] == 0) {								// If it hits a 0, increment to 1
            bits[i] = 1;								// "Increment"
            break;										// Exit the loop once we know we've incremented
        }
        if(bits[i] == 1) {								// If it hits a 1, we need to keep looping and change to 0
            bits[i] = 0;
        }
    }
	return;												// Return (null)
}

/*-------------------------*/

/* Unsigned to Bits Function */

void Unsigned2Bits(uint32_t n, int8_t bits[8]) {
    int i = 0;
    int r;
    while(i < 8) {										// Using the repeated division method, loop through bit array
        r = n % 2;										// Take mod of value n as remainders
        n = n / 2;										// Then take integer value of n/2
        bits[i] = r;									// Our bits (in reverse b0 to b7) will be filled by the remainders
        i++;											// Increment i
    }
	return;												// Return (null)
}

/*-------------------------*/
