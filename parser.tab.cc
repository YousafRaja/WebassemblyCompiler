// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.
#line 6 "parser.yy" // lalr1.cc:404

#include <iostream>
#include "AST.h"
using namespace yy;

#line 42 "parser.tab.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "parser.tab.hh"

// User implementation prologue.
#line 68 "parser.yy" // lalr1.cc:412

#include "Driver.h"
#include "Lexer.h"

#undef yylex
#define yylex driver.m_lexer->lex


#line 64 "parser.tab.cc" // lalr1.cc:412


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
#line 150 "parser.tab.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (struct Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 39: // "id"

#line 66 "parser.yy" // lalr1.cc:614
        { delete (yysym.value.strVal); }
#line 403 "parser.tab.cc" // lalr1.cc:614
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* If YYLEN is nonzero, implement the default value of the
         action: '$$ = $1'.  Otherwise, use the top of the stack.

         Otherwise, the following line sets YYLHS.VALUE to garbage.
         This behavior is undocumented and Bison users should not rely
         upon it.  */
      if (yylen)
        yylhs.value = yystack_[yylen - 1].value;
      else
        yylhs.value = yystack_[0].value;

      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 81 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_START,{"nullStmt"},{}}; }
#line 642 "parser.tab.cc" // lalr1.cc:859
    break;

  case 3:
#line 82 "parser.yy" // lalr1.cc:859
    {driver.n_ast = (yylhs.value.nodeVal)=(yystack_[0].value.nodeVal); }
#line 648 "parser.tab.cc" // lalr1.cc:859
    break;

  case 4:
#line 85 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_LITR,{"number " + ("('"+*(yystack_[0].value.strVal)+"')"),{"int"}},{},yystack_[0].location.end.line};}
#line 654 "parser.tab.cc" // lalr1.cc:859
    break;

  case 5:
#line 86 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_LITR,{"string " + ("('"+*(yystack_[0].value.strVal)+"')") ,{"string"}},{},yystack_[0].location.end.line};}
#line 660 "parser.tab.cc" // lalr1.cc:859
    break;

  case 6:
#line 87 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_LITR,{"true",{"boolean"}},{},yystack_[0].location.end.line};}
#line 666 "parser.tab.cc" // lalr1.cc:859
    break;

  case 7:
#line 88 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_LITR,{"false",{"boolean"}},{},yystack_[0].location.end.line};}
#line 672 "parser.tab.cc" // lalr1.cc:859
    break;

  case 8:
#line 91 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal) = new node{NODE_TYPE,{"boolean",{"boolean"}},{},yystack_[0].location.end.line};}
#line 678 "parser.tab.cc" // lalr1.cc:859
    break;

  case 9:
#line 92 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal) = new node{NODE_TYPE,{"int",{"int"}},{},yystack_[0].location.end.line};}
#line 684 "parser.tab.cc" // lalr1.cc:859
    break;

  case 10:
#line 95 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal)=new node{NODE_START,{"Program"},{(yystack_[0].value.nodeVal)},yystack_[0].location.end.line};}
#line 690 "parser.tab.cc" // lalr1.cc:859
    break;

  case 11:
#line 96 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal)->children.push_back((yystack_[0].value.nodeVal));}
#line 696 "parser.tab.cc" // lalr1.cc:859
    break;

  case 12:
#line 99 "parser.yy" // lalr1.cc:859
    {;}
#line 702 "parser.tab.cc" // lalr1.cc:859
    break;

  case 13:
#line 100 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal) = new node{NODE_SCOPE,{"fcnDecl"},{(yystack_[0].value.nodeVal)},yystack_[0].location.end.line};}
#line 708 "parser.tab.cc" // lalr1.cc:859
    break;

  case 14:
#line 101 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal) = new node{NODE_SCOPE,{"mainDecl"},{(yystack_[0].value.nodeVal)},yystack_[0].location.end.line};}
#line 714 "parser.tab.cc" // lalr1.cc:859
    break;

  case 15:
#line 104 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal) = new node{NODE_DECL,{(yystack_[1].value.nodeVal)->data.name, {(yystack_[2].value.nodeVal)->data.name}},{},yystack_[2].location.end.line};}
#line 720 "parser.tab.cc" // lalr1.cc:859
    break;

  case 16:
