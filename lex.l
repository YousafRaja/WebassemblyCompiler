%option c++
%option yyclass="Lexer"

%{
#include "Lexer.h"
#include "parser.tab.hh"
#include <iostream>
#include <fstream>
#include <string>
#include "stdlib.h"
int linenum = 0;


// before matching any pattern, update the the current location
// X macros
#define TOKEN_LIST() \
	X(GT, ">") \
	X(GE, ">=") \
	X(DOT, ".") \
	X(ID, "id") \
	X(BOOL, "boolean") \
	X(TRUE, "true") \
	X(FALSE, "false") \
	X(INT, "int") \
	X(NUMBER, "number")\
	X(LCURL, "{") \
	X(RCURL, "}") \
	X(LSQUARE, "[") \
	X(RSQUARE, "]") \
	X(LROUND, "(") \
	X(RROUND, ")") \
	X(EQ, "=") \
	X(PLUS, "+") \
	X(MINUS, "-") \
	X(STAR, "*") \
	X(SLASH, "/") \
	X(PERCT, "%") \
	X(LT, "<") \
	X(LE, "<=") \
	X(CMP, "==") \
	X(NCMP, "!=") \
	X(NOT, "!") \
	X(AND, "&&") \
	X(OR, "||") \
	X(BREAK, "break") \
	X(RETURN, "return") \
	X(VOID, "void") \
	X(IF, "if") \
	X(ELSE, "else") \
	X(WHILE, "while") \
	X(COMM, "//") \
	X(SEMICOLON, ";") \
	X(COMMA, ",") \
	X(ERROR, "ERROR")\
	X(T_STRING, "t_string") 


namespace TokType {
enum Type {
	DEAD_TOKEN = 0,
#define X(NAME, STRING) NAME,
		TOKEN_LIST()
#undef X
	TOTAL_TOKENS
};
}

char const* getTokenName(int tok) {
	switch(tok) {
	#define X(NAME, STRING) \
		case TokType::NAME: return STRING;
		TOKEN_LIST()
	#undef X
		default: return "";
	}
}

struct Token {
	int toktype;
	std::string val;
	int lineno;
	int len;
};

inline std::ostream& operator<<(std::ostream& os, Token const& tok) {
	return 
		os << "Token name: " <<  getTokenName(tok.toktype) 
			<< ", value:" << tok.val << ""
			<< ", line:" << tok.lineno;
}



// Must inherit from yyFlexLexer
class CPPLexer : public yyFlexLexer {
public:
	// Pass streams into yyFlexLexer during construction
	// Required by flex
	CPPLexer(std::istream* is, std::ostream* os)
		: yyFlexLexer(is, os) {}

	// Definition but not declaration of this function
	// flex will generate body for you.
	int yylex();
	Token const& getTokenValue() const {
		return m_tok;
	}

private:

	int token(int toktype) {
		m_tok = Token{toktype,  "None", m_lineno};
		return toktype;
	}
	int token(int toktype, std::string str) {
		m_tok = Token{toktype,  std::move(str), m_lineno};
		return toktype;
	}

	// Default initialize line to 1
	int m_lineno = 1;
	Token m_tok;
};


%}
%option yylineno
ws [ \t\r]
digit [0-9]
alpha [a-zA-Z_]
alnum [a-zA-Z0-9_]
bool "boolean"
%option yylineno
%x  STRING

%%

<STRING>"\n"    m_val->strVal->append(yytext); 
<STRING><<EOF>> std::cerr << "Error, unterminated string\n"; return -1;// token(TokType::ERROR);
"\""            BEGIN(STRING); m_val->strVal = new std::string{""};
<STRING>"\""     {
	/* Using built in state machine to build strings */
	BEGIN(INITIAL); 
	return yy::Parser::token::t_string;
}
<STRING>"\\n"   { 
	m_val->strVal->append(yytext); 
}
<STRING>"\\b"   { 
	m_val->strVal->append(yytext); 
}
<STRING>"\\f"   { 
	m_val->strVal->append(yytext); 
}
<STRING>"\\t"   { 
	m_val->strVal->append(yytext); 
}
<STRING>"\\r"   { 
	m_val->strVal->append(yytext); 
}
<STRING>"\\\""   { 
	m_val->strVal->append(yytext); 
}
<STRING>"\\\'"   { 
	m_val->strVal->append(yytext); 
}
<STRING>"\\\\"   { 
	m_val->strVal->append(yytext); 
}
<STRING>.       {
	m_val->strVal->append(yytext); 
}

"while"	return yy::Parser::token::_while;
"break"	return yy::Parser::token::_break;
"return" return yy::Parser::token::_return;
"if" return yy::Parser::token::_if;
"else" return yy::Parser::token::_else;
"void" return yy::Parser::token::_void;
";" return yy::Parser::token::semicolon;
"(" return yy::Parser::token::lround;
")" return yy::Parser::token::rround;
"{" return yy::Parser::token::lcurl;
"}" return yy::Parser::token::rcurl;
"[" return yy::Parser::token::lsquare;
"]" return yy::Parser::token::rsqure;
"==" return yy::Parser::token::cmp;
"=" return yy::Parser::token::eq;
"." return yy::Parser::token::dot;
"boolean"	return yy::Parser::token::_bool;
"true"	return yy::Parser::token::_true;
"false"	return yy::Parser::token::_false;
"int" return yy::Parser::token::_int;
"+" return yy::Parser::token::plus;
">="  return yy::Parser::token::ge;
">"   return yy::Parser::token::gt;
{digit}{digit}* 	{ m_val->strVal = new std::string{yytext}; return yy::Parser::token::number; }
"-"			return yy::Parser::token::minus;
"*"			return yy::Parser::token::star;
"/"			return yy::Parser::token::slash;
"%"			return yy::Parser::token::perct;
"<="			return yy::Parser::token::le;
"<"			return yy::Parser::token::lt;
"!="			return yy::Parser::token::ncmp;
"!"			return yy::Parser::token::_not;
"&&"			return yy::Parser::token::_and;
"||"			return yy::Parser::token::_or;
","			return yy::Parser::token::comma;
"//".*	/* ignore */
{alpha}{alnum}* 	{ m_val->strVal = new std::string{yytext}; return yy::Parser::token::id; }
"\n"			{m_loc->lines(1);linenum+=1;}

[ \t\r\n] 		/* do nothing */
.			std::cerr << "Lex error, unknown char " << yytext << "\n"; return yy::Parser::token::error_tok;

%%

int yyFlexLexer::yywrap() { return 1; }

void yyerror(const char *str)
{
    fprintf(stderr,"Error | Line: %d\n%s\n",linenum,str);
}
