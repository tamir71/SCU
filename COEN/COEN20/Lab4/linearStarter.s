		.syntax		unified
		.cpu		cortex-m4
		.text
		.global		MxPlusB
		.thumb_func
		// int32_t MxPlusB(int32_t x, int32_t mtop, int32_t mbtm, int32_t b);
		// Equation: y = mx + b, where m = mtop / mbtm.
		// Compute the value of y, and return it.
		// HINT: To compute value of m, use the equation at the bottom of the lab PDF!		
		// R0 = x, R1 = mtop, R2 = mbtm, R3 = b
MxPlusB:
		PUSH	{R4}
		MUL		R1, R0, R1		// temp1 = x * dvnd
		MUL		R0, R1, R2		// temp1 = (x * dvnd) * dvsr
		ASR		R0, R0, 31		// temp1 = temp1 >> 31
		MUL		R0, R0, R2		// temp1 = temp1 * dvsr
		LSL		R0, R0, 1		// temp1 = temp1 << 1
		ADD		R0, R0, R2		// temp1 = temp1 + dvsr
		MOV		R4, 2			// temp2 = 2
		SDIV	R0, R0, R4		// temp1 = temp1 / 2
		ADD		R0, R0, R1		// temp1 = temp1 + (x * dvnd)
		SDIV	R0, R0, R2		// temp1 = temp1 / dvsr
		ADD		R0, R0, R3		// temp1 = temp1 + b
		POP		{R4}
		BX		LR	
		.end