#line 108 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal)=new node{NODE_DECL,{(yystack_[1].value.nodeVal)->data.name,{(yystack_[1].value.nodeVal)->children[0]->data.name,(yystack_[1].value.nodeVal)->data.type[0]}},{},yystack_[1].location.end.line};(yylhs.value.nodeVal)->children.push_back((yystack_[0].value.nodeVal));

if((yystack_[1].value.nodeVal)->children.size()>1){(yylhs.value.nodeVal)->children.push_back((yystack_[1].value.nodeVal)->children[1]);
if((yystack_[1].value.nodeVal)->children[1]->children.size()>1)(yystack_[1].value.nodeVal)->children[1]->children[0]->data.type[0]=
(yystack_[1].value.nodeVal)->children[1]->children[0]->data.type[0][0]=='i'?"int":"boolean";}}
#line 730 "parser.tab.cc" // lalr1.cc:859
    break;

  case 17:
#line 115 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal)=(yystack_[0].value.nodeVal);(yylhs.value.nodeVal)->children.insert((yylhs.value.nodeVal)->children.begin(),(yystack_[1].value.nodeVal));}
#line 736 "parser.tab.cc" // lalr1.cc:859
    break;

  case 18:
#line 116 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal)=(yystack_[0].value.nodeVal);(yylhs.value.nodeVal)->children.insert((yylhs.value.nodeVal)->children.begin(),new node{NODE_DECL,{"void"},{},yystack_[1].location.end.line});}
#line 742 "parser.tab.cc" // lalr1.cc:859
    break;

  case 19:
#line 119 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal) = new node{NODE_ID,{(yystack_[2].value.nodeVal)->data.name, {"void"}},{},yystack_[2].location.end.line};}
#line 748 "parser.tab.cc" // lalr1.cc:859
    break;

  case 20:
#line 120 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal) = new node{NODE_ID,{(yystack_[3].value.nodeVal)->data.name, {(yystack_[1].value.nodeVal)->children[0]->data.type[0]}},{(yystack_[1].value.nodeVal)},yystack_[3].location.end.line};}
#line 754 "parser.tab.cc" // lalr1.cc:859
    break;

  case 21:
#line 123 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal)=new node{NODE_PARAM_LIST,{(yystack_[0].value.nodeVal)->data.type[0]},{(yystack_[0].value.nodeVal)},yystack_[0].location.end.line};}
#line 760 "parser.tab.cc" // lalr1.cc:859
    break;

  case 22:
#line 124 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal)->children[0]->data.type[0]+=(yystack_[0].value.nodeVal)->data.type[0];(yylhs.value.nodeVal)->children.push_back((yystack_[0].value.nodeVal));}
#line 766 "parser.tab.cc" // lalr1.cc:859
    break;

  case 23:
#line 127 "parser.yy" // lalr1.cc:859
    {
(yylhs.value.nodeVal) = new node{NODE_ID,{(yystack_[0].value.nodeVal)->data.name, {(yystack_[1].value.nodeVal)->data.name}},{},yystack_[1].location.end.line};
(yylhs.value.nodeVal)->children.push_back(new node{NODE_ASSN,{""},{},yystack_[1].location.end.line});}
#line 774 "parser.tab.cc" // lalr1.cc:859
    break;

  case 24:
#line 132 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal) = new node{NODE_DECL,{(yystack_[1].value.nodeVal)->data.name},{},yystack_[1].location.end.line};(yylhs.value.nodeVal)->children.push_back((yystack_[0].value.nodeVal));}
#line 780 "parser.tab.cc" // lalr1.cc:859
    break;

  case 26:
#line 138 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal)=(yystack_[1].value.nodeVal)->children.size()==1?(yystack_[1].value.nodeVal)->children[0]:(yystack_[1].value.nodeVal);}
#line 786 "parser.tab.cc" // lalr1.cc:859
    break;

  case 27:
#line 139 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_EMPTY,{"nullStmt"},{},yystack_[1].location.end.line}; }
#line 792 "parser.tab.cc" // lalr1.cc:859
    break;

  case 28:
