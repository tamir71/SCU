%{
/* All C++ code must go here or after the final %% */

# include <iostream>
# include <string>
using namespace std;
void ignoreComments();
%}

%option nounput noyywrap yylineno
%%
\"(\\.|[^\\\n"])*\"						{ cout << "string " << yytext << endl; }
"auto"                  				{ cout << "keyword " << yytext << endl; }
"break"                  	 	 	 	{ cout << "keyword " << yytext << endl; }
"case"                  				{ cout << "keyword " << yytext << endl; }
"char"                  				{ cout << "keyword " << yytext << endl; }
"const"                  	 	 	 	{ cout << "keyword " << yytext << endl; }
"continue"                              { cout << "keyword " << yytext << endl; }
"default"                  	   	   	   	{ cout << "keyword " << yytext << endl; }
"do"                  					{ cout << "keyword " << yytext << endl; }
"double"                				{ cout << "keyword " << yytext << endl; }
"else"                  				{ cout << "keyword " << yytext << endl; }
"enum"                  				{ cout << "keyword " << yytext << endl; }
"extern"                  	  	  	  	{ cout << "keyword " << yytext << endl; }
"float"                  	 	 	 	{ cout << "keyword " << yytext << endl; }
"for"                  					{ cout << "keyword " << yytext << endl; }
"goto"                  				{ cout << "keyword " << yytext << endl; }
"if"                  					{ cout << "keyword " << yytext << endl; }
"int"                  					{ cout << "keyword " << yytext << endl; }
"long"                  				{ cout << "keyword " << yytext << endl; }
"register"                              { cout << "keyword " << yytext << endl; }
"return"                  	  	  	  	{ cout << "keyword " << yytext << endl; }
"short"                  	 	 	 	{ cout << "keyword " << yytext << endl; }
"signed"                  	  	  	  	{ cout << "keyword " << yytext << endl; }
"sizeof"                  	  	  	  	{ cout << "keyword " << yytext << endl; } 
"static"                  	  	  	  	{ cout << "keyword " << yytext << endl; } 
"struct"                  	  	  	  	{ cout << "keyword " << yytext << endl; } 
"switch"                  	  	  	  	{ cout << "keyword " << yytext << endl; }
"typedef"                  	   	   	   	{ cout << "keyword " << yytext << endl; }
"union"                  	 	 	 	{ cout << "keyword " << yytext << endl; }
"unsigned"                              { cout << "keyword " << yytext << endl; }
"void"                  				{ cout << "keyword " << yytext << endl; }
"volatile"                              { cout << "keyword " << yytext << endl; }
"while"                  	 	 	 	{ cout << "keyword " << yytext << endl; }
[a-zA-Z_][a-zA-Z0-9_]*					{ cout << "identifier " << yytext << endl; }
[0-9]+                  				{ cout << "integer " << yytext << endl; }
"="										{ cout << "operator " << yytext << endl; }
"||"                                    { cout << "operator " << yytext << endl; }
"&&"                                    { cout << "operator " << yytext << endl; }
"|"                                     { cout << "operator " << yytext << endl; }
"=="                                    { cout << "operator " << yytext << endl; }
"!="                                    { cout << "operator " << yytext << endl; }
"<"                                     { cout << "operator " << yytext << endl; }
">"                                     { cout << "operator " << yytext << endl; }
"<="                                    { cout << "operator " << yytext << endl; }
">="                                    { cout << "operator " << yytext << endl; }
"+"                                     { cout << "operator " << yytext << endl; }
"-"                                     { cout << "operator " << yytext << endl; }
"*"                                     { cout << "operator " << yytext << endl; }
"/"                                     { cout << "operator " << yytext << endl; }
"%"                                     { cout << "operator " << yytext << endl; }
"&"                                     { cout << "operator " << yytext << endl; }
"!"                                     { cout << "operator " << yytext << endl; }
"++"                                    { cout << "operator " << yytext << endl; }
"--"                                    { cout << "operator " << yytext << endl; }
"->"                                    { cout << "operator " << yytext << endl; }
"("                                     { cout << "operator " << yytext << endl; }
")"                                     { cout << "operator " << yytext << endl; }
"["                                     { cout << "operator " << yytext << endl; }
"]"                                     { cout << "operator " << yytext << endl; }
"{"                                     { cout << "operator " << yytext << endl; }
"}"                                     { cout << "operator " << yytext << endl; }
";"                                     { cout << "operator " << yytext << endl; }
":"                                     { cout << "operator " << yytext << endl; }
"."                                     { cout << "operator " << yytext << endl; }
","                                     { cout << "operator " << yytext << endl; }
\\+\*									{ ignoreComments(); }
[ \t\n\v\f]+            				{ /* ignored */ }
.                       				{ cerr << "Invalid: " << yytext << endl; }
%%


/* More C++ code */
void ignoreComments() {
	char c;
	c = yyinput();
	while (c != EOF) {
		if(c == '*' && cin.peek() == '/')		
			return;
		c = yyinput();
	}
}

int main() {
    while(yylex())
        continue;
}
