%skeleton "lalr1.cc"
%define "parser_class_name" {Parser}



%{
#include <iostream>
#include "AST.h"
using namespace yy;
%}


%parse-param { struct Driver& driver }
%error-verbose

%union {
	std::string* strVal;
	node* nodeVal;

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
%start START

%type <nodeVal> START functionheader formalparameter functiondeclarator formalparameterlist functiondeclaration  type _int variabledeclaration expression argumentlist functioninvocation literal conditionalorexpression  conditionalandexpression  equalityexpression relationalexpression  postfixexpression primary unaryexpression multiplicativeexpression additiveexpression globaldeclarations globaldeclaration mainfunctiondeclarator mainfunctiondeclaration block blockstatement blockstatements statement identifier statementexpression assignmentexpression assignment  
%destructor { delete $$; } id

%{
#include "Driver.h"
#include "Lexer.h"

#undef yylex
#define yylex driver.m_lexer->lex

%}
%locations
%%



START	        : { $$ = new node{NODE_START,{"nullStmt"},{}}; }
                | globaldeclarations {driver.n_ast = $$=$1; }
                ;

literal         : number { $$ = new node{NODE_LITR,{"number " + ("('"+*$1+"')"),{"int"}},{},@1.end.line};}
                | t_string { $$ = new node{NODE_LITR,{"string " + ("('"+*$1+"')") ,{"string"}},{},@1.end.line};}
                | _true { $$ = new node{NODE_LITR,{"true",{"boolean"}},{},@1.end.line};}
                | _false { $$ = new node{NODE_LITR,{"false",{"boolean"}},{},@1.end.line};}
                ;

type            : _bool {$$ = new node{NODE_TYPE,{"boolean",{"boolean"}},{},@1.end.line};}
                | _int {$$ = new node{NODE_TYPE,{"int",{"int"}},{},@1.end.line};}
                ;

globaldeclarations      : globaldeclaration {$$=new node{NODE_START,{"Program"},{$1},@1.end.line};}
                        | globaldeclarations globaldeclaration { $$->children.push_back($2);}
                        ;

globaldeclaration       : variabledeclaration {;}
                        | functiondeclaration {$$ = new node{NODE_SCOPE,{"fcnDecl"},{$1},@1.end.line};}
                        | mainfunctiondeclaration {$$ = new node{NODE_SCOPE,{"mainDecl"},{$1},@1.end.line};}
                        ;

variabledeclaration     : type identifier semicolon {$$ = new node{NODE_DECL,{$2->data.name, {$1->data.name}},{},@1.end.line};}
                        ;
                        

functiondeclaration     : functionheader block {$$=new node{NODE_DECL,{$1->data.name,{$1->children[0]->data.name,$1->data.type[0]}},{},@1.end.line};$$->children.push_back($2);

if($1->children.size()>1){$$->children.push_back($1->children[1]);
if($1->children[1]->children.size()>1)$1->children[1]->children[0]->data.type[0]=
$1->children[1]->children[0]->data.type[0][0]=='i'?"int":"boolean";}}
                        ;

functionheader          : type functiondeclarator {$$=$2;$$->children.insert($$->children.begin(),$1);}
                        | _void functiondeclarator {$$=$2;$$->children.insert($$->children.begin(),new node{NODE_DECL,{"void"},{},@1.end.line});}
                        ;

functiondeclarator      : identifier lround rround {$$ = new node{NODE_ID,{$1->data.name, {"void"}},{},@1.end.line};}
			| identifier lround formalparameterlist rround {$$ = new node{NODE_ID,{$1->data.name, {$3->children[0]->data.type[0]}},{$3},@1.end.line};}                       
                        ;

formalparameterlist     : formalparameter {$$=new node{NODE_PARAM_LIST,{$1->data.type[0]},{$1},@1.end.line};}
                        | formalparameterlist comma formalparameter { $$->children[0]->data.type[0]+=$3->data.type[0];$$->children.push_back($3);} 
                        ;

formalparameter         : type identifier {
$$ = new node{NODE_ID,{$2->data.name, {$1->data.name}},{},@1.end.line};
$$->children.push_back(new node{NODE_ASSN,{""},{},@1.end.line});}
                        ;

mainfunctiondeclaration : mainfunctiondeclarator block {$$ = new node{NODE_DECL,{$1->data.name},{},@1.end.line};$$->children.push_back($2);}
                        ;

mainfunctiondeclarator  : identifier lround rround 
                        ;

block                   : lcurl blockstatements rcurl { $$=$2->children.size()==1?$2->children[0]:$2;} 
                        | lcurl rcurl { $$ = new node{NODE_EMPTY,{"nullStmt"},{},@1.end.line}; }
                        ;

blockstatements         : blockstatement {$$ = new node{NODE_BLOCK,{"block"},{$1},@1.end.line}; }
                        | blockstatements blockstatement   { $$->children.push_back($2);}
                        ;

blockstatement          : variabledeclaration {$$=$1; ; }
                        | statement { $$ = $1;} 
                        ;

statement               : statementexpression semicolon {$$ = new node{NODE_STMT,{"statement expression"},{$1},@1.end.line}; }
                        | semicolon { $$ = new node{NODE_EMPTY,{"nullStmt"},{},@1.end.line}; }
                        | block
                        | _break semicolon { $$ = new node{NODE_BREAK,{"break"},{},@1.end.line}; }
                        | _return expression semicolon {  $$ = new node{NODE_RETURN,{"return"},{$2},@1.end.line};}
                        | _return semicolon {  $$ = new node{NODE_RETURN,{"return"},{},@1.end.line}; }
                        | _if lround expression rround statement { $$ = new node{NODE_BCOND,{"if"},{$3,$5},@1.end.line};}
                        | _if lround expression rround statement _else statement { $$ = new node{NODE_BCOND,{"ifElse"},{$3,$5, $7},@1.end.line};}
                        | _while lround expression rround statement { $$ = new node{NODE_BCOND,{"while"},{$3,$5},@1.end.line};$$->children.push_back(new node{NODE_WHILE_END,{""},{},@1.end.line}        );}
                        ;


statementexpression     : assignment { $$ = $1;}
                        | functioninvocation
                        ;

primary                 : literal { $$ = $1; }
                        | lround expression rround {$$ = $2;}
                        | functioninvocation { $$ = $1; }
                        ;

argumentlist            : expression {$$ = new node{NODE_ACTUALS,{"actuals"},{$1},@1.end.line};}
                        | argumentlist comma expression {$$->children.push_back($3);}
                        ;

functioninvocation      : identifier lround argumentlist rround {
$1->children.push_back(new node{NODE_ASSN,{""},{},@1.end.line});
$$ = new node{NODE_FCALL,{"funcCall"},{$1, $3},@1.end.line};}
                        | identifier lround rround {
$1->children.push_back(new node{NODE_ASSN,{""},{},@1.end.line});
$$ = new node{NODE_FCALL,{"funcCall"},{$1,{new node{NODE_ACTUALS,{"actuals"},{},@1.end.line} }},@1.end.line};}
                        ;

postfixexpression       : primary { $$ = $1;}		
			| identifier { $$ = $1; }
                        ;

unaryexpression         : minus unaryexpression {$$=$2; $$=$2->data.name[0]!='n' ? new node{NODE_QUANTU,{"-"}, {$2},@1.end.line} : $$;
							$$->data.name=$2->data.name[0]!='n' ? $$->data.name : $2->data.name.insert(2+$2->data.name.find("(\'"),"-")   ;}
                        | _not unaryexpression {$$ = new node{NODE_LOGIC,{"!"}, {$2}};  }
                        | postfixexpression { $$ = $1; }
                        ;

multiplicativeexpression: unaryexpression {$$ = $1; 	}
                        | multiplicativeexpression star unaryexpression { $$ = new node{NODE_QUANT,{"*"}, {$1, $3},@1.end.line}; }	
                        | multiplicativeexpression slash unaryexpression { $$ = new node{NODE_QUANT,{"/"}, {$1, $3},@1.end.line}; }
                        | multiplicativeexpression perct unaryexpression { $$ = new node{NODE_QUANT,{"%"}, {$1, $3},@1.end.line}; }
                        ;

additiveexpression      : multiplicativeexpression {$$ = $1; }
                        | additiveexpression plus multiplicativeexpression { $$ = new node{NODE_QUANT,{"+"}, {$1, $3},@1.end.line}; }	
                        | additiveexpression minus multiplicativeexpression { $$ = new node{NODE_QUANT,{"-"}, {$1, $3},@1.end.line}; }	
                        ;

relationalexpression    : additiveexpression 
                        | relationalexpression gt additiveexpression { $$ = new node{NODE_QUANTB,{">"}, {$1, $3},@1.end.line}; }	
                        | relationalexpression lt additiveexpression { $$ = new node{NODE_QUANTB,{"<"}, {$1, $3},@1.end.line}; }
                        | relationalexpression le additiveexpression { $$ = new node{NODE_QUANTB,{"<="}, {$1, $3},@1.end.line}; }
                        | relationalexpression ge additiveexpression { $$ = new node{NODE_QUANTB,{">="}, {$1, $3},@1.end.line}; }
                        ;

equalityexpression      : relationalexpression 
                        | equalityexpression cmp relationalexpression { $$ = new node{NODE_EQUALITY,{"=="}, {$1, $3},@1.end.line}; }
                        | equalityexpression ncmp relationalexpression { $$ = new node{NODE_EQUALITY,{"!="}, {$1, $3},@1.end.line}; }
                        ;

conditionalandexpression: equalityexpression 
                        | conditionalandexpression _and equalityexpression { $$ = new node{NODE_LOGIC,{"&&"}, {$1, $3},@1.end.line}; }
                        ;

conditionalorexpression : conditionalandexpression 
                        | conditionalorexpression _or conditionalandexpression { $$ = new node{NODE_LOGIC,{"||"}, {$1, $3},@1.end.line}; }
                        ;



identifier		: id { $$ = new node{NODE_ID,{"id (\'"+*$1+"\')"} , {},@1.end.line}; }
			;

assignmentexpression	: conditionalorexpression 
			| assignment 
 			;

assignment		:identifier eq assignmentexpression {$1->children.push_back(new node{NODE_ASSN,{""},{},@1.end.line});
$$ = new node{NODE_EQUALITY,{" ="}, {$1, $3},@1.end.line}; }	
			;	

expression              : assignmentexpression  {;}

%%

void yy::Parser::error(yy::location const& l, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const& s){
	
	std::cout<<"Parser error on line "<<l.end.line<<" : "<<s<<"\n";
}