#line 142 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal) = new node{NODE_BLOCK,{"block"},{(yystack_[0].value.nodeVal)},yystack_[0].location.end.line}; }
#line 798 "parser.tab.cc" // lalr1.cc:859
    break;

  case 29:
#line 143 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal)->children.push_back((yystack_[0].value.nodeVal));}
#line 804 "parser.tab.cc" // lalr1.cc:859
    break;

  case 30:
#line 146 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal)=(yystack_[0].value.nodeVal); ; }
#line 810 "parser.tab.cc" // lalr1.cc:859
    break;

  case 31:
#line 147 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = (yystack_[0].value.nodeVal);}
#line 816 "parser.tab.cc" // lalr1.cc:859
    break;

  case 32:
#line 150 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal) = new node{NODE_STMT,{"statement expression"},{(yystack_[1].value.nodeVal)},yystack_[1].location.end.line}; }
#line 822 "parser.tab.cc" // lalr1.cc:859
    break;

  case 33:
#line 151 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_EMPTY,{"nullStmt"},{},yystack_[0].location.end.line}; }
#line 828 "parser.tab.cc" // lalr1.cc:859
    break;

  case 35:
#line 153 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_BREAK,{"break"},{},yystack_[1].location.end.line}; }
#line 834 "parser.tab.cc" // lalr1.cc:859
    break;

  case 36:
#line 154 "parser.yy" // lalr1.cc:859
    {  (yylhs.value.nodeVal) = new node{NODE_RETURN,{"return"},{(yystack_[1].value.nodeVal)},yystack_[2].location.end.line};}
#line 840 "parser.tab.cc" // lalr1.cc:859
    break;

  case 37:
#line 155 "parser.yy" // lalr1.cc:859
    {  (yylhs.value.nodeVal) = new node{NODE_RETURN,{"return"},{},yystack_[1].location.end.line}; }
#line 846 "parser.tab.cc" // lalr1.cc:859
    break;

  case 38:
#line 156 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_BCOND,{"if"},{(yystack_[2].value.nodeVal),(yystack_[0].value.nodeVal)},yystack_[4].location.end.line};}
#line 852 "parser.tab.cc" // lalr1.cc:859
    break;

  case 39:
#line 157 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_BCOND,{"ifElse"},{(yystack_[4].value.nodeVal),(yystack_[2].value.nodeVal), (yystack_[0].value.nodeVal)},yystack_[6].location.end.line};}
#line 858 "parser.tab.cc" // lalr1.cc:859
    break;

  case 40:
#line 158 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_BCOND,{"while"},{(yystack_[2].value.nodeVal),(yystack_[0].value.nodeVal)},yystack_[4].location.end.line};(yylhs.value.nodeVal)->children.push_back(new node{NODE_WHILE_END,{""},{},yystack_[4].location.end.line}        );}
#line 864 "parser.tab.cc" // lalr1.cc:859
    break;

  case 41:
#line 162 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = (yystack_[0].value.nodeVal);}
#line 870 "parser.tab.cc" // lalr1.cc:859
    break;

  case 43:
#line 166 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = (yystack_[0].value.nodeVal); }
#line 876 "parser.tab.cc" // lalr1.cc:859
    break;

  case 44:
#line 167 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal) = (yystack_[1].value.nodeVal);}
#line 882 "parser.tab.cc" // lalr1.cc:859
    break;

  case 45:
#line 168 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = (yystack_[0].value.nodeVal); }
#line 888 "parser.tab.cc" // lalr1.cc:859
    break;

  case 46:
#line 171 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal) = new node{NODE_ACTUALS,{"actuals"},{(yystack_[0].value.nodeVal)},yystack_[0].location.end.line};}
#line 894 "parser.tab.cc" // lalr1.cc:859
    break;

  case 47:
#line 172 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal)->children.push_back((yystack_[0].value.nodeVal));}
#line 900 "parser.tab.cc" // lalr1.cc:859
    break;

  case 48:
#line 175 "parser.yy" // lalr1.cc:859
    {
(yystack_[3].value.nodeVal)->children.push_back(new node{NODE_ASSN,{""},{},yystack_[3].location.end.line});
(yylhs.value.nodeVal) = new node{NODE_FCALL,{"funcCall"},{(yystack_[3].value.nodeVal), (yystack_[1].value.nodeVal)},yystack_[3].location.end.line};}
#line 908 "parser.tab.cc" // lalr1.cc:859
    break;

  case 49:
