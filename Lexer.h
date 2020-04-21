#pragma once
#include <iostream>
#include <string>
#include "AST.h"
#include "parser.tab.hh"

#ifndef yyFlexLexerOnce
#include <FlexLexer.h>
#endif
 

class Lexer : public yyFlexLexer {
public: 
	Lexer(std::istream* is = nullptr, std::ostream* os = nullptr) 
		: yyFlexLexer(is, os)
	{}
	using TokenType = yy::Parser::semantic_type;
	using LocationType = yy::Parser::location_type;
	int yylex();
	int lex(TokenType* semval, LocationType* locval) {
		m_val  = semval;
		m_loc = locval;
		return yylex();
	}
	
private:
	TokenType* m_val;
	LocationType* m_loc;
};
