%{
/*
 * File:	lexer.l
 *
 * Description:	This file contains the flex description for the lexical
 *		analyzer for Simple C.
 *
 *		Extra functionality:
 *		- checking for out of range integer literals
 *		- checking for invalid string literals
 */

# include <cerrno>
# include <cstdio>
# include <cstdlib>
# include <iostream>
# include "string.h"
# include "lexer.h"


/* This used to be a function, but students wouldn't remove the definition
   when they moved to the next phase, even though the function wasn't used
   anymore and they'd get a warning telling them that.  It annoyed me. */

# define printToken(s)	(cout << s << " " << yytext << endl)


using namespace std;

int numerrors = 0;
static void checkInteger();
static void checkString();
static void ignoreComment();
%}

%option nounput noyywrap yylineno
%%

"/*"										{ignoreComment();}

"auto"										{printToken("AUTO");}
"break"										{printToken("BREAK");}
"case"										{printToken("CASE");}
"char"										{printToken("CHAR");}
"const"										{printToken("CONST");}
"continue"									{printToken("CONTINUE");}
"default"									{printToken("DEFAULT");}
"do"										{printToken("DO");}
"double"									{printToken("DOUBLE");}
"else"										{printToken("ELSE");}
"enum"										{printToken("ENUM");}
"extern"									{printToken("EXTERN");}
"float"										{printToken("FLOAT");}
"for"										{printToken("FOR");}
"goto"										{printToken("GOTO");}
"if"										{printToken("IF");}
"int"										{printToken("INT");}
"long"										{printToken("LONG");}
"register"									{printToken("REGISTER");}
"return"									{printToken("RETURN");}
"short"										{printToken("SHORT");}
"signed"									{printToken("SIGNED");}
"sizeof"									{printToken("SIZEOF");}
"static"									{printToken("STATIC");}
"struct"									{printToken("STRUCT");}
"switch"									{printToken("SWITCH");}
"typedef"									{printToken("TYPEDEF");}
"union"										{printToken("UNION");}
"unsigned"									{printToken("UNSIGNED");}
"void"										{printToken("VOID");}
"volatile"									{printToken("VOLATILE");}
"while"										{printToken("WHILE");}

"||"										{printToken("OR");}
"&&"										{printToken("AND");}
"=="										{printToken("EQ");}
"!="										{printToken("NEQ");}
"<="										{printToken("LEQ");}
">="										{printToken("GEQ");}
"++"										{printToken("INC");}
"--"										{printToken("DEC");}
"->"										{printToken("PTR");}
[-|=<>+*/%&!()\[\]{};:.,]					{printToken(*yytext);}

[a-zA-Z_][a-zA-Z_0-9]*						{printToken("ID");}

[0-9]+										{checkInteger(); printToken("INT");}
\"(\\.|[^\\\n"])*\"							{checkString(); printToken("STRING");}

[ \f\n\r\t\v]+								{/* ignored */}
.											{cerr << "oops: " << yytext << endl; /* ignored */}

%%

/*
 * Function:	ignoreComment
 *
 * Description:	Ignore a comment after recognizing its beginning.
 */

static void ignoreComment()
{
    int c1, c2;


    while ((c1 = yyinput()) != 0) {
	while (c1 == '*') {
	    if ((c2 = yyinput()) == '/' || c2 == 0)
		return;

	    c1 = c2;
	}
    }

    if (c1 == 0)
	report("unterminated comment");
}


/*
 * Function:	checkInteger
 *
 * Description:	Check if an integer constant is valid.
 */

static void checkInteger()
{
    errno = 0;
    strtol(yytext, NULL, 0);

    if (errno != 0)
	report("integer constant too large");
}


/*
 * Function:	checkString
 *
 * Description:	Check if a string literal is valid.
 */

static void checkString()
{
    bool invalid, overflow;


    parseString(yytext, invalid, overflow);

    if (invalid)
	report("unknown escape sequence in string constant");
    else if (overflow)
	report("escape sequence out of range in string constant");
}


/*
 * Function:	report
 *
 * Description:	Report an error to the standard error prefixed with the
 *		line number.  We'll be using this a lot later with an
 *		optional string argument, but C++'s stupid streams don't do
 *		positional arguments, so we actually resort to snprintf.
 *		You just can't beat C for doing things down and dirty.
 */

void report(const string &str, const string &arg)
{
    char buf[1000];


    snprintf(buf, sizeof(buf), str.c_str(), arg.c_str());
    cerr << "line " << yylineno << ": " << buf << endl;
    numerrors ++;
}