#line 178 "parser.yy" // lalr1.cc:859
    {
(yystack_[2].value.nodeVal)->children.push_back(new node{NODE_ASSN,{""},{},yystack_[2].location.end.line});
(yylhs.value.nodeVal) = new node{NODE_FCALL,{"funcCall"},{(yystack_[2].value.nodeVal),{new node{NODE_ACTUALS,{"actuals"},{},yystack_[2].location.end.line} }},yystack_[2].location.end.line};}
#line 916 "parser.tab.cc" // lalr1.cc:859
    break;

  case 50:
#line 183 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = (yystack_[0].value.nodeVal);}
#line 922 "parser.tab.cc" // lalr1.cc:859
    break;

  case 51:
#line 184 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = (yystack_[0].value.nodeVal); }
#line 928 "parser.tab.cc" // lalr1.cc:859
    break;

  case 52:
#line 187 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal)=(yystack_[0].value.nodeVal); (yylhs.value.nodeVal)=(yystack_[0].value.nodeVal)->data.name[0]!='n' ? new node{NODE_QUANTU,{"-"}, {(yystack_[0].value.nodeVal)},yystack_[1].location.end.line} : (yylhs.value.nodeVal);
							(yylhs.value.nodeVal)->data.name=(yystack_[0].value.nodeVal)->data.name[0]!='n' ? (yylhs.value.nodeVal)->data.name : (yystack_[0].value.nodeVal)->data.name.insert(2+(yystack_[0].value.nodeVal)->data.name.find("(\'"),"-")   ;}
#line 935 "parser.tab.cc" // lalr1.cc:859
    break;

  case 53:
#line 189 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal) = new node{NODE_LOGIC,{"!"}, {(yystack_[0].value.nodeVal)}};  }
#line 941 "parser.tab.cc" // lalr1.cc:859
    break;

  case 54:
#line 190 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = (yystack_[0].value.nodeVal); }
#line 947 "parser.tab.cc" // lalr1.cc:859
    break;

  case 55:
#line 193 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal) = (yystack_[0].value.nodeVal); 	}
#line 953 "parser.tab.cc" // lalr1.cc:859
    break;

  case 56:
#line 194 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_QUANT,{"*"}, {(yystack_[2].value.nodeVal), (yystack_[0].value.nodeVal)},yystack_[2].location.end.line}; }
#line 959 "parser.tab.cc" // lalr1.cc:859
    break;

  case 57:
#line 195 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_QUANT,{"/"}, {(yystack_[2].value.nodeVal), (yystack_[0].value.nodeVal)},yystack_[2].location.end.line}; }
#line 965 "parser.tab.cc" // lalr1.cc:859
    break;

  case 58:
#line 196 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_QUANT,{"%"}, {(yystack_[2].value.nodeVal), (yystack_[0].value.nodeVal)},yystack_[2].location.end.line}; }
#line 971 "parser.tab.cc" // lalr1.cc:859
    break;

  case 59:
#line 199 "parser.yy" // lalr1.cc:859
    {(yylhs.value.nodeVal) = (yystack_[0].value.nodeVal); }
#line 977 "parser.tab.cc" // lalr1.cc:859
    break;

  case 60:
#line 200 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_QUANT,{"+"}, {(yystack_[2].value.nodeVal), (yystack_[0].value.nodeVal)},yystack_[2].location.end.line}; }
#line 983 "parser.tab.cc" // lalr1.cc:859
    break;

  case 61:
#line 201 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_QUANT,{"-"}, {(yystack_[2].value.nodeVal), (yystack_[0].value.nodeVal)},yystack_[2].location.end.line}; }
#line 989 "parser.tab.cc" // lalr1.cc:859
    break;

  case 63:
#line 205 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_QUANTB,{">"}, {(yystack_[2].value.nodeVal), (yystack_[0].value.nodeVal)},yystack_[2].location.end.line}; }
#line 995 "parser.tab.cc" // lalr1.cc:859
    break;

  case 64:
