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
#include "touch.h"

extern int	Addition(int op1, int op2) ;
extern int	Subtraction(int op1, int op2) ;
extern int	Multiplication(int op1, int op2) ;
extern int	Division(int op1, int op2) ;

typedef int BOOL ;
#define	FALSE	0
#define	TRUE	1

typedef enum {RELEASED=0, PRESSED=1, SELECTED=2, ERROR=3} BUTTON_STATE ;

typedef struct
	{
	char		*label ;
	int			xmin ;
	int			ymin ;
	BOOL		(*func)() ;
	int			value ;
	int			minRadix ;
	} BUTTON ;

// Public fonts defined in run-time library
typedef struct
	{
	const uint8_t *	table ;
	const uint16_t	Width ;
	const uint16_t	Height ;
	} sFONT ;

extern sFONT Font8, Font12, Font16, Font20, Font24 ;

#define	HEADER_YSIZE	48
#define	FOOTER_YSIZE	15

#define	OFFSET_X		0
#define	OFFSET_Y		HEADER_YSIZE

#define	SPACING_X		7
#define	SPACING_Y		6

#define	PADDING_X		5
#define	PADDING_Y		6

#define	DISPLAY_XPOS	PADDING_X
#define	DISPLAY_YPOS	(OFFSET_Y + PADDING_Y)

#define	DISPLAY_XSIZE	(XPIXELS - 2*PADDING_X)
#define	DISPLAY_YSIZE	43

#define	BUTTON_XOFF		PADDING_X
#define	BUTTON_YOFF		(DISPLAY_YPOS + DISPLAY_YSIZE + SPACING_Y)

#define	BUTTON_COLS		5
#define	BUTTON_ROWS		5

#define	BUTTON_XSIZE	40
#define	BUTTON_YSIZE	34

#define	DISPLAY_FGND	COLOR_BLACK
#define	DISPLAY_BGND	COLOR_WHITE
#define	DISPLAY_BRDR	COLOR_BLACK
#define	DISPLAY_ERR		COLOR_RED

#define	BUTTON_FG_OFF	COLOR_BLACK
#define	BUTTON_BG_OFF	COLOR_WHITE
#define	BUTTON_BD_OFF	COLOR_BLACK

#define	BUTTON_FG_ON	COLOR_BLACK
#define	BUTTON_BG_ON	COLOR_GREEN
#define	BUTTON_BD_ON	COLOR_BLACK

#define	BUTTON_FG_ERR	COLOR_WHITE
#define	BUTTON_BG_ERR	COLOR_RED
#define	BUTTON_BD_ERR	COLOR_BLACK

#define	BUTTON_FG_SEL	COLOR_BLACK
#define	BUTTON_BG_SEL	COLOR_LIGHTYELLOW
#define	BUTTON_BD_SEL	COLOR_BLACK

#define	BUTTON_DEC		buttons[4][0]
#define	BUTTON_HEX		buttons[4][1]
#define	BUTTON_BIN		buttons[4][2]
#define	BUTTON_EQU		buttons[4][4]

#define	BUTTON_LFNT		Font20
#define	BUTTON_SFNT		Font16
#define	OP1_FONT		Font16
#define	OP2_FONT		Font24

// Private functions defined in this file
static BUTTON *	ButtonTouched(int x, int y) ;
static void		Delay(uint32_t msec) ;
static void		DrawButton(BUTTON *button, BUTTON_STATE state) ;
static void		DrawCalculator(void) ;
static uint32_t GetTimeout(uint32_t msec) ;
static void		InitializeTouchScreen(void) ;
static int		Null(void) ;
static char *	Num2Text(int op, char *text, int radix) ;
static void		Op(int (*func)(int op1, int op2), char *symbol) ;
static void		Reverse(char *str) ;
static void		SetFontSize(sFONT *pFont) ;
static void		UpdateDisplay(BOOL divBy0) ;

static BOOL		BtnDigit(int) ;
static BOOL		BtnSUB(void) ;
static BOOL		BtnMUL(void) ;
static BOOL		BtnDIV(void) ;
static BOOL		BtnRadix(int) ;
static BOOL		BtnEquals(void) ;
static BOOL		BtnBackSpace(void) ;
static BOOL		BtnADD(void) ;

