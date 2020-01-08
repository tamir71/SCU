// Tamir Enkhjargal, created by Vineet Joshi
// October 15, 2019
// copy.s
// This is my starter code for Lab3 of COEN 20.

// If you have never encountered void pointers before:
// 		A void pointer is a pointer that has no associated data type with it.
// 		A void pointer can hold address of any type and can be typcasted to any type.
// (Source: "GeeksforGeeks")

		.syntax		unified
		.cpu		cortex-m4
		.text

		.global		UseLDRB
		.thumb_func
UseLDRB:						// void UseLDRB(void *dst, void *src);
		.rept 512				// 512 / 1 = 512 repeated
		LDRB	R2, [R1], 1		// Read content of source and increment by 1 byte
		STRB	R2, [R0], 1		// Store the byte at R2 into content of R0 and increment
		.endr					// End loop
		BX		LR				// Return

		.global		UseLDRH
		.thumb_func
UseLDRH:						// void UseLDRH(void *dst, void *src);
		.rept 256				// 512 / 2 = 256 repeated
		LDRH	R2, [R1], 2		// Read content at source, increment by 2 bytes
		STRH	R2, [R0], 2		// Store content to dest, increment by 2 bytes
		.endr					// End loop
		BX		LR				// Return

		.global		UseLDR
		.thumb_func
UseLDR:							// void UseLDR(void *dst, void *src);
		.rept 128				// 512 / 4 = 128 repeated
		LDR		R2, [R1], 4		// Read content at source, increment by 4 bytes
		STR		R2, [R0], 4		// Store content to dest, increment by 4 bytes
		.endr					// End loop
		BX		LR				// Return
		
		.global		UseLDRD
		.thumb_func
UseLDRD:						// void UseLDRD(void *dst, void *src);
		.rept 64				// 512 / 8 = 64 repeated
		LDRD	R2,R3, [R1], 8	// Load 64 bits to R2 and R3, increment by 8
		STRD	R2,R3, [R0], 8	// Store the 64 bits to dest, increment by 8
		.endr					// End loop
		BX		LR				// Return
		
		.global		UseLDM
		.thumb_func
UseLDM:							// void UseLDM(void *dst, void *src);
		PUSH	{R4-R12}		// We need 8 scratch registers
		.rept 16				// 512 / 32 = 16 repeated
		LDMIA	R1!, {R4-R12}	// Load contents of R1 into R4-R12
		STMIA	R0!, {R4-R12}	// Store contents of R4-R12 to dest
		.endr					// End loop
		POP		{R4-R12}		// Restore original R4-R12 data
		BX		LR				// Return
		
		.end