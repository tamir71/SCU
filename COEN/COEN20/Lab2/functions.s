//	functions.s
//	Starter code for COEN20L Lab 2
//	Tamir Enkhjargal, 2019

		.syntax		unified
		.cpu		cortex-m4
		.text
	
						// int32_t Add(int32_t a, int32_t b);
		.global		Add
		.thumb_func
Add:
		ADD	R0,R0,R1	// Add parameter 1 (R0) and parameter 2 (R1) to R0
		BX	LR			// Return
	
						// int32_t Less1(int32_t a);
		.global		Less1
		.thumb_func
Less1:
		SUB	R0,1		// Subtract 1 from parameter R0
		BX	LR			// Return	
	
						// int32_t Square2x(int32_t x);
		.global		Square2x
		.thumb_func
Square2x:
		ADD	R0,R0,R0	// Add value of R0 to itself (2x)
		B	Square		// Then go to function Square() with R0 (2x)
		
						// int32_t Last(int32_t x);
		.global		Last
		.thumb_func
Last:
		PUSH {R4, LR}	// Save previous data on R4 to stack
		MOV	R4, R0		// Then save value of x to R4
		BL	SquareRoot	// Call SquareRoot with value of x
		ADD	R0,R0,R4	// R0 is now changed from Square(x), and add saved initial x
		POP	{R4, PC}	// Return our original value of R4
		
.end