#define	BTNX(col)	(BUTTON_XOFF + col*(BUTTON_XSIZE + SPACING_X))
#define	BTNY(row)	(BUTTON_YOFF + row*(BUTTON_YSIZE + SPACING_Y))

static int op1 = 0 ;
static int op2 = 0 ;
static char line1[100] = "" ;
static char *symbol = "" ;
static int (*function)() = Null ;
static int radix = 10 ;

static BUTTON buttons[BUTTON_ROWS][BUTTON_COLS] =
	{
		{
			{"C",	BTNX(0), BTNY(0),	BtnDigit, 0xC,	 16},
			{"D",	BTNX(1), BTNY(0),	BtnDigit, 0xD,	 16},
			{"E",	BTNX(2), BTNY(0),	BtnDigit, 0xE,	 16},
			{"F",	BTNX(3), BTNY(0),	BtnDigit, 0xF,	 16},
			{"+",	BTNX(4), BTNY(0),	BtnADD,	  0x0,	  0}
		},
		{
			{"8",	BTNX(0), BTNY(1),	BtnDigit, 0x8,	 10},
			{"9",	BTNX(1), BTNY(1),	BtnDigit, 0x9,	 10},
			{"A",	BTNX(2), BTNY(1),	BtnDigit, 0xA,	 16},
			{"B",	BTNX(3), BTNY(1),	BtnDigit, 0xB,	 16},
			{"-",	BTNX(4), BTNY(1),	BtnSUB,	  0x0,	  0}
		},
		{
			{"4",	BTNX(0), BTNY(2),	BtnDigit, 0x4,	 10},
			{"5",	BTNX(1), BTNY(2),	BtnDigit, 0x5,	 10},
			{"6",	BTNX(2), BTNY(2),	BtnDigit, 0x6,	 10},
			{"7",	BTNX(3), BTNY(2),	BtnDigit, 0x7,	 10},
			{"*",	BTNX(4), BTNY(2),	BtnMUL,	  0x0,	  0}
		},
		{
			{"0",	BTNX(0), BTNY(3),	BtnDigit, 0x0,	  2},
			{"1",	BTNX(1), BTNY(3),	BtnDigit, 0x1,	  2},
			{"2",	BTNX(2), BTNY(3),	BtnDigit, 0x2,	 10},
			{"3",	BTNX(3), BTNY(3),	BtnDigit, 0x3,	 10},
			{"/",	BTNX(4), BTNY(3),	BtnDIV,	  0x0,	  0}
		},
		{
			{"DEC", BTNX(0), BTNY(4),	BtnRadix, 10,	-10},
			{"HEX", BTNX(1), BTNY(4),	BtnRadix, 16,	-16},
			{"BIN", BTNX(2), BTNY(4),	BtnRadix,  2,	 -2},
			{"BSp",  BTNX(3), BTNY(4),	BtnBackSpace,	  0x0,	  0},
			{"=",	BTNX(4), BTNY(4),	BtnEquals,0x0,	  0}
		}
	} ;

int main(void)
	{
	InitializeHardware(HEADER, "Lab 0: 16-bit Calculator") ;
	InitializeTouchScreen() ;

	DrawCalculator() ;
	DrawButton(&BUTTON_DEC, SELECTED) ;
	for (;;)
		{
		if (TS_Touched())
			{
			BUTTON *button = ButtonTouched(TS_GetX(), TS_GetY() ) ;

			if (button != NULL)
				{
				BUTTON_STATE state ;
				BOOL divBy0 ;

				if (button != &BUTTON_EQU) divBy0 = FALSE ;
				else divBy0 = (function == Division) && !op2 ;

				state = (*button->func)(button->value) ? PRESSED : ERROR ;
				DrawButton(button, state) ;
				do Delay(100) ; while (TS_Touched()) ;
				state = (button->minRadix == -radix) ? SELECTED : RELEASED ;
				DrawButton(button, state) ;

				UpdateDisplay(divBy0) ;
				}
			}
		}

	return 0 ;
	}

static BUTTON *ButtonTouched(int x, int y)
	{
	int row, col ;

	for (row = 0; row < BUTTON_ROWS; row++)
		{
		BUTTON *b = buttons[row] ;
		for (col = 0; col < BUTTON_COLS; col++, b++)
			{
			if (x < b->xmin) continue ;
			if (y < b->ymin) continue ;
			if (x >= b->xmin + BUTTON_XSIZE) continue ;
			if (y >= b->ymin + BUTTON_YSIZE) continue ;
			return b ;
			}
		}

	return NULL ;
	}

