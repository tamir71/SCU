		.syntax		unified
		.cpu		cortex-m4
		.text
		.global		MatrixMultiply 
		.thumb_func
		// void MatrixMultiply(int32_t a[3][3], int32_t b[3][3], int32_t c[3][3]);
		// a = R0, b = R1, c = R2
		// R3 = adrr calc, R4 = a[][], R5 = b[][], R6 = c[][], R7 = row, R8 = col, R9 = k
MatrixMultiply:
		PUSH	{R4-R9, LR}
		
		MOV		R4, R0				// Store a in R4
		MOV		R5, R1				// Store b in R5
		MOV		R6, R2				// Store c in R6
		
		LDR		R7, =0				// row = 0
top1:	CMP		R7, 3				// row ? 0
		BGE		btm3				// if row >= 3 go btm3
		
		LDR		R8, =0				// col = 0
top2:	CMP		R8, 3				// col ? 0
		BGE		btm2				// if col >= 3 go btm2
		
		LDR		R3, =3
		MLA		R3, R3, R7, R8		// 3*row + col
		LDR		R1, =0	
		STR		R1, [R4, R3, LSL 2]	// 0 --> a[row][col]
		
		LDR		R9, =0				// k  =  0
top3:	CMP		R9, 3				// k  ?  0
		BGE		btm1				// if  k  >= 3 go btm3
		
		LDR		R3, =3
		MLA		R3, R3, R7, R8		// 3*row + col
		LDR		R0, [R4, R3, LSL 2]	// keep a[row][col] in R0

		LDR		R3, =3
		MLA		R3, R3, R7, R9		// 3*row + k
		LDR		R1, [R5, R3, LSL 2]	// keep b[row][k] in R1

		LDR		R3, =3
		MLA		R3, R3, R9, R8		// 3*k + col
		LDR		R2, [R6, R3, LSL 2]	// keep c[k][col] in R2
		
		BL		MultAndAdd			// Call MultAndAdd
		
		LDR		R3, =3
		MLA		R3, R3, R7, R8		// 3*row + col
		STR		R0, [R4, R3, LSL 2]	// store result R0 at A[row][col]

		ADD		R9, R9, 1			// k++;
		B		top3				// go back to k for loop
		
btm1:	ADD		R8, R8, 1			// col++;
		B		top2				// go back to col for loop
		
btm2:	ADD		R7, R7, 1			// row++;
		B		top1				// go back to row for loop
		
btm3:	POP		{R4-R9, PC}
		.end