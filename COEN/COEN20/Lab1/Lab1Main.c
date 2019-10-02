/*
	This code was written to support the book, "ARM Assembly for Embedded Applications",
	by Daniel W. Lewis. Permission is granted to freely share this software provided
	that this notice is not removed. This software is intended to be used with a run-time
    library adapted by the author from the STM Cube Library for the 32F429IDISCOVERY 
    board and available for download from http://www.engr.scu.edu/~dlewis/book3.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "library.h"
#include "graphics.h"

// Functions to be implemented in a separate C file
extern int32_t	Bits2Signed(int8_t bits[8]) ;
extern uint32_t Bits2Unsigned(int8_t bits[8]) ;
extern void		Increment(int8_t bits[8]) ;
extern void		Unsigned2Bits(uint32_t n, int8_t bits[8]) ;

// Public fonts defined in run-time library
typedef struct
	{
	const uint8_t *	table ;
	const uint16_t	Width ;
	const uint16_t	Height ;
	} sFONT ;

extern sFONT	Font8, Font12, Font16, Font20, Font24 ;

// Private functions defined in this file
static float	AcuteRadians(float degrees) ;
static char *	Bin2Asc(uint32_t binary) ;
static uint8_t	Bits2Byte(int8_t bits[]) ;
static void		Check(int8_t bits[], uint32_t ubinary, int32_t sbinary) ;
static void		Error(int8_t bits[], uint32_t ubinary, int32_t sbinary, char *cause) ;
static void		Delay(uint32_t msec) ;
static uint32_t	GetX(float deg, float percent, uint32_t radius) ;
static uint32_t GetTimeout(uint32_t msec) ;
static uint32_t	GetY(float deg, float percent, uint32_t radius) ;
static void		InitializeDisplay(void) ;
static void		LEDs(int grn_on, int red_on) ;
static void		PutStringAt(uint32_t x, uint32_t y, char *format, ...) ;
static void		SetFontSize(sFONT *pFont) ;
static float	Sine(float radians) ;
static float	SquareRoot(float radical) ;
static void		UpdateCircle(uint32_t ubinary) ;
static void		UpdateSigned(int32_t sbinary) ;
static void		UpdateUnsigned(uint32_t ubinary) ;

#define	ERR_FONT					Font12
#define	ERR_BRDR_COLOR				COLOR_BLACK
#define	ERR_BGND_COLOR				COLOR_RED
#define	ERR_FGND_COLOR				COLOR_WHITE

#define	PI							3.14159
#define	CPU_CLOCK_SPEED_MHZ			168
#define	ENTRIES(a)					(sizeof(a)/sizeof(a[0]))

#define	UNS_COLOR					COLOR_RED
#define	REP_COLOR					COLOR_BLACK
#define	SGN_COLOR					COLOR_BLUE

#define	CIRCLE_XPOS					(XPIXELS/2)
#define	CIRCLE_YPOS					184
#define CIRCLE_INNER_RAD			65
#define CIRCLE_OUTER_RAD			75

#define	UBAR_X						31
#define	UBAR_Y						84
#define	UBAR_SIZE					200

#define	UVAL_FONT					Font12
#define	UVAL_MIN					"0"
#define	UVAL_MAX					"255"
#define	UVAL_XMIN					(UBAR_X - strlen(UVAL_MIN)*UVAL_FONT.Width/2)
#define	UVAL_XMAX					(UBAR_X - strlen(UVAL_MAX)*UVAL_FONT.Width/2)
#define	UVAL_YTOP					(UBAR_Y - 3*UVAL_FONT.Height/2)
#define	UVAL_YBTM					(UBAR_Y + UBAR_SIZE + UVAL_FONT.Height/2 + 2)

#define	ULBL_FONT					Font12
#define	ULBL_TXT					"Unsigned"
#define	ULBL_X						(UBAR_X - strlen(ULBL_TXT)*ULBL_FONT.Width/2)
#define	ULBL_Y						(UVAL_YTOP - ULBL_FONT.Height)

#define	SBAR_X						209
#define	SBAR_Y						84
#define	SBAR_SIZE					200

#define	SVAL_FONT					Font12
#define	SVAL_MIN					"-128"
#define	SVAL_MAX					"+127"
#define	SVAL_XMIN					(SBAR_X - strlen(SVAL_MIN)*SVAL_FONT.Width/2)
#define	SVAL_XMAX					(SBAR_X - strlen(SVAL_MAX)*SVAL_FONT.Width/2)
#define	SVAL_YTOP					(UBAR_Y - 3*SVAL_FONT.Height/2)
#define	SVAL_YBTM					(UBAR_Y + UBAR_SIZE + SVAL_FONT.Height/2 + 2)

#define	SLBL_FONT					Font12
#define	SLBL_TXT					"Signed"
#define	SLBL_X						(SBAR_X - strlen(SLBL_TXT)*SLBL_FONT.Width/2)
#define	SLBL_Y						(SVAL_YTOP - SLBL_FONT.Height)

#define	REPVAL_FONT					Font8

#define	REP04TH_TXT					"00000000"
#define	REP04TH_X					(CIRCLE_XPOS - strlen(REP04TH_TXT)*REPVAL_FONT.Width/2)
#define	REP04TH_Y					(CIRCLE_YPOS - CIRCLE_INNER_RAD + 6)

#define	REP14TH_TXT					"01000000"
#define	REP14TH_X					(CIRCLE_XPOS + CIRCLE_INNER_RAD - strlen(REP04TH_TXT)*REPVAL_FONT.Width - 2)
#define	REP14TH_Y					(CIRCLE_YPOS - REPVAL_FONT.Height/2 + 1)

#define	REP24TH_TXT					"10000000"
#define	REP24TH_X					(CIRCLE_XPOS - strlen(REP24TH_TXT)*REPVAL_FONT.Width/2)
#define	REP24TH_Y					(CIRCLE_YPOS + CIRCLE_INNER_RAD - 6 - REPVAL_FONT.Height)

#define	REP34TH_TXT					"11000000"
#define	REP34TH_X					(CIRCLE_XPOS - CIRCLE_INNER_RAD + 2)
#define	REP34TH_Y					(CIRCLE_YPOS - REPVAL_FONT.Height/2 + 1)

#define	REPLBL_FONT					Font12
#define	REPLBL_TXT					"Representation"
#define	REPLBL_X					(CIRCLE_XPOS - strlen(REPLBL_TXT)*REPLBL_FONT.Width/2)					
#define	REPLBL_Y					(CIRCLE_YPOS - CIRCLE_OUTER_RAD - 2*REPLBL_FONT.Height)

#define	PTR_WIDTH					10
#define	PTR_HEIGHT					16

#define	U_X1						30
#define	U_X2						(U_X1 - PTR_WIDTH)
#define	U_X3						(U_X1 - PTR_WIDTH)

#define	U_Y1(y)						(y)
#define	U_Y2(y)						((y) - PTR_HEIGHT/2)
#define	U_Y3(y)						((y) + PTR_HEIGHT/2)

#define	S_X1						210
#define	S_X2						(S_X1 + PTR_WIDTH)
#define	S_X3						(S_X1 + PTR_WIDTH)

#define	S_Y1(y)						(y)
#define	S_Y2(y)						((y) - PTR_HEIGHT/2)
#define	S_Y3(y)						((y) + PTR_HEIGHT/2)

#define	BINARY_FONT					Font20
#define	BINARY_X					((XPIXELS - 8*BINARY_FONT.Width)/2)
#define	BINARY_Y					(CIRCLE_YPOS + CIRCLE_OUTER_RAD + 2*REPVAL_FONT.Height)

#define	OVFL_FONT					Font12
#define	OVFL_TEXT					" OVERFLOW! "
#define	OVFL_XPOS					(CIRCLE_XPOS - strlen(OVFL_TEXT)*OVFL_FONT.Width/2)
#define	OVFL_YOFF					35
#define	OVFL_MSEC					500

int main(void)
	{
	uint32_t ubinary ;
	int32_t sbinary ;
	int8_t bits[8] ;

	InitializeHardware(HEADER, "Lab 1: 8-bit Binary Numbers") ;
	LEDs(1, 0) ;

	InitializeDisplay() ;
	Unsigned2Bits(0, bits) ;
	for (;;)
		{
		ubinary = Bits2Unsigned(bits) ;
		sbinary = Bits2Signed(bits) ;
		Check(bits, ubinary, sbinary) ;

		SetFontSize(&BINARY_FONT) ;
		SetForeground(REP_COLOR) ;
		SetBackground(COLOR_WHITE) ;
		DisplayStringAt(BINARY_X, BINARY_Y, Bin2Asc(ubinary)) ;

		UpdateCircle(ubinary) ;
		UpdateUnsigned(ubinary) ;
		UpdateSigned(sbinary) ;

		Delay(30) ;
		Increment(bits) ;
		}

	return 0 ;
	}

static void UpdateUnsigned(uint32_t ubinary)
	{
	static uint32_t oldY = UBAR_Y + UBAR_SIZE/2 ;
	static uint32_t timeout = 0 ;
	uint32_t k, newY ;
	float percent ;

	if (ubinary == 0)
		{
		SetFontSize(&OVFL_FONT) ;
		SetForeground(COLOR_WHITE) ;
		SetBackground(UNS_COLOR) ;
		PutStringAt(OVFL_XPOS, CIRCLE_YPOS - OVFL_YOFF - OVFL_FONT.Height, OVFL_TEXT) ;
		timeout = GetTimeout(OVFL_MSEC) ;
		}

	if (timeout != 0 && (int32_t) (GetClockCycleCount() - timeout) > 0)
		{
		SetFontSize(&OVFL_FONT) ;
		SetForeground(COLOR_WHITE) ;
		SetBackground(COLOR_WHITE) ;
		PutStringAt(OVFL_XPOS, CIRCLE_YPOS - OVFL_YOFF - OVFL_FONT.Height, OVFL_TEXT) ;
		timeout = 0 ;
		}

	percent = (float) ubinary / 256 ;
	newY = 0.5 + (UBAR_Y + UBAR_SIZE - percent * UBAR_SIZE) ;

	SetColor(COLOR_WHITE) ;
	FillTriangle(U_X1, U_X2, U_X3, U_Y1(oldY), U_Y2(oldY), U_Y3(oldY)) ;
	SetColor(UNS_COLOR) ;
	FillTriangle(U_X1, U_X2, U_X3, U_Y1(newY), U_Y2(newY), U_Y3(newY)) ;
	oldY = newY ;

	SetColor(UNS_COLOR) ;
	for (k = 0; k < 5; k++)
		{
		DrawHLine(UBAR_X - 5, UBAR_Y + k*UBAR_SIZE/4, 10) ;
		}
	}

static void UpdateSigned(int32_t sbinary)
	{
	static uint32_t oldY = SBAR_Y + SBAR_SIZE/2 ;
	static uint32_t timeout = 0 ;
	float percent ;
	uint32_t k, newY ;

	if (sbinary == -128)
		{
		SetFontSize(&OVFL_FONT) ;
		SetForeground(COLOR_WHITE) ;
		SetBackground(SGN_COLOR) ;
		PutStringAt(OVFL_XPOS, CIRCLE_YPOS + OVFL_YOFF, OVFL_TEXT) ;
		timeout = GetTimeout(OVFL_MSEC) ;
		}

	if (timeout != 0 && (int32_t) (GetClockCycleCount() - timeout) > 0)
		{
		SetFontSize(&OVFL_FONT) ;
		SetForeground(COLOR_WHITE) ;
		SetBackground(COLOR_WHITE) ;
		PutStringAt(OVFL_XPOS, CIRCLE_YPOS + OVFL_YOFF, OVFL_TEXT) ;
		timeout = 0 ;
		}

	percent = (float) sbinary / 128 ;
	newY = 0.5 + (SBAR_Y + SBAR_SIZE/2 - percent * SBAR_SIZE/2) ;

	SetColor(COLOR_WHITE) ;
	FillTriangle(S_X1, S_X2, S_X3, S_Y1(oldY), S_Y2(oldY), S_Y3(oldY)) ;
	SetColor(SGN_COLOR) ;
	FillTriangle(S_X1, S_X2, S_X3, S_Y1(newY), S_Y2(newY), S_Y3(newY)) ;
	oldY = newY ;

	SetColor(SGN_COLOR) ;
	for (k = 0; k < 5; k++)
		{
		DrawHLine(SBAR_X - 5, SBAR_Y + k*SBAR_SIZE/4, 10) ;
		}
	}

static char *Bin2Asc(uint32_t binary)
	{
	static char bfr[9] ;
	int32_t bit ;

	for (bit = 7; bit >= 0; bit--)
		{
		bfr[7 - bit] = '0' + ((binary & (1 << bit)) != 0) ;
		}
	bfr[8] = '\0' ;

	return bfr ;
	}

static float AcuteRadians(float degrees)
	{
	float acute ;

	if      (degrees > 270)	acute = 360 - degrees ;
	else if (degrees > 180)	acute = degrees - 180 ;
	else if (degrees >  90)	acute = 180 - degrees ;
	else					acute = degrees ;

	return 	(PI * acute) / 180 ;
	}

static uint32_t GetX(float deg, float percent, uint32_t radius)
	{
	if      (deg > 270)	return 0.5 + CIRCLE_XPOS - percent * radius ;
	else if (deg > 180)	return 0.5 + CIRCLE_XPOS - percent * radius ;
	else if (deg >  90)	return 0.5 + CIRCLE_XPOS + percent * radius ;
	else				return 0.5 + CIRCLE_XPOS + percent * radius ;
	}

static uint32_t GetY(float deg, float percent, uint32_t radius)
	{
	if      (deg > 270)	return 0.5 + CIRCLE_YPOS - percent * radius ;
	else if (deg > 180)	return 0.5 + CIRCLE_YPOS + percent * radius ;
	else if (deg >  90)	return 0.5 + CIRCLE_YPOS + percent * radius ;
	else				return 0.5 + CIRCLE_YPOS - percent * radius ;
	}

static void UpdateCircle(uint32_t binary)
	{
	float sin1, sin2, sin3, cos1, cos2, cos3 ;
	static uint32_t x1, x2, x3, y1, y2, y3 ;
	static int32_t erase = 0 ; 
	float deg1, deg2, deg3 ;

	if (erase)
		{
		SetColor(COLOR_WHITE) ;
		FillTriangle(x1, x2, x3, y1, y2, y3) ;
		}
	erase = 1 ;

	deg1 = (binary * 360) / 256.0 - 7.0 ;
	deg2 = (binary * 360) / 256.0 + 0.0 ;
	deg3 = (binary * 360) / 256.0 + 7.0 ;

	if (deg1 <    0) deg1 += 360 ;
	if (deg3 >= 360) deg3 -= 360 ;

	sin1 = Sine(AcuteRadians(deg1)) ;
	sin2 = Sine(AcuteRadians(deg2)) ;
	sin3 = Sine(AcuteRadians(deg3)) ;

	cos1 = SquareRoot(1.0 - sin1*sin1) ;
	cos2 = SquareRoot(1.0 - sin2*sin2) ;
	cos3 = SquareRoot(1.0 - sin3*sin3) ;

	x1 = GetX(deg1, sin1, CIRCLE_INNER_RAD) ;
	x2 = GetX(deg2, sin2, CIRCLE_OUTER_RAD) ;
	x3 = GetX(deg3, sin3, CIRCLE_INNER_RAD) ;

	y1 = GetY(deg1, cos1, CIRCLE_INNER_RAD) ;
	y2 = GetY(deg2, cos2, CIRCLE_OUTER_RAD) ;
	y3 = GetY(deg3, cos3, CIRCLE_INNER_RAD) ;

	SetColor(REP_COLOR) ;
	FillTriangle(x1, x2, x3, y1, y2, y3) ;

	SetColor(COLOR_BLACK) ;
	DrawVLine(CIRCLE_XPOS, CIRCLE_YPOS - CIRCLE_OUTER_RAD - 5, 10) ;
	DrawHLine(CIRCLE_XPOS + CIRCLE_OUTER_RAD - 5, CIRCLE_YPOS, 10) ;
	DrawVLine(CIRCLE_XPOS, CIRCLE_YPOS + CIRCLE_OUTER_RAD - 5, 10) ;
	DrawHLine(CIRCLE_XPOS - CIRCLE_OUTER_RAD - 5, CIRCLE_YPOS, 10) ;
	}

static float Sine(float radians)
	{
	static float coef[] =
		{
		 0.0,					//  0/0!
		+1.0/(1),				// +1/1!
		 0.0,					//  0/2!
		-1.0/(3*2*1),			// -1/3!
		 0.0,					//  0/4!
		+1.0/(5*4*3*2*1),		// +1/5!
		 0.0,					//  0/6!
		-1.0/(7*6*5*4*3*2*1)	// -1/7!
		} ;
	float poly, *p ;
	uint32_t k ;

	poly = 0.0 ;
	p = &coef[ENTRIES(coef)] ;
	for (k = 0; k < ENTRIES(coef); k++)
		{
		poly = poly * radians + *--p ;
		}
	return poly ;
	}

static void InitializeDisplay(void)
	{
	SetColor(UNS_COLOR) ;
	DrawVLine(UBAR_X, UBAR_Y, UBAR_SIZE) ;
	SetFontSize(&ULBL_FONT) ;
	PutStringAt(ULBL_X, ULBL_Y, ULBL_TXT) ;
	SetFontSize(&UVAL_FONT) ;
	PutStringAt(UVAL_XMAX, UVAL_YTOP, UVAL_MAX) ;
	PutStringAt(UVAL_XMIN, UVAL_YBTM, UVAL_MIN) ;

	SetColor(SGN_COLOR) ;
	DrawVLine(SBAR_X, SBAR_Y, SBAR_SIZE) ;
	SetFontSize(&SLBL_FONT) ;
	PutStringAt(SLBL_X, SLBL_Y, SLBL_TXT) ;
	SetFontSize(&SVAL_FONT) ;
	PutStringAt(SVAL_XMAX, SVAL_YTOP, SVAL_MAX) ;
	PutStringAt(SVAL_XMIN, SVAL_YBTM, SVAL_MIN) ;

	SetColor(COLOR_BLACK) ;
	DrawCircle(CIRCLE_XPOS, CIRCLE_YPOS, CIRCLE_OUTER_RAD + 1) ;
	SetColor(REP_COLOR) ;
	SetFontSize(&REPLBL_FONT) ;
	PutStringAt(REPLBL_X, REPLBL_Y, REPLBL_TXT) ;
	SetFontSize(&REPVAL_FONT) ;
	PutStringAt(REP04TH_X, REP04TH_Y, REP04TH_TXT) ;
	PutStringAt(REP14TH_X, REP14TH_Y, REP14TH_TXT) ;
	PutStringAt(REP24TH_X, REP24TH_Y, REP24TH_TXT) ;
	PutStringAt(REP34TH_X, REP34TH_Y, REP34TH_TXT) ;
	}

static float SquareRoot(float radical)
	{
	float sqrt, error ;
	uint32_t k ;

	if (radical == 0.0) return 0.0 ;
	sqrt = 1.0 ;
	for (k = 0; k < 100; k++)
		{
		error = fabs(sqrt*sqrt - radical) ;
		if (error <= 0.00001) break ;
		sqrt = (radical / sqrt + sqrt) / 2.0 ;
    	}

	return sqrt ;
	}

static uint32_t GetTimeout(uint32_t msec)
	{
	uint32_t cycles = 1000 * msec * CPU_CLOCK_SPEED_MHZ ;
	return GetClockCycleCount() + cycles ;
	}

static void Delay(uint32_t msec)
	{
	uint32_t timeout = GetTimeout(msec) ;
	while ((int) (timeout - GetClockCycleCount()) > 0) ;
	}

static void PutStringAt(uint32_t x, uint32_t y, char *format, ...)
	{
	va_list args ;
	char text[100] ;

	va_start(args, format) ;
	vsprintf(text, format, args) ;
	va_end(args) ;

	DisplayStringAt(x, y, text) ;
	}

static void SetFontSize(sFONT *Font)
	{
	extern void BSP_LCD_SetFont(sFONT *) ;
	BSP_LCD_SetFont(Font) ;
	}

static void LEDs(int grn_on, int red_on)
	{
	static uint32_t * const pGPIOG_MODER	= (uint32_t *) 0x40021800 ;
	static uint32_t * const pGPIOG_ODR		= (uint32_t *) 0x40021814 ;
	
	*pGPIOG_MODER |= (1 << 28) | (1 << 26) ;	// output mode
	*pGPIOG_ODR &= ~(3 << 13) ;			// both off
	*pGPIOG_ODR |= (grn_on ? 1 : 0) << 13 ;
	*pGPIOG_ODR |= (red_on ? 1 : 0) << 14 ;
	}

static uint8_t Bits2Byte(int8_t bits[])
	{
	union { uint64_t u64; uint8_t u8[8]; } prod ;
	prod.u64 = 0x0102040810204080ULL * *((uint64_t *) bits) ;
	return prod.u8[7] ;
	}

static uint32_t BitPattern(int8_t bits[])
	{
	uint32_t pattern ;
	int32_t bit ;

	pattern = 0 ;
	for (bit = 7; bit >= 0; bit--)
		{
		pattern = 10*pattern + bits[bit] ;
		}
	return pattern ;
	}

static void Check(int8_t bits[], uint32_t ubinary, int32_t sbinary)
	{
	static uint32_t step = 0 ;
	int8_t test[8] ;

	Unsigned2Bits(step, test) ;
	if (Bits2Byte(test) != step)	Error(bits, ubinary, sbinary, "Unsigned2Bits") ;
	if (Bits2Byte(bits) != step)	Error(bits, ubinary, sbinary, "Increment") ;
	if (ubinary != step)			Error(bits, ubinary, sbinary, "Bits2Unsigned") ;
	if (sbinary >= 0)
		{
		if (sbinary != step)		Error(bits, ubinary, sbinary, "Bits2Signed") ;
		}
	else if (sbinary + 256 != step)	Error(bits, ubinary, sbinary, "Bits2Signed") ;
	step = (step + 1) & 0xFF ;
	}

static void Error(int8_t bits[], uint32_t ubinary, int32_t sbinary, char *cause)
	{
#	define	GFXROW1	54
#	define	GFXROWN	215
#	define	GFXROWS	(GFXROWN - GFXROW1 + 1)
	uint32_t width, row, col, chars ;

	chars = strlen("   Error: ") + strlen(cause) ;
	width = ERR_FONT.Width * (chars + 2) ;
	col = (XPIXELS - width) / 2 ;
	row = GFXROW1 + GFXROWS / 2 ;

	SetFontSize(&ERR_FONT) ;
	SetColor(ERR_BGND_COLOR) ;
	FillRect(col + 1, row, width - 1, 5*ERR_FONT.Height) ;
	SetColor(ERR_BRDR_COLOR) ;
	DrawRect(col, row, width, 5*ERR_FONT.Height) ;
	row += ERR_FONT.Height/2 ;

	SetForeground(ERR_FGND_COLOR) ;
	SetBackground(ERR_BGND_COLOR) ;
	PutStringAt(col + ERR_FONT.Width, row, "   Error: %s", cause) ;
	row += ERR_FONT.Height ;
	PutStringAt(col + ERR_FONT.Width, row, "    Bits: %08u", BitPattern(bits)) ;
	row += ERR_FONT.Height ; 
	PutStringAt(col + ERR_FONT.Width, row, "Unsigned: %u", ubinary) ;
	row += ERR_FONT.Height ;
	PutStringAt(col + ERR_FONT.Width, row, "  Signed: %d", sbinary) ;

	LEDs(0, 1) ;
	for (;;) ;
	}