static void DrawButton(BUTTON *button, BUTTON_STATE state)
	{
	static uint32_t fgnd[] = {BUTTON_FG_OFF, BUTTON_FG_ON, BUTTON_FG_SEL, BUTTON_FG_ERR} ;
	static uint32_t bgnd[] = {BUTTON_BG_OFF, BUTTON_BG_ON, BUTTON_BG_SEL, BUTTON_BG_ERR} ;
	static uint32_t brdr[] = {BUTTON_BD_OFF, BUTTON_BD_ON, BUTTON_BD_SEL, BUTTON_BD_ERR} ;
	sFONT *font = (strlen(button->label) > 1) ? &BUTTON_SFNT : &BUTTON_LFNT ;
	int x, y ;

	SetColor(bgnd[state]) ;
	FillRect(button->xmin, button->ymin, BUTTON_XSIZE, BUTTON_YSIZE) ;
	SetColor(brdr[state]) ;
	DrawRect(button->xmin, button->ymin, BUTTON_XSIZE, BUTTON_YSIZE) ;

	SetFontSize(font) ;
	SetForeground(fgnd[state]) ;
	SetBackground(bgnd[state]) ;
	x = button->xmin + (BUTTON_XSIZE - font->Width*strlen(button->label)) / 2 ;
	y = button->ymin + (BUTTON_YSIZE - font->Height) / 2 + 1 ; 
	DisplayStringAt(x, y, button->label) ;
	}

static void DrawCalculator(void)
	{
	int row, col ;

	SetColor(COLOR_LIGHTGRAY) ;
	FillRect(0, OFFSET_Y, XPIXELS, YPIXELS - HEADER_YSIZE - FOOTER_YSIZE) ;

	SetColor(DISPLAY_BGND) ;
	FillRect(DISPLAY_XPOS, DISPLAY_YPOS, DISPLAY_XSIZE, DISPLAY_YSIZE) ;

	SetColor(DISPLAY_BRDR) ;
	DrawRect(DISPLAY_XPOS, DISPLAY_YPOS, DISPLAY_XSIZE - 1, DISPLAY_YSIZE) ;

	for (row = 0; row < BUTTON_ROWS; row++)
		{
		for (col = 0; col < BUTTON_COLS; col++)
			{
			DrawButton(&buttons[row][col], FALSE) ;
			}
		}
	UpdateDisplay(FALSE) ;
	}

static void UpdateDisplay(BOOL divBy0)
	{
	static char prev1[100] = "" ;
	static char line2[100] = "" ;
	static sFONT *prev2 = &OP2_FONT ;
	int y1 = DISPLAY_YPOS + 1  ;
	int y2 = y1 + OP1_FONT.Height ;
	sFONT *font2 = (radix == 2 && !divBy0) ? &OP1_FONT : &OP2_FONT ;
	int x ;

	SetBackground(DISPLAY_BGND) ;

	SetForeground(DISPLAY_BGND) ;
	SetFontSize(&OP1_FONT) ;
	x = DISPLAY_XPOS + DISPLAY_XSIZE - OP1_FONT.Width*strlen(prev1) - 4 ;
	DisplayStringAt(x, y1, prev1) ;
	x = DISPLAY_XPOS + DISPLAY_XSIZE - OP1_FONT.Width*strlen(line1) - 4 ;
	SetForeground(DISPLAY_FGND) ;
	DisplayStringAt(x, y1, line1) ;
	strcpy(prev1, line1) ;

	SetForeground(DISPLAY_BGND) ;
	SetFontSize(prev2) ;
	x = DISPLAY_XPOS + DISPLAY_XSIZE - prev2->Width*strlen(line2) - 4 ;
	DisplayStringAt(x, y2, line2) ;
	if (divBy0) sprintf(line2, "Divide by 0 ") ;
	else Num2Text(op2, line2, radix) ;
	SetFontSize(font2) ;
	x = DISPLAY_XPOS + DISPLAY_XSIZE - font2->Width*strlen(line2) - 4 ;
	SetForeground(divBy0 ? DISPLAY_ERR : DISPLAY_FGND) ;
	DisplayStringAt(x, y2, line2) ;
	prev2 = font2 ;
	}

