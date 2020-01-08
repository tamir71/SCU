		.syntax		unified
		.cpu		cortex-m4
		.text
		
		.global		Zeller1
		.thumb_func
		//                           R0          R1          R2          R3
		// uint32_t Zeller1(uint32_t k, uint32_t m, uint32_t D, uint32_t C);
		// This function can use multiply and divide instructions.
Zeller1:
		ADD		R0, R0, R2			// f = k + D
		ADD		R0, R0, R2, LSR 2	// D / 4
		ADD		R0, R0, R3, LSR 2	// C / 4
		SUB		R0, R0, R3, LSL 1	// f -= C * 2
		LDR		R3, =13				
		MUL		R2, R1, R3			// 13 * m
		SUB		R2, R2, 1			// 13 * m - 1
		LDR		R3, =5
		UDIV	R2, R2, R3			// temp = (13 * m - 1) / 5
		ADD		R0, R0, R2			// f += temp
		LDR		R3, =7
		SDIV	R2, R0, R3			// temp = f / 7
		MUL		R2, R2, R3			// temp *= 7
		SUB		R2, R0, R2			// temp = f - temp
		CMP		R2, 0				// temp ? 0
		IT		LT					// temp < 0 ?
		ADDLT	R2, R2, R3			// if temp < 0, temp += 7
		MOV		R0, R2
		BX 		LR
		
		.global		Zeller2
		.thumb_func
		//                           R0          R1          R2          R3
		// uint32_t Zeller2(uint32_t k, uint32_t m, uint32_t D, uint32_t C);
		// This function CANNOT use divide instructions (SDIV or UDIV).
Zeller2:
		PUSH	{R4}
		ADD		R0, R0, R2			// f = k + D
		ADD		R0, R0, R2, LSR 2	// D / 4
		ADD		R0, R0, R3, LSR 2	// C / 4
		SUB		R0, R0, R3, LSL 1	// f -= C * 2
		LDR		R3, =13				
		MUL		R2, R1, R3			// 13 * m
		SUB		R2, R2, 1			// 13 * m - 1
		LDR		R3, =858993459		// 2^32 / 5
		SMULL	R2, R3, R2, R3		// temp = temp * (2^32)/5
		ADD		R0, R0, R3			// f += temp
		LDR		R3, =613566757		// 2^32 / 7
		SMULL	R2, R3, R0, R3		// temp = f * (2^32)/7
		LDR		R4, =7
		MUL		R3, R3, R4			// temp *= 7
		SUB		R3, R0, R3			// temp = f - temp
		CMP		R3, 0				// temp ? 0
		IT		LT					// temp < 0 ?
		ADDLT	R3, R3, 7			// if temp < 0, temp += 7
		MOV		R0, R3
		POP		{R4}
		BX 		LR
		
		.global		Zeller3
		.thumb_func
		//                           R0          R1          R2          R3
		// uint32_t Zeller3(uint32_t k, uint32_t m, uint32_t D, uint32_t C);
		// This function CANNOT use multiply instructions (MUL, MLS, etc.).
Zeller3:
		PUSH	{R4}
		ADD		R0, R0, R2			// f = k + D
		ADD		R0, R0, R2, LSR 2	// D / 4
		ADD		R0, R0, R3, LSR 2	// C / 4
		SUB		R0, R0, R3, LSL 1	// f -= C * 2
		ADD		R4, R1, R1, LSL 3	// 8m + 1m
		ADD		R2, R4, R1, LSL 2	// temp = 9m + 4m = 13m
		SUB		R2, R2, 1			// 13 * m - 1
		LDR		R4, =5
		UDIV	R2, R2, R4			// (13 * m - 1) / 5
		ADD		R0, R0, R2			// f += temp
		LDR		R4, =7
		SDIV	R2, R0, R4			// temp = f / 7
		LSL		R4, R2, 3			// R4 = 8*temp
		SUB		R2, R4, R2			// 8*temp - temp = 7*temp
		SUB		R2, R0, R2			// temp = f - temp
		CMP		R2, 0				// temp ? 0
		IT		LT					// temp < 0 ?
		ADDLT	R2, R2, 7			// if temp < 0, temp += 7
		MOV		R0, R2
		POP		{R4}
		BX 		LR
		
		.end