#line 206 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_QUANTB,{"<"}, {(yystack_[2].value.nodeVal), (yystack_[0].value.nodeVal)},yystack_[2].location.end.line}; }
#line 1001 "parser.tab.cc" // lalr1.cc:859
    break;

  case 65:
#line 207 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_QUANTB,{"<="}, {(yystack_[2].value.nodeVal), (yystack_[0].value.nodeVal)},yystack_[2].location.end.line}; }
#line 1007 "parser.tab.cc" // lalr1.cc:859
    break;

  case 66:
#line 208 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_QUANTB,{">="}, {(yystack_[2].value.nodeVal), (yystack_[0].value.nodeVal)},yystack_[2].location.end.line}; }
#line 1013 "parser.tab.cc" // lalr1.cc:859
    break;

  case 68:
#line 212 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_EQUALITY,{"=="}, {(yystack_[2].value.nodeVal), (yystack_[0].value.nodeVal)},yystack_[2].location.end.line}; }
#line 1019 "parser.tab.cc" // lalr1.cc:859
    break;

  case 69:
#line 213 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_EQUALITY,{"!="}, {(yystack_[2].value.nodeVal), (yystack_[0].value.nodeVal)},yystack_[2].location.end.line}; }
#line 1025 "parser.tab.cc" // lalr1.cc:859
    break;

  case 71:
#line 217 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_LOGIC,{"&&"}, {(yystack_[2].value.nodeVal), (yystack_[0].value.nodeVal)},yystack_[2].location.end.line}; }
#line 1031 "parser.tab.cc" // lalr1.cc:859
    break;

  case 73:
#line 221 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_LOGIC,{"||"}, {(yystack_[2].value.nodeVal), (yystack_[0].value.nodeVal)},yystack_[2].location.end.line}; }
#line 1037 "parser.tab.cc" // lalr1.cc:859
    break;

  case 74:
#line 226 "parser.yy" // lalr1.cc:859
    { (yylhs.value.nodeVal) = new node{NODE_ID,{"id (\'"+*(yystack_[0].value.strVal)+"\')"} , {},yystack_[0].location.end.line}; }
#line 1043 "parser.tab.cc" // lalr1.cc:859
    break;

  case 77:
#line 233 "parser.yy" // lalr1.cc:859
    {(yystack_[2].value.nodeVal)->children.push_back(new node{NODE_ASSN,{""},{},yystack_[2].location.end.line});
(yylhs.value.nodeVal) = new node{NODE_EQUALITY,{" ="}, {(yystack_[2].value.nodeVal), (yystack_[0].value.nodeVal)},yystack_[2].location.end.line}; }
#line 1050 "parser.tab.cc" // lalr1.cc:859
    break;

  case 78:
#line 237 "parser.yy" // lalr1.cc:859
    {;}
#line 1056 "parser.tab.cc" // lalr1.cc:859
    break;


