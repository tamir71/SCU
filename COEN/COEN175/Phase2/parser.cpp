/*
 * File:	parser.cpp
 *
 * Description:	This file is just a placeholder for the real parser.  It is
 *		here just so that the main function is separate from the
 *		lexer and can be built upon in a separate file.
 */

# include <iostream>
# include "lexer.h"
# include "tokens.h"

using namespace std;

int lookahead;
int nexttoken;
string lexbuf;
string nextbuf;

void expression();
void argumentList();
void statement();
void declarations();

void error() {
	if(lookahead == DONE)
		cout << "error at EOF" << endl;
	else
		cout << "error at " << endl;
	exit(EXIT_SUCCESS);
}

void match(int t) {
	if(lookahead != t)
		error();
	if(nexttoken) {
		lookahead = nexttoken;
		lexbuf = nextbuf;
		nexttoken = 0;
	}
	else {
		lookahead = yylex();
		lexbuf = yytext;
	}
}

int peek() {
	if(!nexttoken) {
		nexttoken = yylex();
		nextbuf = yytext;
	}
	return nexttoken;
}

void primaryExpression() {
	if(lookahead == '(') {
		match('(');
		expression();
		match(')');
	}
	else if(lookahead == ID) {
		match(ID);
		if(lookahead == '(') {
			match('(');
			if(lookahead != ')') {
				argumentList();
			}
			match(')');
		}
	}
	else
		match(NUM);
}

void postfixExpression() {
	primaryExpression();
	while(lookahead == '[') {
		match('[');
		expression();
		match(']');
		cout << "index" << endl;
		postfixExpression();
	}
}

void prefixExpression() {
	if(lookahead == '&') {
		match('&');
		prefixExpression();
		cout << "addr" << endl;
	}	
	else if(lookahead == '*') {
		match('*');
		prefixExpression();
		cout << "deref" << endl;
	}	
	else if(lookahead == '!') {
		match('!');
		prefixExpression();
		cout << "not" << endl;
	}	
	else if(lookahead == '-') {
		match('-');
		prefixExpression();
		cout << "neg" << endl;
	}	
	else if(lookahead == SIZEOF) {
		match(SIZEOF);
		prefixExpression();
		cout << "sizeof" << endl;
	}
	else
		postfixExpression();	
}

void multiplicativeExpression() {
	prefixExpression();
	while(1) {
		if(lookahead == '*') {
			match('*');
			prefixExpression();
			cout << "mul" << endl;
		}
		else if(lookahead == '/') {
			match('/');
			prefixExpression();
			cout << "div" << endl;
		}
		if(lookahead == '%') {
			match('%');
			prefixExpression();
			cout << "rem" << endl;
		}
		else
			break;	
	}
}

void additiveExpression() {
	multiplicativeExpression();
	while(1) {
		if(lookahead == '+') {
			match('+');
			multiplicativeExpression();
			cout << "add" << endl;
		}
		else if(lookahead == '-') {
			match('-');
			multiplicativeExpression();
			cout << "sub" << endl;
		}
		else
			break;
	}
}

void relationalExpression() {
	additiveExpression();
	while(1) {
		if(lookahead == '<') {
			match('<');
			additiveExpression();
			cout << "ltn" << endl;
		}
		else if(lookahead == '>') {
			match('>');
			additiveExpression();
			cout << "gtn" << endl;
		}
		else if(lookahead == LEQ) {
			match(LEQ);
			additiveExpression();
			cout << "leq" << endl;
		}
		else if(lookahead == GEQ) {
			match(GEQ);
			additiveExpression();
			cout << "geq" << endl;
		}
		else
			break;
	}
}

void equalityExpression() {
	relationalExpression();
	while(1) {
		if(lookahead == EQ) {
			match(EQ);
			relationalExpression();
			cout << "eql" << endl;
		}
		else if(lookahead == NEQ) {
			match(NEQ);
			relationalExpression();
			cout << "neq" << endl;
		}
		else
			break;
	}
}

void logicalAndExpression() {
	equalityExpression();
	while(lookahead == AND) {
		match(AND);
		equalityExpression();
		cout << "and" << endl;
	}	
}

void expression() {
	logicalAndExpression();
	while(lookahead == OR) {
		match(OR);
		logicalAndExpression();
		cout << "or" << endl;
	}
}

void argument() {
	if(lookahead == STRING) {
		match(STRING);
	}
	else
		expression();
}

void argumentList() {
	argument();
	while(lookahead == ',') {
		match(',');
		argument();
	}
}

void assignment() {
	expression();
	if(lookahead == ASSIGN) {
		match(ASSIGN);
		expression();
	}
}

void statements() {
	while(lookahead != '}') {
		statement();
	}
}

void statement() {
	if(lookahead == '[') {
		match('[');
		declarations();
		statements();
		match(']');
	}
	else if(lookahead == RETURN) {
		match(RETURN);
		expression();
		match(';');
	}
	else if(lookahead == WHILE) {
		match(WHILE);
		match('(');
		expression();
		match(')');
	}
	else if(lookahead == FOR) {
		match(FOR);
		match('(');
		assignment();
		match(';');
		expression();
		match(';');
		assignment();
		match(')');
		statement();
	}
	else if(lookahead == IF) {
		match(IF);
		match('(');
		expression();
		match(')');
		statement();
		if(lookahead == ELSE) {
			match(ELSE);
			statement();
		}
	}
	else {
		assignment();
		match(';');
	}
}

void pointers() {
	while(lookahead == '*') {
		match('*');
	}
}

void specifier() {
	if(lookahead == INT) {
		match(INT);
	}
	else if(lookahead == LONG) {
		match(LONG);
	}
}

void declarator() {
	pointers();
	match(ID);
	if(lookahead == '[') {
		match('[');
		match(NUM);
		match(']');
	}
}

void declaration() {
	specifier();
	declarator();
	while(lookahead == ',') {
		match(',');
		declarator();
	}
	match(';');
}

void declarations() {
	while(lookahead == INT || lookahead == LONG)
		declaration();
}

void parameter() {
	specifier();
	pointers();
	match(ID);
}

void parameterList() {
	parameter();
	while(lookahead == ',') {
		match(',');
		parameter();
	}
}

void parameters() {
	if(lookahead == VOID)
		match(VOID);
	else
		parameterList();
}

void globalDeclarator() {
	pointers();
	match(ID);
	if(lookahead == '[') {
		match('[');
		match(NUM);
		match(']');
	}
	else if(lookahead == '(') {
		match('(');
		match(')');
	}
}

void remainingDeclarators() {
	while(lookahead == ',') {
		match(',');
		globalDeclarator();
	}
	match(';');
}

void functionOrGlobal() {
	specifier();
	pointers();
	match(ID);
	if(lookahead == '[') {
		match('[');
		match(NUM);
		match(']');
		remainingDeclarators();
	}
	else if(lookahead == '(') {
		match('(');
		if(lookahead == ')') {
			match(')');
			remainingDeclarators();
		}
		else {
			parameters();
			match(')');
			match('{');
			declarations();
			statements();
			match('}');
		}
	}
	else
		remainingDeclarators();
}

int main() {
    yylex();
	while(lookahead != DONE)
    	functionOrGlobal();
	return 0;
}
