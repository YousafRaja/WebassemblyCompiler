%skeleton "lalr1.cc"
%define "parser_class_name" {Parser}
%{
#include <iostream>
#include "AST.h"
%}


%parse-param { struct Driver& driver }
%error-verbose

%union {
	std::string* strVal;
	struct ASTNode* nodeVal;
}




%token <strVal>	t_string 	"t_string"
%token  	_while		"_while"
%token  	_break		"_break"
%token  	_return		"_return"
%token  	_if		"_if"
%token  	_else		"_else"
%token  	_void		"_void"
%token  	semicolon	"semicolon"
%token  	lround		"lround"
%token  	rround		"rround"
%token  	lcurl		"lcurl"
%token  	rcurl		"rcurl"
%token  	lsquare		"lsquare"
%token  	rsqure		"rsqure"
%token  	cmp		"cmp"
%token 		eq 		"eq"
%token  	dot		"dot"
%token  	_bool		"_bool"
%token  	_true		"_true"
%token  	_false		"_false"
%token  	_int		"_int"
%token  	plus		"plus"
%token  	ge		"ge"
%token  	gt		"gt"
%token <strVal>	number 		"number"
%token  	minus		"minus"
%token  	star		"star"
%token  	slash		"slash"
%token  	perct		"perct"
%token  	le		"le"
%token  	lt		"lt"
%token  	ncmp		"ncmp"
%token  	_not		"not"
%token  	_and		"_and"
%token  	_or		"or"
%token 		comma 		"comma"
%token <strVal>	id 		"id"
%token 		error_tok	"error token"
%start START1

%type <nodeVal> START S L R identifier assignment assignmentexpression 

%destructor { delete $$; } id

%{
#include "Driver.h"
#include "Lexer.h"

#undef yylex
#define yylex driver.m_lexer->lex

%}

%%



START1	        : /* empty */
                | {std::cout<<"a\n";} globaldeclarations 
                ;

literal         : number
                | t_string
                | _true
                | _false
                ;

type            : _bool
                | _int
                ;

globaldeclarations      : {std::cout<<"b\n";} globaldeclaration
                        | {std::cout<<"c\n";} globaldeclarations globaldeclaration
                        ;

globaldeclaration       : variabledeclaration
                        | functiondeclaration
                        | {std::cout<<"d\n";} mainfunctiondeclaration
                        ;

variabledeclaration     : {std::cout<<"b1\n";} type identifier semicolon
                        ;


                        ;

functiondeclaration     : {std::cout<<"b2\n";} functionheader block
                        ;

functionheader          : {std::cout<<"b2a\n";} type functiondeclarator
                        | {std::cout<<"b2b\n";} _void functiondeclarator
                        ;

functiondeclarator      : {std::cout<<"b2bb\n";} identifier lround rround
			| {std::cout<<"b2ba\n";} identifier lround formalparameterlist rround                        
                        ;

formalparameterlist     : formalparameter
                        | formalparameterlist ',' formalparameter
                        ;

formalparameter         : type identifier
                        ;

mainfunctiondeclaration : {std::cout<<"e\n";} mainfunctiondeclarator block
                        ;

mainfunctiondeclarator  : identifier lround rround
                        ;

block                   : {std::cout<<"fa\n";} lcurl blockstatements rcurl
                        | {std::cout<<"fb\n";} lcurl rcurl
                        ;

blockstatements         : blockstatement
                        | blockstatements blockstatement
                        ;

blockstatement          : {std::cout<<"ea\n";} variabledeclaration
                        | {std::cout<<"eb\n";} statement
                        ;

statement               : statementexpression semicolon 
                        | {std::cout<<"gb\n";} semicolon
                        | {std::cout<<"gc\n";} block
                        | {std::cout<<"gd\n";} _break semicolon
                        | {std::cout<<"ge\n";} _return expression semicolon
                        | {std::cout<<"gf\n";} _return semicolon
                        | {std::cout<<"gg\n";} _if lround expression rround statement
                        | {std::cout<<"gh\n";} _if lround expression rround statement _else statement
                        | {std::cout<<"gi\n";} _while lround expression rround statement
                        ;

statementexpression     : assignment { driver.m_ast = $1; }
                        | {std::cout<<"hb\n";} functioninvocation
                        ;

primary                 : literal
                        | '(' expression ')'
                        | functioninvocation
                        ;

argumentlist            : expression
                        | argumentlist ',' expression
                        ;

functioninvocation      : identifier '(' argumentlist ')'
                        | identifier '(' ')'
                        ;

postfixexpression       : primary
                        | identifier
                        ;

unaryexpression         : '-' unaryexpression
                        | '!' unaryexpression
                        | postfixexpression
                        ;

multiplicativeexpression: unaryexpression
                        | multiplicativeexpression '*' unaryexpression
                        | multiplicativeexpression '/' unaryexpression
                        | multiplicativeexpression '%' unaryexpression
                        ;

additiveexpression      : multiplicativeexpression
                        | additiveexpression '+' multiplicativeexpression
                        | additiveexpression '-' multiplicativeexpression
                        ;

relationalexpression    : additiveexpression
                        | relationalexpression '<' additiveexpression
                        | relationalexpression '>' additiveexpression
                        | relationalexpression le additiveexpression
                        | relationalexpression ge additiveexpression
                        ;

equalityexpression      : relationalexpression
                        | equalityexpression cmp relationalexpression
                        | equalityexpression ncmp relationalexpression
                        ;

conditionalandexpression: equalityexpression
                        | conditionalandexpression _and equalityexpression
                        ;

conditionalorexpression : conditionalandexpression
                        | conditionalorexpression _or conditionalandexpression
                        ;



assignment		: S { $$ = new ASTNode{"assignment",{$1}}; }
     			;

S:			identifier eq assignmentexpression { $$ = new ASTNode{"=", {$1, $3}}; }
			| assignmentexpression      { $$ = $1; }
			;

identifier		: star assignmentexpression { $$ = new ASTNode{"*", {$2}}; }
			| id         { $$ = new ASTNode{*$1, {}}; }
			;

assignmentexpression	: identifier          { $$ = $1; }
 			;

expression              : assignmentexpression
                        ;

%%

void yy::Parser::error(std::string const& msg) {
	std::cerr << "Error: " << msg << "\n";
	exit(1);
}
