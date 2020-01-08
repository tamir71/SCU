					.syntax		unified
					.cpu		cortex-m4
					.text		
					.global		Discriminant
					.thumb_func
					// float Discriminant(float a, float b, float c);
					// S0 = a, S1 = b, S2 = c, b^2 - 4ac
Discriminant:
				VMUL.F32	S0, S0, S2		// a*c
				VMOV		S2, 4			
				VMUL.F32	S0, S0, S2		// S0 = 4*a*c
				VMUL.F32	S1, S1, S1		// S1 = b^2
				VSUB.F32	S0, S1, S0		// S0 = b^2 - 4*a*c
				BX			LR
			
					.global		Quadratic
					.thumb_func
					// float Quadratic(float x, float a, float b, float c);
					// S0 = x, S1 = a, S2 = b, S3 = c,    ax^2 + bx + c
Quadratic:
				VMUL.F32	S2, S0, S2		// S2 = b*x
				VMUL.F32	S0, S0, S0		// S0 = x*x
				VMUL.F32	S0, S0, S1		// S0 = a*x^2
				VADD.F32	S0, S0, S2		// S0 = ax^2 + bx
				VADD.F32	S0, S0, S3		// S0 = ax^2 + bx + c
				BX			LR
			
					.global		Root1
					.thumb_func
					// float Root1(float a, float b, float c);
					// [-b + sqrt(discriminant)]/2a
					// S0 = a, S1 = b, S2 = c
Root1:
				PUSH		{LR}
				VPUSH		{S16-S18}
				VMOV		S16, S0			// store a => S16
				VMOV		S17, S1			// store b => S17
				VMOV		S18, S2			// store c => S18
				BL			Discriminant	// calling Discriminant resets S0-S3, saved to S0
				VSQRT.F32	S0, S0			// sqrt(dscrt)
				VNEG.F32	S17, S17		// b --> -b
				VADD.F32	S0, S17, S0		// S0 = -b + sqrt(dscrt)
				VMOV		S1, 2
				VMUL.F32	S16, S1, S16	// S16 = 2*a
				VDIV.F32	S0, S0, S16		// S0 = S0/S16 => (-b + sqrt(dscrt)) / 2*a
				VPOP		{S16-S18}
				POP			{PC}
					
					.global		Root2
					.thumb_func
					// float Root2(float a, float b, float c);
Root2:
				PUSH		{LR}
				VPUSH		{S16-S18}
				VMOV		S16, S0			// store a => S16
				VMOV		S17, S1			// store b => S17
				VMOV		S18, S2			// store c => S18
				BL			Discriminant	// calling Discriminant resets S0-S3, saved to S0
				VSQRT.F32	S0, S0			// sqrt(dscrt)
				VNEG.F32	S17, S17		// b --> -b
				VSUB.F32	S0, S17, S0		// S0 = -b - sqrt(dscrt)
				VMOV		S1, 2
				VMUL.F32	S16, S1, S16	// S16 = 2*a
				VDIV.F32	S0, S0, S16		// S0 = S0/S16 => (-b + sqrt(dscrt)) / 2*a
				VPOP		{S16-S18}
				POP			{PC}
				.end
				
				