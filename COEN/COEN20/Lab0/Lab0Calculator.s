/*
	This code was written to support the book, "ARM Assembly for Embedded Applications",
	by Daniel W. Lewis. Permission is granted to freely share this software provided
	that this notice is not removed. This software is intended to be used with a run-time
    library adapted by the author from the STM Cube Library for the 32F429IDISCOVERY 
    board and available for download from http://www.engr.scu.edu/~dlewis/book3.
*/
        .syntax     unified
		.cpu        cortex-m4
        .text

// ----------------------------------------------------------
// int Addition(int op1, int op2) { return op1 + op2 ;}
// ----------------------------------------------------------

		.global		Addition
        .thumb_func
        .align
Addition:	// R0 = op1, R1 = op2
		ADD			R0,R0,R1		// R0 = R0 + R1
		BX			LR

// ----------------------------------------------------------
// int Subtraction(int op1, int op2) { return op1 - op2 ;}
// ----------------------------------------------------------

		.global		Subtraction
        .thumb_func
        .align
Subtraction:	// R0 = op1, R1 = op2
		SUB			R0,R0,R1		// R0 = R0 - R1
		BX			LR

// ----------------------------------------------------------
// int Multiplication(int op1, int op2) { return op1 * op2 ;}
// ----------------------------------------------------------

		.global		Multiplication
        .thumb_func
        .align
Multiplication:	// R0 = op1, R1 = op2
		MUL			R0,R0,R1		// R0 = R0 * R1
		BX			LR


// ----------------------------------------------------------
// int Division(int op1, int op2) { return op1 / op2 ;}
// ----------------------------------------------------------

		.global		Division
        .thumb_func
        .align
Division:	// R0 = op1, R1 = op2
		SDIV		R0,R0,R1		// R0 = R0 / R1
		BX			LR

		.end


