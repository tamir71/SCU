# include <iostream>
# include "tokens.h"
# include "lexer.h"

using namespace std;

int main()
{
    int token;
    string label;

    while ((token = yylex()) != 0) {
	if (AUTO <= token && token <= WHILE)
	    label = "keyword";

	else if (token == STRING)
	    label = "string";

	else if (token == ID)
	    label = "identifier";

	else if (token == NUM)
	    label = "integer";

	else
	    label = "operator";

	cout << label << " " << yytext << endl;
    }
}
