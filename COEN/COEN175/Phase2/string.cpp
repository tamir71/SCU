/*
 * File:	string.cpp
 *
 * Description:	This file contains the function definitions for parsing and
 *		escaping C-style escape sequences in strings.
 */

# include <climits>
# include "string.h"

using namespace std;


/*
 * Function:	parseString
 *
 * Description:	Parse a string contains C-style escape sequences.  An
 *		invalid escape sequence is detected, as is an overflow in
 *		an octal or hexadecimal escape sequence.
 */

string parseString(const string &s, bool &invalid, bool &overflow)
{
    unsigned start, val;
    string result;


    invalid = false;
    overflow = false;

    for (unsigned i = 0; i < s.size(); i ++) {
	if (s[i] == '\\') {
	    i ++;

	    switch(s[i]) {
	    case 'a':
		result += '\a';
		break;

	    case 'b':
		result += '\b';
		break;

	    case 'f':
		result += '\f';
		break;

	    case 'n':
		result += '\n';
		break;

	    case 'r':
		result += '\r';
		break;

	    case 't':
		result += '\t';
		break;

	    case 'v':
		result += '\v';
		break;

	    case '\n':
		break;

	    case '\\': case '\?': case '\'': case '\"':
		result += s[i];
		break;

	    case 'x':
		val = 0;
		start = i;

		while (1) {
		    if (s[i + 1] >= '0' && s[i + 1] <= '9')
			val = val * 16 + (s[++ i] - '0');
		    else if (s[i + 1] >= 'a' && s[i + 1] <= 'f')
			val = val * 16 + (s[++ i] - 'a' + 10);
		    else if (s[i + 1] >= 'A' && s[i + 1] <= 'F')
			val = val * 16 + (s[++ i] - 'A' + 10);
		    else
			break;
		}

		if (start == i) {
		    invalid = true;
		    val = 'x';
		} else if (val > UCHAR_MAX)
		    overflow = true;

		result += val;
		break;

	    case '0': case '1': case '2': case '3':
	    case '4': case '5': case '6': case '7':
		val = s[i] - '0';

		if (s[i + 1] >= '0' && s[i + 1] <= '7')
		    val = val * 8 + (s[++ i] - '0');

		if (s[i + 1] >= '0' && s[i + 1] <= '7')
		    val = val * 8 + (s[++ i] - '0');

		if (val > UCHAR_MAX)
		    overflow = true;

		result += val;
		break;

	    default:
		invalid = true;
		result += s[i];
		break;
	    }

	} else
	    result += s[i];
    }

    return result;
}


/*
 * Function:	parseString
 *
 * Description:	Parse a string contains C-style escape sequences.  Any
 *		invalid escape sequence is silently ignored.
 */

string parseString(const string &s)
{
    bool invalid, overflow;
    return parseString(s, invalid, overflow);
}


/*
 * Function:	escapeString
 *
 * Description:	Return a copy of the given string but with any unprintable
 *		character replaced with an octal escape sequence.
 */

string escapeString(const string &s)
{
    char buf[5];
    string result;


    for (unsigned i = 0; i < s.size(); i ++)
	if (!isprint(s[i])) {
	    sprintf(buf, "\\%03o", (unsigned char) s[i]);
	    result += buf;
	} else
	    result += s[i];

    return result;
}