#line 1060 "parser.tab.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -62;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      14,   -26,   -62,   -62,   -62,    26,   -26,    14,   -62,   -62,
     -62,    19,   -62,    19,    35,   -62,    47,   -62,   -62,    70,
     -62,   114,   -62,   -62,    49,    94,   -62,    55,    62,    28,
      63,   -62,   -62,   -26,   -62,   -62,   126,   -62,   -62,    76,
     -62,    46,   -62,   -62,   -62,   -26,     2,   -62,    74,   -62,
     -62,   -62,    74,   -62,   -62,   -62,    74,    74,   -62,   -62,
     -62,   -62,   -62,   129,    -8,   118,    37,    52,    66,    46,
     -62,   -62,    97,    74,   102,   -62,   -62,   -62,    48,    74,
     -62,   -62,     5,    72,   110,   -62,   124,   -62,    74,    74,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    74,
      74,   -62,   130,   -62,     3,   -62,   -62,   -62,    87,   -62,
     -62,   -62,   -62,   129,   129,    -8,    -8,    -8,    -8,   118,
     118,    37,    52,    87,   -62,    74,   -62,   133,   -62,    87,
     -62
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       2,     0,     8,     9,    74,     0,     0,     3,    10,    12,
      13,     0,    14,     0,     0,    18,     0,     1,    17,     0,
      11,     0,    16,    24,     0,     0,    15,     0,     0,     0,
       0,    33,    27,     0,    30,    34,     0,    28,    31,     0,
      42,     0,    41,    25,    19,     0,     0,    21,     0,    35,
       5,    37,     0,     6,     7,     4,     0,     0,    43,    50,
      45,    54,    55,    59,    62,    67,    70,    72,    75,    51,
      78,    76,     0,     0,     0,    26,    29,    32,     0,     0,
      23,    20,     0,     0,     0,    52,    51,    53,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    36,     0,    49,     0,    46,    77,    22,     0,    44,
      56,    57,    58,    60,    61,    66,    63,    65,    64,    68,
      69,    71,    73,     0,    48,     0,    40,    38,    47,     0,
      39
  };

  const short int
  Parser::yypgoto_[] =
  {
     -62,   -62,   -62,   -17,   -62,   131,    -9,   -62,   -62,   139,
     -62,    65,   -62,   -62,    11,   -62,   112,   -61,   -62,   -62,
     -62,   -19,   -62,   -46,     7,    61,    18,    53,    64,   -62,
       0,    82,   -18,   -43
  };

  const signed char
  Parser::yydefgoto_[] =
  {
      -1,     5,    58,     6,     7,     8,     9,    10,    11,    15,
      46,    47,    12,    13,    35,    36,    37,    38,    39,    59,
     104,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      86,    70,    71,    72
  };

  const unsigned char
  Parser::yytable_[] =
  {
      14,    16,    40,    42,    33,    83,    19,    14,    45,    84,
      85,    87,    34,     4,    81,   124,    91,    40,    42,    33,
      92,    41,    22,     1,    23,     2,    17,    34,     3,    69,
     102,    50,    21,    74,     2,   105,    41,     3,    51,    52,
      82,   125,   110,   111,   112,    80,    24,   126,    69,    53,
      54,    50,    69,     4,    97,    55,    56,    78,    25,    52,
     103,    43,   127,    57,    79,    45,    48,     4,   130,    53,
      54,    98,    49,    69,    73,    55,    56,    50,    69,    69,
      26,    25,   128,    57,   108,    52,    77,     4,    99,    40,
      42,    27,    28,    29,    30,    53,    54,    31,   113,   114,
      21,    55,    56,   100,    40,    42,    44,   101,    41,    57,
      40,    42,    26,     4,     2,   119,   120,     3,    27,    28,
      29,    30,   109,    41,    31,    69,     4,    21,    32,    41,
      27,    28,    29,    30,     2,    78,    31,     3,    20,    21,
      75,   129,   123,    93,    94,    18,     2,   107,    76,     3,
      95,    96,   121,     4,   115,   116,   117,   118,    88,    89,
      90,   106,     0,     0,   122,     4
  };

  const short int
  Parser::yycheck_[] =
  {
       0,     1,    21,    21,    21,    48,     6,     7,    25,    52,
      56,    57,    21,    39,    12,    12,    24,    36,    36,    36,
      28,    21,    11,     9,    13,    20,     0,    36,    23,    29,
      73,     3,    13,    33,    20,    78,    36,    23,    10,    11,
      38,    38,    88,    89,    90,    45,    11,   108,    48,    21,
      22,     3,    52,    39,    17,    27,    28,    11,    11,    11,
      12,    12,   123,    35,    18,    82,    11,    39,   129,    21,
      22,    34,    10,    73,    11,    27,    28,     3,    78,    79,
      10,    11,   125,    35,    12,    11,    10,    39,    36,   108,
     108,     4,     5,     6,     7,    21,    22,    10,    91,    92,
      13,    27,    28,    37,   123,   123,    12,    10,   108,    35,
     129,   129,    10,    39,    20,    97,    98,    23,     4,     5,
       6,     7,    12,   123,    10,   125,    39,    13,    14,   129,
       4,     5,     6,     7,    20,    11,    10,    23,     7,    13,
      14,     8,    12,    25,    26,     6,    20,    82,    36,    23,
      32,    33,    99,    39,    93,    94,    95,    96,    29,    30,
      31,    79,    -1,    -1,   100,    39
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     9,    20,    23,    39,    42,    44,    45,    46,    47,
      48,    49,    53,    54,    71,    50,    71,     0,    50,    71,
      46,    13,    55,    55,    11,    11,    10,     4,     5,     6,
       7,    10,    14,    44,    47,    55,    56,    57,    58,    59,
      62,    71,    73,    12,    12,    44,    51,    52,    11,    10,
       3,    10,    11,    21,    22,    27,    28,    35,    43,    60,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    11,    71,    14,    57,    10,    11,    18,
      71,    12,    38,    74,    74,    64,    71,    64,    29,    30,
      31,    24,    28,    25,    26,    32,    33,    17,    34,    36,
      37,    10,    74,    12,    61,    74,    72,    52,    12,    12,
      64,    64,    64,    65,    65,    66,    66,    66,    66,    67,
      67,    68,    69,    12,    12,    38,    58,    58,    74,     8,
      58
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    41,    42,    42,    43,    43,    43,    43,    44,    44,
      45,    45,    46,    46,    46,    47,    48,    49,    49,    50,
      50,    51,    51,    52,    53,    54,    55,    55,    56,    56,
      57,    57,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    59,    59,    60,    60,    60,    61,    61,    62,    62,
      63,    63,    64,    64,    64,    65,    65,    65,    65,    66,
      66,    66,    67,    67,    67,    67,    67,    68,    68,    68,
      69,    69,    70,    70,    71,    72,    72,    73,    74
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     0,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     3,     2,     2,     2,     3,
       4,     1,     3,     2,     2,     3,     3,     2,     1,     2,
       1,     1,     2,     1,     1,     2,     3,     2,     5,     7,
       5,     1,     1,     1,     3,     1,     1,     3,     4,     3,
       1,     1,     2,     2,     1,     1,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     3,     1,     3,     3,
       1,     3,     1,     3,     1,     1,     1,     3,     1
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "$end", "error", "$undefined", "\"t_string\"", "\"_while\"",
  "\"_break\"", "\"_return\"", "\"_if\"", "\"_else\"", "\"_void\"",
  "\"semicolon\"", "\"lround\"", "\"rround\"", "\"lcurl\"", "\"rcurl\"",
  "\"lsquare\"", "\"rsqure\"", "\"cmp\"", "\"eq\"", "\"dot\"", "\"_bool\"",
  "\"_true\"", "\"_false\"", "\"_int\"", "\"plus\"", "\"ge\"", "\"gt\"",
  "\"number\"", "\"minus\"", "\"star\"", "\"slash\"", "\"perct\"",
  "\"le\"", "\"lt\"", "\"ncmp\"", "\"not\"", "\"_and\"", "\"or\"",
  "\"comma\"", "\"id\"", "\"error token\"", "$accept", "START", "literal",
  "type", "globaldeclarations", "globaldeclaration", "variabledeclaration",
  "functiondeclaration", "functionheader", "functiondeclarator",
  "formalparameterlist", "formalparameter", "mainfunctiondeclaration",
  "mainfunctiondeclarator", "block", "blockstatements", "blockstatement",
  "statement", "statementexpression", "primary", "argumentlist",
  "functioninvocation", "postfixexpression", "unaryexpression",
  "multiplicativeexpression", "additiveexpression", "relationalexpression",
  "equalityexpression", "conditionalandexpression",
  "conditionalorexpression", "identifier", "assignmentexpression",
  "assignment", "expression", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,    81,    81,    82,    85,    86,    87,    88,    91,    92,
      95,    96,    99,   100,   101,   104,   108,   115,   116,   119,
     120,   123,   124,   127,   132,   135,   138,   139,   142,   143,
     146,   147,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   162,   163,   166,   167,   168,   171,   172,   175,   178,
     183,   184,   187,   189,   190,   193,   194,   195,   196,   199,
     200,   201,   204,   205,   206,   207,   208,   211,   212,   213,
     216,   217,   220,   221,   226,   229,   230,   233,   237
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
    };
    const unsigned int user_token_number_max_ = 295;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // yy
#line 1587 "parser.tab.cc" // lalr1.cc:1167
#line 239 "parser.yy" // lalr1.cc:1168


void yy::Parser::error(yy::location const& l, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const& s){
	
	std::cout<<"Parser error on line "<<l.end.line<<" : "<<s<<"\n";
}
