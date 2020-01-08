			.syntax		unified
			.cpu		cortex-m4
			.text		
			.global		GetNibble
			.thumb_func
			// uint32_t GetNibble(void *nibbles, uint32_t which);
			// R0 = start address of nibbles array, R1 = increment address by which
GetNibble:
			LSR		R2, R1, 1		// Divide which by 2
			LDRB	R2, [R0, R2]	// Address shift by which
			AND		R1, R1, 1		// This is to test if odd/even, ODD=1, EVEN=0
			CMP		R1, 1			// If R1 = 1
			ITE		EQ				// EQUAL = ODD, NEQUAL = EVEN
			UBFXEQ	R0, R2, #4, #4	// IF EQUAL INSERT 4 BITS STARTING AT 4
			UBFXNE	R0, R2, #0, #4	// IF NEQUAL INSERT 4 BITS STARTING AT 0
			BX 		LR		
	
			.global		PutNibble
			.thumb_func
			// void PutNibble(void *nibbles, uint32_t which, uint32_t value);
			// R0 = start adr of nibble array, R1 = increment adr by which, R2 = value
PutNibble:
			PUSH	{R4, LR}
			LSR		R4, R1, 1		// Divide which by 2
			LDRB	R3, [R0, R4]	// Address shfit by which
			AND		R1, R1, 1		// Test if odd/even, ODD=1, EVEN=0
			CMP		R1, 1			// If R1 = 1
			ITE		EQ				// EQUAL = ODD, NEQUAL = EVEN
			BFIEQ	R3, R2, #4, #4	// IF EQUAL INSERT 4 BITS STARTING AT 4
			BFINE	R3, R2, #0, #4	// IF NEQUAL INSERT 4 BITS STARTING AT 0
			STRB	R3, [R0, R4]	// Store back into shifted address
			POP		{R4, PC}		// Pop back
			.end