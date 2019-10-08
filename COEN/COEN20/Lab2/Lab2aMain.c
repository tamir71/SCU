/*
	This code was written to support the book, "ARM Assembly for Embedded Applications",
	by Daniel W. Lewis. Permission is granted to freely share this software provided
	that this notice is not removed. This software is intended to be used with a run-time
    library adapted by the author from the STM Cube Library for the 32F429IDISCOVERY 
    board and available for download from http://www.engr.scu.edu/~dlewis/book3.
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "library.h"
#include "graphics.h"

extern int32_t Less1(int32_t x) ;
extern int32_t Add(int32_t x, int32_t y) ;
extern int32_t Square2x(int32_t x) ;
extern int32_t Last(int32_t x) ;

// Public fonts defined in run-time library
typedef struct
	{
	const uint8_t *	table ;
	const uint16_t	Width ;
	const uint16_t	Height ;
	} sFONT ;

typedef struct
	{
	int	x, y ;
	} TEST ;

typedef enum	{LEFT, CENTER, RIGHT, ABOVE, BELOW} ALIGN ;
typedef enum	{FALSE=0, TRUE=1} BOOL ;

extern sFONT	Font8, Font12, Font16, Font20, Font24 ;

static sFONT	*font = &Font12 ;

static void		DisplayProgress(int which, int count) ;
static void		DrawVArrow(int x, int y_fm, int y_to) ;
static void		DrawHArrow(int y, int x_fm, int x_to) ;
static void		FillBox(int x, int y, char *lbl, BOOL ok) ;
static void		LEDs(BOOL grn_on, BOOL red_on) ;
static void		PaintBox(int x, int y, char *lbl, int fg_color, int bg_color) ;
static void		PutStringAt(int x, int y, char *fmt, ...) ;
static void		PutValueAt(int x, int y, char *text, ALIGN align) ;
static void		SetFontSize(sFONT *pFont) ;
static char *	String(int n) ;
static int32_t 	_SquareRoot(int32_t n) ;

#define	BOX_HEIGHT	55
#define	BOX_WIDTH	55
#define	BOX_HSPACE	((XPIXELS - 3*BOX_WIDTH - 4)/2)
#define	BOX_VSPACE	35

#define	PROGRESS_Y	75

#define	ROW1_YMIN	105
#define	ROW2_YMIN	(ROW1_YMIN + BOX_HEIGHT + BOX_VSPACE)

#define	COL1_XMIN	2
#define	COL2_XMIN	(COL1_XMIN + BOX_WIDTH + BOX_HSPACE)
#define	COL3_XMIN	(COL2_XMIN + BOX_WIDTH + BOX_HSPACE)

#define	INPUT1_X	(COL1_XMIN + BOX_WIDTH/2)
#define	INPUT1_Y	(ROW1_YMIN - BOX_VSPACE)

#define	INPUT2_X	INPUT1_X
#define	INPUT2_Y	(ROW2_YMIN + BOX_HEIGHT + BOX_VSPACE)

#define	OUTPUT3_X	(COL3_XMIN + BOX_WIDTH/2)
#define	OUTPUT3_Y	(ROW1_YMIN - BOX_VSPACE)

#define	TEMP1_X		(COL1_XMIN + BOX_WIDTH/2)
#define	TEMP1_Y		(ROW2_YMIN - BOX_VSPACE/2)

#define	TEMP2_X		(COL1_XMIN + BOX_WIDTH + BOX_HSPACE/2)
#define	TEMP2_Y		(ROW1_YMIN + BOX_HEIGHT/2)

#define	TEMP3_X		(COL2_XMIN + BOX_WIDTH + BOX_HSPACE/2)
#define	TEMP3_Y		(ROW1_YMIN + BOX_HEIGHT/2)

#define	INPUT3_X	(COL2_XMIN + BOX_WIDTH/3)
#define	INPUT3_Y	(ROW2_YMIN - BOX_VSPACE/2)

#define	OUTPUT1_X	(COL2_XMIN + 2*BOX_WIDTH/3)
#define	OUTPUT1_Y	(ROW2_YMIN - BOX_VSPACE/2)

#define	INPUT4_X	(COL3_XMIN + BOX_WIDTH/3)
#define	INPUT4_Y	(ROW2_YMIN - BOX_VSPACE/2)

#define	OUTPUT2_X	(COL3_XMIN + 2*BOX_WIDTH/3)
#define	OUTPUT2_Y	(ROW2_YMIN - BOX_VSPACE/2)

#define	ENTRIES(a)	(sizeof(a)/sizeof(a[0]))

int main(void)
	{
	static TEST tests[] =
		{
		{+1, +1}, {-1, -1}, {+2, -3}, {-3, +2}, {+4, +5},
		{-4, -5}, {+6, -7}, {+7, -6}, {+8, +9}, {-9, -8}
		} ;
	int x, y, z, t1, t2, t3, which ;
	BOOL ok ;

	InitializeHardware(HEADER, "Lab 2a: Functions & Parameters") ;
	LEDs(TRUE, FALSE) ;

	PaintBox(COL1_XMIN, ROW2_YMIN, "x-1", COLOR_BLACK, COLOR_LIGHTGRAY) ;
	PaintBox(COL1_XMIN, ROW1_YMIN, "Add", COLOR_BLACK, COLOR_LIGHTGRAY) ;
	PaintBox(COL2_XMIN, ROW1_YMIN, "2x*2x", COLOR_BLACK, COLOR_LIGHTGRAY) ;
	PaintBox(COL3_XMIN, ROW1_YMIN, "x+SR(x)", COLOR_BLACK, COLOR_LIGHTGRAY) ;
	PaintBox(COL2_XMIN, ROW2_YMIN, "x*x", COLOR_BLACK, COLOR_LIGHTGRAY) ;
	PaintBox(COL3_XMIN, ROW2_YMIN, "sqrt", COLOR_BLACK, COLOR_LIGHTGRAY) ;

	DrawHArrow(ROW1_YMIN + BOX_HEIGHT/2, COL1_XMIN + BOX_WIDTH, COL2_XMIN) ;
	DrawHArrow(ROW1_YMIN + BOX_HEIGHT/2, COL2_XMIN + BOX_WIDTH, COL3_XMIN) ;
	DrawVArrow(COL1_XMIN + BOX_WIDTH/2, ROW2_YMIN, ROW1_YMIN + BOX_HEIGHT) ;
	DrawVArrow(COL2_XMIN + 1*BOX_WIDTH/3, ROW1_YMIN + BOX_HEIGHT, ROW2_YMIN) ;
	DrawVArrow(COL2_XMIN + 2*BOX_WIDTH/3, ROW2_YMIN, ROW1_YMIN + BOX_HEIGHT) ;
	DrawVArrow(COL3_XMIN + 1*BOX_WIDTH/3, ROW1_YMIN + BOX_HEIGHT, ROW2_YMIN) ;
	DrawVArrow(COL3_XMIN + 2*BOX_WIDTH/3, ROW2_YMIN, ROW1_YMIN + BOX_HEIGHT) ;
	DrawVArrow(COL1_XMIN + BOX_WIDTH/2, ROW1_YMIN - BOX_VSPACE, ROW1_YMIN) ;
	DrawVArrow(COL3_XMIN + BOX_WIDTH/2, ROW1_YMIN, ROW1_YMIN - BOX_VSPACE) ;
	DrawVArrow(COL1_XMIN + BOX_WIDTH/2, ROW2_YMIN + BOX_HEIGHT + BOX_VSPACE, ROW2_YMIN + BOX_HEIGHT) ;

	PutValueAt(TEMP1_X, TEMP1_Y, "?", LEFT) ;
	PutValueAt(TEMP2_X, TEMP2_Y, "?", ABOVE) ;
	PutValueAt(TEMP3_X, TEMP3_Y, "?", ABOVE) ;
	PutValueAt(OUTPUT3_X, OUTPUT3_Y, "?", ABOVE) ;
	PutValueAt(INPUT3_X, INPUT3_Y, "?", RIGHT) ;
	PutValueAt(OUTPUT1_X, OUTPUT1_Y, "?", LEFT) ;
	PutValueAt(INPUT4_X, INPUT4_Y, "?", RIGHT) ;
	PutValueAt(OUTPUT2_X, OUTPUT2_Y, "?", LEFT) ;

	which = 0;
	for (;;)
		{
		DisplayProgress(which, ENTRIES(tests)) ;

		x = tests[which].x ;
		PutValueAt(INPUT1_X, INPUT1_Y, String(x), ABOVE) ;
		y = tests[which].y ;
		PutValueAt(INPUT2_X, INPUT2_Y, String(y), BELOW) ;

		PaintBox(COL1_XMIN, ROW2_YMIN, "x-1", COLOR_BLACK, COLOR_ORANGE) ;
		t1 = Less1(y) ; ok = (t1 == y - 1) ;
		FillBox(COL1_XMIN, ROW2_YMIN, "x-1", ok) ;
		PutValueAt(TEMP1_X, TEMP1_Y, String(t1), LEFT) ;

		PaintBox(COL1_XMIN, ROW1_YMIN, "Add", COLOR_BLACK, COLOR_ORANGE) ;
		t2 = Add(x, t1) ; ok = (t2 == x + t1) ;
		FillBox(COL1_XMIN, ROW1_YMIN, "Add", ok) ;
		PutValueAt(TEMP2_X, TEMP2_Y, String(t2), ABOVE) ;

		PaintBox(COL2_XMIN, ROW1_YMIN, "2x*2x", COLOR_BLACK, COLOR_ORANGE) ;
		t3 = Square2x(t2) ; ok = (t3 == 4*t2*t2) ;
		FillBox(COL2_XMIN, ROW1_YMIN, "2x*2x", ok) ;
		PutValueAt(TEMP3_X, TEMP3_Y, String(t3), ABOVE) ;

		PaintBox(COL3_XMIN, ROW1_YMIN, "x+SR(x)", COLOR_BLACK, COLOR_ORANGE) ;
		z = Last(t3) ; ok = (z == t3 + _SquareRoot(t3)) ;
		FillBox(COL3_XMIN, ROW1_YMIN, "x+SR(x)", ok) ;
		PutValueAt(OUTPUT3_X, OUTPUT3_Y, String(z), ABOVE) ;

		WaitForPushButton() ;
		which = (which + 1) % ENTRIES(tests) ;
		}

	return 0 ;
	}

int Square(int x)
	{
	int square = x * x ;
	PaintBox(COL2_XMIN, ROW2_YMIN, "x*x", COLOR_BLACK, COLOR_YELLOW) ;
	PutValueAt(INPUT3_X, INPUT3_Y, String(x), RIGHT) ;
	PutValueAt(OUTPUT1_X, OUTPUT1_Y, String(square), LEFT) ;
	return square ;
	}

int32_t SquareRoot(int32_t n)
	{
	int32_t root ;

	PaintBox(COL3_XMIN, ROW2_YMIN, "sqrt", COLOR_BLACK, COLOR_YELLOW) ;
	PutValueAt(INPUT4_X, INPUT4_Y, String(n), RIGHT) ;
	root = _SquareRoot(n) ;
	PutValueAt(OUTPUT2_X, OUTPUT2_Y, String(root), LEFT) ;
	return root ;
	}

static int32_t _SquareRoot(int32_t n)
	{
	int32_t smallCandidate, largeCandidate ;

	if (n < 2) return n ;

	// Recursive call:
	smallCandidate = 2 * _SquareRoot(n / 4) ;
	largeCandidate = smallCandidate + 1 ;

	if (largeCandidate * largeCandidate > n) return smallCandidate ;
	return largeCandidate ;
	}

static void DisplayProgress(int which, int count)
	{
	char text[100] ;

	sprintf(text, " Test %d of %d ", which + 1, count) ;
	SetFontSize(&Font16) ;
	SetForeground(COLOR_BLACK) ;
	SetBackground(COLOR_WHITE) ;
	PutStringAt((XPIXELS - font->Width * strlen(text)) / 2, PROGRESS_Y, text) ;
	}

static char *String(int n)
	{
	static char text[20] ;
	sprintf(text, "%d", n) ;
	return text ;
	}

static void PutValueAt(int x, int y, char *text, ALIGN align)
	{
	char erase[] = "    " ;
	int width, save ;

	SetFontSize(&Font12) ;

	save = x ;
	width = strlen(erase) * font->Width ;
	switch (align)
		{
		case RIGHT:		x -= width + 2;	y -= font->Height/2;	break ;
		case CENTER:	x -= width/2;	y -= font->Height/2;	break ;
		case LEFT:		x += 2;			y -= font->Height/2;	break ;
		case ABOVE:		x -= width/2;	y -= font->Height + 2;	break ;
		case BELOW:		x -= width/2;	y += 2;					break ;
		}
	SetForeground(COLOR_BLACK) ;
	SetBackground(COLOR_WHITE) ;
	PutStringAt(x, y, erase) ;

	x = save ;
	width = strlen(text) * font->Width ;
	switch (align)
		{
		case RIGHT:		x -= width + 2;	break ;
		case CENTER:	x -= width/2;	break ;
		case LEFT:		x += 2;			break ;
		case ABOVE:		x -= width/2;	break ;
		case BELOW:		x -= width/2;	break ;
		}
	PutStringAt(x, y, text) ;
	}

static void FillBox(int x, int y, char *lbl, BOOL ok)
	{
	int fg_color = ok ? COLOR_BLACK : COLOR_WHITE ;
	int bg_color = ok ? COLOR_LIGHTGREEN : COLOR_RED ;

	if (!ok) LEDs(FALSE, TRUE) ;
	PaintBox(x, y, lbl, fg_color, bg_color) ;
	}

static void PaintBox(int x, int y, char *lbl, int fg_color, int bg_color)
	{
	SetForeground(bg_color) ;
	FillRect(x, y, BOX_WIDTH, BOX_HEIGHT) ;
	SetForeground(COLOR_BLACK) ;
	DrawRect(x, y, BOX_WIDTH, BOX_HEIGHT) ;
	SetFontSize(&Font12) ;
	x += (BOX_WIDTH - font->Width*strlen(lbl))/2 ;
	y += (BOX_HEIGHT - font->Height)/2 ;
	SetForeground(fg_color) ;
	SetBackground(bg_color) ;
	PutStringAt(x, y, lbl) ;
	}

static void DrawVArrow(int x, int y_fm, int y_to)
	{
	SetColor(COLOR_BLACK) ;
	if (y_fm < y_to)
		{
		DrawVLine(x, y_fm, y_to - y_fm) ;
		FillTriangle(x, x-3, x+3, y_to, y_to-5, y_to-5) ;
		}
	else
		{
		DrawVLine(x, y_to, y_fm - y_to) ;
		FillTriangle(x, x-3, x+3, y_to, y_to+5, y_to+5) ;
		}
	}

static void DrawHArrow(int y, int x_fm, int x_to)
	{
	SetColor(COLOR_BLACK) ;
	if (x_fm < x_to)
		{
		DrawHLine(x_fm, y, x_to - x_fm) ;
		FillTriangle(x_to, x_to-5, x_to-5, y, y-3, y+3) ;
		}
	else
		{
		DrawHLine(x_to, y, x_fm - x_to) ;
		FillTriangle(x_to, x_to+5, x_to+5, y, y-3, y+3) ;
		}
	}

static void PutStringAt(int x, int y, char *fmt, ...)
	{
	va_list args ;
	char text[100] ;

	va_start(args, fmt) ;
	vsprintf(text, fmt, args) ;
	va_end(args) ;

	DisplayStringAt(x, y, text) ;
	}

static void SetFontSize(sFONT *Font)
	{
	extern void BSP_LCD_SetFont(sFONT *) ;
	BSP_LCD_SetFont(Font) ;
	font = Font ;
	}

static void LEDs(BOOL grn_on, BOOL red_on)
	{
	static uint32_t * const pGPIOG_MODER	= (uint32_t *) 0x40021800 ;
	static uint32_t * const pGPIOG_ODR		= (uint32_t *) 0x40021814 ;
	
	*pGPIOG_MODER |= (1 << 28) | (1 << 26) ;	// output mode
	*pGPIOG_ODR &= ~(3 << 13) ;			// both off
	*pGPIOG_ODR |= (grn_on ? 1 : 0) << 13 ;
	*pGPIOG_ODR |= (red_on ? 1 : 0) << 14 ;
	}

