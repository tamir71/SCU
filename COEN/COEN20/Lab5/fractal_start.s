// Tamir Enkhjargal
// COEN 20 Lab 5
// Lab#4b: Pixels, Fonts, and Fractals

		.syntax		unified
		.cpu		cortex-m4
		.text
		
.global		WritePixel
.thumb_func
// void WritePixel(int x, int y, uint8_t colorIndex, uint8_t frameBuffer[256][240]);
// x = R0, y = R1, colorIndex = R2, frameBuffer = R3
// frameBuffer + (y*240+x) = colorIndex
WritePixel:
		PUSH	{R4}
		LDR		R4, =240
		MUL		R1, R1, R4		// y*240
		ADD		R1, R1, R0		// (y*240)+x
		ADD		R1, R1, R3		// frameBuffer + (y*240+x)
		STR		R2, [R1]
		POP		{R4}
		BX 		LR
		
.global		BitmapAddress
.thumb_func
// uint8_t *BitmapAddress(char ascii, uint8_t *fontTable, int height, int width);
// ascii = R0, fontTable = R1, height = R2, width = R3
BitmapAddress:
		PUSH	{R4}
		SUB		R0, R0, ' '		// 0b[ascii] - ' ' = char_offset
		ADD		R3, R3, 7		// width + 7
		LDR		R4, =8
		UDIV	R3, R3, R4		//  (width + 7) / 8 = n = bytesPerRow
		MUL		R3, R3, R2		// bytesPerRow * height
		MUL		R3, R3, R0		// char_offset * (bytesPerRow*height) = offset
		ADD		R0, R1, R3		// return fontTable + offset
		POP		{R4}
		BX		LR
		
.global		GetBitmapRow
.thumb_func
// uint32_t GetBitmapRow(uint8_t *rowAdrs);
GetBitmapRow:
		LDR		R0, [R0]
		REV		R0, R0			// Reverse bytes
		BX		LR
		
		.end