static void SetFontSize(sFONT *Font)
	{
	extern void BSP_LCD_SetFont(sFONT *) ;
	BSP_LCD_SetFont(Font) ;
	}

static void InitializeTouchScreen(void)
	{
	static char *message[] =
		{
		"If this message remains on",
		"the screen, there is an",
		"initialization problem with",
		"the touch screen. This does",
		"NOT mean that there is a",
		"problem with your code.",
		" ",
		"To correct the problem,",
		"disconnect and reconnect",
		"the power.",
		NULL
		} ;
	char **pp ;
	unsigned x, y ;

	x = 25 ;
	y = 100 ;
	for (pp = message; *pp != NULL; pp++)
		{
		DisplayStringAt(x, y, *pp) ;
		y += 12 ;
		}
	TS_Init() ;
	ClearDisplay() ;
	}

static uint32_t GetTimeout(uint32_t msec)
	{
#	define	CPU_CLOCK_SPEED_MHZ			168
	uint32_t cycles = 1000 * msec * CPU_CLOCK_SPEED_MHZ ;
	return GetClockCycleCount() + cycles ;
	}

static void Delay(uint32_t msec)
	{
	uint32_t timeout = GetTimeout(msec) ;
	while ((int) (timeout - GetClockCycleCount()) > 0) ;
	}

static int Null(void)
	{
	return op2 ;
	}

static void Op(int (*func)(int, int), char *symb)
	{
	if (strlen(line1) > 0) BtnEquals() ;
	function = func ;
	symbol = symb ;
	op1 = op2 ;	op2 = 0 ;
	Num2Text(op1, line1, radix) ;
	strcat(line1, symb) ;
	}

static BOOL BtnDigit(int digit)
	{
	int n = radix*op2 + digit ;
	if (digit >= radix) return FALSE ;
	if (n > UINT16_MAX) return FALSE ;
	op2 = n & 0xFFFF ;
	return TRUE ;
	}

static BOOL	BtnADD(void)	{ Op(Addition,			"+") ; return TRUE ; }
static BOOL	BtnSUB(void)	{ Op(Subtraction,		"-") ; return TRUE ; }
static BOOL	BtnMUL(void)	{ Op(Multiplication,	"*") ; return TRUE ; }
static BOOL	BtnDIV(void)	{ Op(Division,			"/") ; return TRUE ; }

static BOOL	BtnRadix(int r)
	{
	radix = 0 ;
	DrawButton(&BUTTON_DEC, RELEASED) ;
	DrawButton(&BUTTON_HEX, RELEASED) ;
	DrawButton(&BUTTON_BIN, RELEASED) ;
	radix = r ;
	return TRUE ;
	}

static BOOL	BtnBackSpace(void)
	{
	op2 /= radix ;
	return TRUE ;
	}

static BOOL	BtnEquals(void)
	{
	strcpy(line1, "") ;
	op2 = (*function)(op1, op2) ;
	op1 = 0 ;
	function = Null ;
	return TRUE ;
	}

static char *Num2Text(int op, char *text, int radix)
	{
	int bit, digits ;
	char *p, *sign ;

	sign = "" ;
	p = text ;
	switch (radix)
		{
		case  2:
			digits = 16 ;
			break ;
		case 10:
		default:
			if (op < 0)
				{
				sign = "-" ;
				op = -op ;
				}
			digits =  5 ;
			break ;
		case 16:
			digits =  4 ;
			break ;
		}

	op &= 0xFFFF ;
	for (bit = 1; bit <= digits; bit++)
		{
		*p++ = "0123456789ABCDEF"[op % radix] ;
		op /= radix ;
		if (op == 0) break ;
		if (radix == 2 && (bit % 4) == 0) *p++ = ' ' ;
		}
	*p = '\0' ;

	strcat(text, sign) ;
	Reverse(text) ;
	return text ;
	}

static void Reverse(char *str)
	{
	int i, j ;
	char a;
	unsigned len ;

	len = strlen(str);
	for (i = 0, j = len - 1; i < j; i++, j--)
		{
		a = str[i];
		str[i] = str[j];
		str[j] = a;
		}
	}


