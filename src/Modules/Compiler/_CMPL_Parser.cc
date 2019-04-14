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

// Take the name prefix into account.
#define yylex   cmpllex

// First part of user declarations.
#line 36 "CMPL_Parser.yy" // lalr1.cc:404

namespace cmpl
{
    class CompilerContext;
	class SyntaxElement;
}
#line 53 "CMPL_Parser.yy" // lalr1.cc:404

#include "../../CommonData/SyntaxElements.hh"
#include "CompilerUtil.hh"
#include "CompilerContext.hh"

#define CMPLCOMP_FOR_SCANNER    cmplcomp._scanner

// in the skeleton the definition of yyerrok is missing, thats why it is defined here
#define yyerrok     (yyerrstatus_ = 0)

#line 56 "_CMPL_Parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "_CMPL_Parser.hh"

// User implementation prologue.
#line 110 "CMPL_Parser.yy" // lalr1.cc:412

#include "../../Control/MainControl.hh"
#define PROTO_PC_OUT(a)		PROTO_MOD_OUT((&cmplcomp), a)
#define PROTO_PC_OUTL(a)	PROTO_MOD_OUTL((&cmplcomp), a)
#define PARSE_CONTEXT		cmplcomp


// defines for location output
#define CMPLELEMENTRY(s,n,lf,lt)			{ s._empty = false; s._elem = SyntaxElement::newEntry(PARSE_CONTEXT.nextIdSyntaxElem(), n, &lf, &lt); }
#define CMPLELEMENTRY_TXT(s,n,lf,lt,t)		{ s._empty = false; s._elem = SyntaxElement::newEntry(PARSE_CONTEXT.nextIdSyntaxElem(), n, t, &lf, &lt); }
#define CMPLELEMENTRY_ALT(s,n,lf,lt,t,a)	{ s._empty = false; s._elem = SyntaxElement::newEntry(PARSE_CONTEXT.nextIdSyntaxElem(), n, t, a, &lf, &lt); }
#define CMPLELEMENTRY_SYM(s,n,lf,lt,sym)	{ s._empty = false; s._elem = SyntaxElement::newEntry(PARSE_CONTEXT.nextIdSyntaxElem(), n, (sym)->nameGlob(), (sym)->defId(), &lf, &lt); }
#define CMPLELEMENTRY_ERR(s,lf)				{ s._empty = false; s._elem = PARSE_CONTEXT.errorRecoveryElem(&lf); }
#define CMPLELEMENTRY_EMPTY(s,lf)			{ s._empty = false; s._elem = SyntaxElement::newEntry(PARSE_CONTEXT.nextIdSyntaxElem(), SyntaxElementEmpty, &lf, &lf); }

#define CMPLELEM_SET(s,b)					{ s._empty = b._empty; s._elem = b._elem; }
#define CMPLELEM_NEXT(s,n)					{ s._elem->appendNext(n._elem); }
#define CMPLELEM_CONCAT(s,b,n)				{ s._empty = b._empty; s._elem = b._elem; if (s._empty) { CMPLELEM_SET(s,n) } else s._elem->appendNext(n._elem); }
#define CMPLELEM_CHILD(s,c)					{ s._elem->appendChild(c._elem); }
#define CMPLELEM_CHILD2(s,c,d)				{ s._elem->appendChild(c._elem); s._elem->appendChild(d._elem); }

#define SET_CMPLELEM(c,lf)					{ PARSE_CONTEXT.setSyntaxStructure(c._elem, &lf); }


// defines for generating intermediary code
#define COMP_END(e)							{ if (!PARSE_CONTEXT.checkOnly()) PARSE_CONTEXT.compFunction(e, false, false, 0, 0, false); }
#define COMP_LIT_VALUE(e,s,t)				{ if (!PARSE_CONTEXT.checkOnly()) PARSE_CONTEXT.compLitVal(e, s, t); }
#define COMP_LIT_BLANK(ar)					{ if (!PARSE_CONTEXT.checkOnly()) ar = PARSE_CONTEXT.compLitVal(NULL, "", ICS_LIT_BLANK); }
#define COMP_FETCH_SYM(e,s)					{ if (!PARSE_CONTEXT.checkOnly()) PARSE_CONTEXT.compFetchSym(e, s); }
#define COMP_INCDEC_FETCH(e,b,i)			{ if (!PARSE_CONTEXT.checkOnly()) PARSE_CONTEXT.compIncDecFetch(e, b, i); }
#define COMP_ASSIGN(e,lhs,rhs)				{ if (!PARSE_CONTEXT.checkOnly()) PARSE_CONTEXT.compAssign(e, lhs, rhs); }
#define COMP_OPERATION(e,op,c)				{ if (!PARSE_CONTEXT.checkOnly()) PARSE_CONTEXT.compOperation(e, false, op, c); }
#define COMP_CONSTRUCT(e,op,c)				{ if (!PARSE_CONTEXT.checkOnly()) PARSE_CONTEXT.compOperation(e, true, op, c); }
#define COMP_FUNC_START(e,ar)				{ if (!PARSE_CONTEXT.checkOnly()) ar = PARSE_CONTEXT.compFunction(e, true, true, 0, 0, false); }
#define COMP_FUNC_END(e,a,cl,us)			{ if (!PARSE_CONTEXT.checkOnly()) PARSE_CONTEXT.compFunction(e, true, false, a, cl, us); }
#define COMP_LNP_COMPAT(e,s)				{ if (!PARSE_CONTEXT.checkOnly()) PARSE_CONTEXT.compLineNamePrefCompat(e, s); }
#define COMP_CBHEADER_START(e,ar)			{ if (!PARSE_CONTEXT.checkOnly()) ar = PARSE_CONTEXT.compCBHeaderStart(e); }
#define COMP_CBHEADER_END(e,x,s)			{ if (!PARSE_CONTEXT.checkOnly()) PARSE_CONTEXT.compCBHeaderEnd(e, x, s); }
#define COMP_SET_SYNTAXELEM(a,e)			{ if (!PARSE_CONTEXT.checkOnly()) PARSE_CONTEXT.compSetCmdSyntaxElem(a, e); }


// does nothing, only to suppress warnings about not used token values, that bison prints out when use %destructor
#define NOT_USED(a)

#line 114 "_CMPL_Parser.cc" // lalr1.cc:412


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


namespace cmpl {
#line 200 "_CMPL_Parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  CMPL_Parser::yytnamerr_ (const char *yystr)
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
  CMPL_Parser::CMPL_Parser (CompilerContext& cmplcomp_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      cmplcomp (cmplcomp_yyarg)
  {}

  CMPL_Parser::~CMPL_Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/

  inline
  CMPL_Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  CMPL_Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  CMPL_Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
    value = other.value;
  }


  template <typename Base>
  inline
  CMPL_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  /// Constructor for valueless symbols.
  template <typename Base>
  inline
  CMPL_Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  inline
  CMPL_Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  CMPL_Parser::basic_symbol<Base>::clear ()
  {
    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  CMPL_Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  CMPL_Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
    value = s.value;
    location = s.location;
  }

  // by_type.
  inline
  CMPL_Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  CMPL_Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  CMPL_Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  CMPL_Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  CMPL_Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  CMPL_Parser::by_type::type_get () const
  {
    return type;
  }


  // by_state.
  inline
  CMPL_Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  CMPL_Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  CMPL_Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  CMPL_Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  CMPL_Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  CMPL_Parser::symbol_number_type
  CMPL_Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  CMPL_Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  CMPL_Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
    value = that.value;
    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  CMPL_Parser::stack_symbol_type&
  CMPL_Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    value = that.value;
    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  CMPL_Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);

    // User destructor.
    switch (yysym.type_get ())
    {
            case 1: // error

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 453 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 3: // "operator `->`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 460 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 4: // "assign operator `:=`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 467 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 9: // "operator `||`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 474 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 10: // "operator `&&`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 481 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 11: // "operator `=`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 488 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 12: // "operator `==`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 495 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 13: // "operator `<>`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 502 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 14: // "operator `!=`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 509 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 15: // "operator `<`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 516 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 16: // "operator `>`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 523 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 17: // "operator `<=`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 530 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 18: // "operator `>=`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 537 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 19: // "operator `in`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 544 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 20: // "operator `of`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 551 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 25: // "operator `*>`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 558 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 26: // "transpose operator `T`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 565 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 28: // "operator `..`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 572 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 31: // "operator `!`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 579 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 34: // "`{`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 586 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 35: // "subsymbol operator `.`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 593 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 36: // "int literal"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 600 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 37: // "double literal"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 607 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 38: // "string literal"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 614 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 39: // "linename prefix"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 621 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 40: // "int literal factor"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 628 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 41: // "double literal factor"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 635 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 42: // "symbol"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 642 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 43: // "subsymbol"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 649 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 44: // "object type symbol"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 656 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 45: // "data type symbol"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 663 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 46: // "assign modificator"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 670 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 47: // "order modificator"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 677 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 48: // "assign operator `::=`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 684 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 49: // "assign operator `+=`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 691 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 50: // "assign operator `-=`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 698 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 51: // "assign operator `*=`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 705 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 52: // "assign operator `/=`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 712 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 53: // "increment/decrement operator"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 719 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 54: // "`:`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 726 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 55: // "`}`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 733 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 56: // "`|`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 740 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 57: // "`&`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 747 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 58: // "`@`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 754 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 59: // "`;`"

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 761 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 64: // cmpl

#line 228 "CMPL_Parser.yy" // lalr1.cc:614
        { }
#line 768 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 65: // cmplParts

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 775 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 66: // cmplPart

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 782 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 67: // directive

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 789 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 68: // directiveParts

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 796 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 69: // directivePart

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 803 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 70: // objDataType

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 810 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 71: // statement

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 817 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 72: // statementExpr

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 824 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 73: // assignLhsOp

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 831 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 74: // assignRhs

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 838 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 75: // objDataTypeRhs

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 845 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 76: // assignOp

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 852 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 77: // codeblock

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 859 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 78: // blockStart

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 866 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 79: // blockParts

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 873 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 80: // blockAltStart

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 880 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 81: // blockPart

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 887 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 82: // blockPartStart

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 894 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 83: // blockModifiers

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 901 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 84: // blockModifier

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 908 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 85: // blockHeaders

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 915 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 86: // blockHeader

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 922 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 87: // blockHeaderStart

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 929 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 88: // blockBody

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 936 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 89: // expressionWithCodeblockSymbolDef

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 943 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 90: // refcodeblock

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 950 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 91: // expression

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 957 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 92: // symbolIncDec

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 964 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 93: // symbol

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 971 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 94: // expressionList

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 978 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 95: // literal

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 985 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 96: // literalMult

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 992 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 97: // arrayExpr

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 999 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 98: // arrayStart

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1006 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 99: // tupleExpr

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1013 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 100: // tupleStart

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1020 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 101: // listParts

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1027 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 102: // listPart

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1034 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 103: // intervalExpr

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1041 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 104: // intervalOp

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1048 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 105: // setExpr

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1055 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 106: // setExprEnd

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1062 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 107: // unaryOp

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1069 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 108: // binaryOp

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1076 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 109: // numOpSignAdd

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1083 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 110: // numOpSignMult

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1090 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 111: // logOpSignNot

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1097 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 112: // inOpPre

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1104 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 113: // ofOpPre

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1111 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 114: // compareOp

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1118 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 115: // subsymbolOp

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1125 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 116: // subsymbolIncDec

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1132 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 117: // subsymbol

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1139 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 118: // functionCall

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1146 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 119: // indexation

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1153 "_CMPL_Parser.cc" // lalr1.cc:614
        break;

      case 120: // errorExpression

#line 229 "CMPL_Parser.yy" // lalr1.cc:614
        { if (!(yysym.value.s)._empty) { PARSE_CONTEXT.insertErrElem((yysym.value.s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ }
#line 1160 "_CMPL_Parser.cc" // lalr1.cc:614
        break;


      default:
        break;
    }
  }

#if YYDEBUG
  template <typename Base>
  void
  CMPL_Parser::yy_print_ (std::ostream& yyo,
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
  CMPL_Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  CMPL_Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  CMPL_Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  CMPL_Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  CMPL_Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  CMPL_Parser::debug_level_type
  CMPL_Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  CMPL_Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline CMPL_Parser::state_type
  CMPL_Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  CMPL_Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  CMPL_Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  CMPL_Parser::parse ()
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
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location, CMPLCOMP_FOR_SCANNER, cmplcomp));
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
#line 237 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PROTO_PC_OUTL("Parse cmpl End"); SET_CMPLELEM((yystack_[0].value.s), yystack_[0].location); COMP_END((yystack_[0].value.s)._elem); }
#line 1399 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 3:
#line 240 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); }
#line 1405 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 241 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEM_CONCAT((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s)); }
#line 1411 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 5:
#line 244 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeStatementStart(); PARSE_CONTEXT.setDirectiveFromCurrent(&yystack_[0].location); }
#line 1417 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 245 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeStatementStart(); PARSE_CONTEXT.clearModificators(); }
#line 1423 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 7:
#line 248 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementDirective, yystack_[1].location, yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[1].value.s)); NOT_USED((yystack_[0].value.s)); }
#line 1429 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 251 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); }
#line 1435 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 252 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEM_CONCAT((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s)); }
#line 1441 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 255 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementModificator, yystack_[0].location, yystack_[0].location, (yystack_[0].value.s)._name); PARSE_CONTEXT.setModificator(&yystack_[0].location, (ModificatorKey) (yystack_[0].value.s)._u.i); }
#line 1447 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 256 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementModificator, yystack_[0].location, yystack_[0].location, (yystack_[0].value.s)._name); PARSE_CONTEXT.setModificator(&yystack_[0].location, (ModificatorKey) (yystack_[0].value.s)._u.i); }
#line 1453 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 257 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); CMPLELEM_SET((yylhs.value.s), (yystack_[0].value.s)); PARSE_CONTEXT.setModificator(&yystack_[0].location, (yystack_[0].value.s)._u.exp->sym(), (SPECIALSYMBOL_IS_OBJTYPE((yystack_[0].value.s)._u.exp->sym()->special())));
																				  delete (yystack_[0].value.s)._u.exp; }
#line 1460 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 259 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementLineNamePrefix, yystack_[0].location, yystack_[0].location);
																				  PARSE_CONTEXT.setLineNamePref((yylhs.value.s)._elem, &yystack_[0].location, (yystack_[0].value.s)._u.s); }
#line 1467 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 263 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); CMPLELEMENTRY_SYM((yylhs.value.s), SyntaxElementSymbol, yystack_[0].location, yystack_[0].location, (yystack_[0].value.s)._u.exp->sym()); }
#line 1473 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 264 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); CMPLELEMENTRY_SYM((yylhs.value.s), SyntaxElementSymbol, yystack_[0].location, yystack_[0].location, (yystack_[0].value.s)._u.exp->sym()); }
#line 1479 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 272 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init();
		   																		  if (!(yystack_[1].value.s)._empty && PARSE_CONTEXT.testCompControlCB((yystack_[1].value.s)._elem, yystack_[1].location, false)) { CMPLELEMENTRY((yylhs.value.s), SyntaxElementStatement, yystack_[1].location, yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[1].value.s)); }
																				  else { CMPLELEMENTRY_EMPTY((yystack_[0].value.s), yystack_[0].location); CMPLELEMENTRY((yylhs.value.s), SyntaxElementStatement, yystack_[0].location, yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[0].value.s)); }
																				  PARSE_CONTEXT.endOfStatement((yylhs.value.s)._elem); }
#line 1488 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 276 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init();
																				  if ((yystack_[1].value.s)._u.b) PARSE_CONTEXT.testCompControlCB((yystack_[2].value.s)._elem, yystack_[2].location, true);
																				  CMPLELEMENTRY((yylhs.value.s), SyntaxElementStatement, ((yystack_[2].value.s)._empty ? (yystack_[1].location) : (yystack_[2].location)), yystack_[0].location); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[1].value.s)); PARSE_CONTEXT.endOfStatement((yylhs.value.s)._elem); NOT_USED((yystack_[0].value.s)); }
#line 1496 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 279 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_ERR((yystack_[1].value.s), yystack_[1].location); CMPLELEMENTRY((yylhs.value.s), SyntaxElementStatement, yystack_[1].location, yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[1].value.s)); PARSE_CONTEXT.endOfStatement((yylhs.value.s)._elem); NOT_USED((yystack_[0].value.s));
																				  yyerrok; }
#line 1503 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 19:
#line 283 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementAssignRhs, yystack_[0].location, yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[0].value.s)); CMPLELEM_SET((yystack_[0].value.s), (yylhs.value.s));
			  																	  CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementAssignment, yystack_[1].location, yystack_[0].location, (yystack_[1].value.s)._u.exp->assignOp()); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s));
																				  if ((yystack_[1].value.s)._u.exp->isRefAssign()) { (yystack_[0].value.s)._u.exp->compChangeFetchLvalue(&PARSE_CONTEXT); }
																				  COMP_ASSIGN((yylhs.value.s)._elem, (yystack_[1].value.s)._u.exp, (yystack_[0].value.s)._u.exp);
																				  (yystack_[0].value.s)._u.exp->checkClearLvalSyms(&PARSE_CONTEXT);
																				  (yystack_[1].value.s)._u.exp->assignSpecialToConst((yystack_[0].value.s)._u.exp->special());
																				  delete (yystack_[1].value.s)._u.exp; delete (yystack_[0].value.s)._u.exp; (yylhs.value.s)._u.b = false; }
#line 1515 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 290 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s);
																				  bool controlCB = false;
																				  bool amEmpty = PARSE_CONTEXT.assignModCurrentEmpty(true);
																				  if ((yystack_[0].value.s)._u.exp->setAssignIfLhs(&PARSE_CONTEXT)) {
																				  	(yystack_[0].value.s)._u.exp->checkLNPError(&PARSE_CONTEXT);
																				  	CMPLELEMENTRY((yylhs.value.s), SyntaxElementAssignLhs, yystack_[0].location, yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[0].value.s));
																					COMP_ASSIGN((yylhs.value.s)._elem, (yystack_[0].value.s)._u.exp, NULL); }
																				  else {
																				    controlCB = PARSE_CONTEXT.assignModControlCB(&yystack_[0].location);
																					if (!controlCB) {
																				  		if (!amEmpty) PARSE_CONTEXT.outParseError(ERROR_LVL_NORMAL, "statement cannot have assign modificators", yystack_[0].location);
																						COMP_ASSIGN((yylhs.value.s)._elem, NULL, (yystack_[0].value.s)._u.exp); } }
																				  delete (yystack_[0].value.s)._u.exp; (yylhs.value.s)._u.b = controlCB; }
#line 1533 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 305 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[1].value.s); CMPLELEMENTRY((yylhs.value.s), SyntaxElementAssignLhs, yystack_[1].location, yystack_[1].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[1].value.s));
			 																	  (yystack_[1].value.s)._u.exp->checkLNPError(&PARSE_CONTEXT);
			 																	  (yylhs.value.s)._u.exp->setAssignLhs(&PARSE_CONTEXT, (yystack_[0].value.s)._name, &yystack_[0].location); }
#line 1541 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 310 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); (yystack_[0].value.s)._u.exp->checkLNPError(&PARSE_CONTEXT); }
#line 1547 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 311 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); }
#line 1553 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 312 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementIndexation, yystack_[1].location, yystack_[0].location); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s));
																				  (yylhs.value.s).setExp((yystack_[1].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_IND, (yystack_[0].value.s)._u.exp, true)); }
#line 1560 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 316 "CMPL_Parser.yy" // lalr1.cc:859
    { COMP_FETCH_SYM((yylhs.value.s)._elem, (yystack_[0].value.s)._u.exp); (yylhs.value.s)._u.exp->checkSetCbhExpr(&PARSE_CONTEXT); }
#line 1566 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 319 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1572 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 320 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1578 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 321 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1584 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 322 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1590 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 323 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1596 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 324 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1602 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 325 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1608 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 332 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementCodeblock, yystack_[2].location, yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[1].value.s)); NOT_USED((yystack_[2].value.s)); NOT_USED((yystack_[0].value.s));
		   																		  (yylhs.value.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yylhs.value.s)._elem->loc(), specialSymbolNo, false, true));
																				  (yylhs.value.s)._u.fnc.exp = (yylhs.value.s)._u.exp; (yylhs.value.s)._u.fnc.cntLocal = PARSE_CONTEXT.funcParseScopeInfo((yylhs.value.s)._u.fnc.useSubs);
		   																		  PARSE_CONTEXT.endParseScope((yylhs.value.s)._elem, yystack_[0].location); }
#line 1617 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 336 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_ERR((yystack_[1].value.s), yystack_[1].location); CMPLELEMENTRY((yylhs.value.s), SyntaxElementCodeblock, yystack_[2].location, yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[1].value.s)); NOT_USED((yystack_[2].value.s)); NOT_USED((yystack_[0].value.s));
																				  (yylhs.value.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yylhs.value.s)._elem->loc(), specialSymbolNo, false, true));
																				  (yylhs.value.s)._u.fnc.exp = (yylhs.value.s)._u.exp; (yylhs.value.s)._u.fnc.cntLocal = PARSE_CONTEXT.funcParseScopeInfo((yylhs.value.s)._u.fnc.useSubs);
																				  PARSE_CONTEXT.endParseScope((yylhs.value.s)._elem, yystack_[0].location);
																				  yyerrok; }
#line 1627 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 343 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.startParseScope((yylhs.value.s)._elem, yystack_[0].location, parseScopeTypeBlock, (yystack_[0].value.s)._u.sptt);
																				  PARSE_CONTEXT.setCbExprModeReset(); }
#line 1634 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 347 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); }
#line 1640 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 348 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEM_CONCAT((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); NOT_USED((yystack_[1].value.s)); }
#line 1646 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 351 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.startParseScope((yylhs.value.s)._elem, yystack_[0].location, parseScopeTypePart); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1652 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 354 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementBlockPart, yystack_[1].location, yystack_[0].location); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s)); delete (yystack_[1].value.s)._u.exp; PARSE_CONTEXT.setPartParseScopeElem((yylhs.value.s)._elem); }
#line 1658 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 357 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[1].value.s); PARSE_CONTEXT.startParseScope((yystack_[0].value.s)._elem, yystack_[0].location, parseScopeTypeBody); PARSE_CONTEXT.setCbExprModeCBBodyStart(); NOT_USED((yystack_[2].value.s)); }
#line 1664 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 360 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); }
#line 1670 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 361 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEM_CONCAT((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s)); }
#line 1676 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 364 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementModificator, yystack_[0].location, yystack_[0].location, (yystack_[0].value.s)._name); PARSE_CONTEXT.setParseScopeParBlockPart(ICPAR_BLOCK_ORDERED); }
#line 1682 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 367 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init();
			 																	  if ((yystack_[0].value.s)._empty) { CMPLELEMENTRY_EMPTY((yystack_[0].value.s), yystack_[0].location); (yystack_[0].value.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, yystack_[0].location)); }
			 																	  CMPLELEMENTRY((yylhs.value.s), SyntaxElementBlockHeader, yystack_[0].location, yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[0].value.s));
																				  (yylhs.value.s).setExp((yystack_[0].value.s)._u.exp); }
#line 1691 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 371 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init();
																				  if ((yystack_[2].value.s)._empty) { CMPLELEMENTRY_EMPTY((yystack_[2].value.s), yystack_[2].location); (yystack_[2].value.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, yystack_[2].location)); }
																				  CMPLELEMENTRY((yylhs.value.s), SyntaxElementBlockHeader, yystack_[2].location, yystack_[2].location); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s));
																				  (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CBHCAT, (yystack_[0].value.s)._u.exp, true)); }
#line 1700 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 377 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); }
#line 1706 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 378 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); (yylhs.value.s)._u.exp->setAssignCbh(&PARSE_CONTEXT); COMP_CBHEADER_END((yylhs.value.s)._elem, (yylhs.value.s)._u.exp, (yystack_[1].value.s)._u.cbr.a); (yylhs.value.s)._u.exp->resetCbhExpr(); }
#line 1712 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 381 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); COMP_CBHEADER_START(NULL, (yylhs.value.s)._u.cbr.a); }
#line 1718 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 384 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementBlockBody, yystack_[1].location, yystack_[0].location); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s));
		   																		  if (!(yystack_[1].value.s)._empty) {
																				  	if (!PARSE_CONTEXT.assignModCurrentEmpty()) PARSE_CONTEXT.outParseError(ERROR_LVL_NORMAL, "expression as code block body cannot have assign modificators", yystack_[1].location);
																					if (PARSE_CONTEXT.hasLineNamePref()) PARSE_CONTEXT.outParseError(ERROR_LVL_NORMAL, "expression as code block body cannot have line name prefix", yystack_[1].location);
																				  }
																				  (yystack_[0].value.s)._u.exp->checkLNPError(&PARSE_CONTEXT); (yystack_[0].value.s)._u.exp->checkClearLvalSyms(&PARSE_CONTEXT);
																				  if ((yystack_[0].value.s)._u.exp->ncSymAccess()) PARSE_CONTEXT.setParseScopeParBlockPart(ICPAR_BLOCK_NCSYM);
		   																		  delete (yystack_[0].value.s)._u.exp; }
#line 1731 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 392 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementBlockBody, yystack_[0].location, yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[0].value.s)); PARSE_CONTEXT.setParseScopeParBlockPart(ICPAR_BLOCK_STMNT); }
#line 1737 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 395 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); (yystack_[0].value.s)._u.exp->checkLNPError(&PARSE_CONTEXT); }
#line 1743 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 396 "CMPL_Parser.yy" // lalr1.cc:859
    { (yystack_[2].value.s)._u.exp->checkCbhAssignError(&PARSE_CONTEXT, yystack_[1].location);
																				  (yylhs.value.s).init(); CMPLELEMENTRY_ALT((yylhs.value.s), SyntaxElementCompareOp, yystack_[2].location, yystack_[0].location, (yystack_[2].value.s)._name, "=="); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); NOT_USED((yystack_[1].value.s));
																				  (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, ICS_OPER_EQ2, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_EQ, 2); }
#line 1752 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 402 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); (yylhs.value.s)._u.cbr.b = (yystack_[0].value.s)._u.b; COMP_FUNC_START((yylhs.value.s)._elem, (yylhs.value.s)._u.cbr.a); }
#line 1758 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 408 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeResetStorePrv(); }
#line 1764 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 409 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1770 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 410 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1776 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 411 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1782 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 412 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1788 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 413 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1794 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 414 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1800 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 415 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1806 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 416 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1812 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 417 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1818 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 418 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1824 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 419 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1830 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 420 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1836 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 421 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); (yylhs.value.s)._u.exp = (yystack_[0].value.s)._u.fnc.exp; (yylhs.value.s)._u.exp->resetVolaExp();
																				  CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementFunction, yystack_[1].location, yystack_[0].location, ((yystack_[1].value.s)._u.cbr.b ? "pure" : "nonpure")); CMPLELEM_CHILD((yylhs.value.s), (yystack_[0].value.s));
																				  COMP_FUNC_END((yylhs.value.s)._elem, (yystack_[1].value.s)._u.cbr.a, (yystack_[0].value.s)._u.fnc.cntLocal, (yystack_[0].value.s)._u.fnc.useSubs);
																				  PARSE_CONTEXT.setCbExprModeReset(); }
#line 1845 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 425 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset();
																				  PARSE_CONTEXT.outParseError(ERROR_LVL_NORMAL, "illegal expression, maybe missing operation sign", yystack_[0].location); }
#line 1852 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 429 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); (yylhs.value.s)._u.exp->checkSetCbhExpr(&PARSE_CONTEXT); }
#line 1858 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 430 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementIncDec, yystack_[1].location, yystack_[0].location, ((yystack_[1].value.s)._u.i > 0 ? "prefix inc" : "prefix dec")); CMPLELEM_CHILD((yylhs.value.s), (yystack_[0].value.s));
																				  (yylhs.value.s).setExp((yystack_[0].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_INC, NULL, false));
																				  (yylhs.value.s)._u.exp->checkSetCbhExpr(&PARSE_CONTEXT);
																				  COMP_INCDEC_FETCH((yylhs.value.s)._elem, true, (yystack_[1].value.s)._u.i); }
#line 1867 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 434 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[1].value.s); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementIncDec, yystack_[1].location, yystack_[0].location, ((yystack_[0].value.s)._u.i > 0 ? "postfix inc" : "postfix dec")); CMPLELEM_CHILD((yylhs.value.s), (yystack_[1].value.s));
																				  (yylhs.value.s).setExp((yystack_[1].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_INC, NULL, false));
																				  (yylhs.value.s)._u.exp->checkSetCbhExpr(&PARSE_CONTEXT);
																				  COMP_INCDEC_FETCH((yylhs.value.s)._elem, false, (yystack_[0].value.s)._u.i); }
#line 1876 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 72:
#line 440 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); CMPLELEMENTRY_SYM((yylhs.value.s), SyntaxElementSymbol, yystack_[0].location, yystack_[0].location, (yystack_[0].value.s)._u.exp->sym());
		 																		  COMP_FETCH_SYM((yylhs.value.s)._elem, (yystack_[0].value.s)._u.exp);
																				  (yylhs.value.s)._u.exp->setLvalueSyntaxElem((yylhs.value.s)._elem); }
#line 1884 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 73:
#line 445 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); }
#line 1890 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 74:
#line 446 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEM_CONCAT((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CAT, (yystack_[0].value.s)._u.exp, true)); }
#line 1896 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 75:
#line 449 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); CMPLELEMENTRY((yylhs.value.s), SyntaxElementLitDouble, yystack_[0].location, yystack_[0].location);
		  																		  COMP_LIT_VALUE((yylhs.value.s)._elem, (yystack_[0].value.s)._u.s, ICS_LIT_REAL); (yylhs.value.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, yystack_[0].location)); }
#line 1903 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 76:
#line 451 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); CMPLELEMENTRY((yylhs.value.s), SyntaxElementLitInt, yystack_[0].location, yystack_[0].location);
																				  COMP_LIT_VALUE((yylhs.value.s)._elem, (yystack_[0].value.s)._u.s, ICS_LIT_INT); (yylhs.value.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, yystack_[0].location)); }
#line 1910 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 77:
#line 453 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); CMPLELEMENTRY((yylhs.value.s), SyntaxElementLitString, yystack_[0].location, yystack_[0].location);
																				  COMP_LIT_VALUE((yylhs.value.s)._elem, (yystack_[0].value.s)._u.s, ICS_LIT_STR); (yylhs.value.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, yystack_[0].location)); }
#line 1917 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 78:
#line 457 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); CMPLELEMENTRY((yylhs.value.s), SyntaxElementLitDouble, yystack_[0].location, yystack_[0].location);
			 																	  COMP_LIT_VALUE((yylhs.value.s)._elem, (yystack_[0].value.s)._u.s, ICS_LIT_REAL); (yylhs.value.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, yystack_[0].location));
			 																	  PARSE_CONTEXT.setCbExprModeReset(); }
#line 1925 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 79:
#line 460 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); CMPLELEMENTRY((yylhs.value.s), SyntaxElementLitInt, yystack_[0].location, yystack_[0].location);
																				  COMP_LIT_VALUE((yylhs.value.s)._elem, (yystack_[0].value.s)._u.s, ICS_LIT_INT); (yylhs.value.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, yystack_[0].location));
																				  PARSE_CONTEXT.setCbExprModeReset(); }
#line 1933 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 80:
#line 466 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementArray, yystack_[2].location, yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[1].value.s)); NOT_USED((yystack_[2].value.s));
		   																		  if ((yystack_[1].value.s)._u.exp->listCnt() || (yystack_[1].value.s)._u.exp->empty()) { COMP_CONSTRUCT((yylhs.value.s)._elem, ICS_CONSTRUCT_ARRAY, ((yystack_[1].value.s)._u.exp->listCnt() ?: 1)); }
		   																		  (yylhs.value.s).setExp((yystack_[1].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_ARR, NULL, false)); }
#line 1941 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 81:
#line 469 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_ERR((yystack_[1].value.s), yystack_[1].location); CMPLELEMENTRY((yylhs.value.s), SyntaxElementArray, yystack_[2].location, yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[1].value.s)); NOT_USED((yystack_[2].value.s));
																				  (yylhs.value.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, yystack_[2].location));
																				  yyerrok; }
#line 1949 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 474 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1955 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 477 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementTupel, yystack_[2].location, yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[1].value.s)); NOT_USED((yystack_[2].value.s));
		   																		  COMP_CONSTRUCT((yylhs.value.s)._elem, ICS_CONSTRUCT_TUPEL, ((yystack_[1].value.s)._u.exp->listCnt() ?: 1));
		   																		  (yylhs.value.s).setExp((yystack_[1].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_TUP, NULL, false)); }
#line 1963 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 480 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_ERR((yystack_[1].value.s), yystack_[1].location); CMPLELEMENTRY((yylhs.value.s), SyntaxElementTupel, yystack_[2].location, yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[1].value.s)); NOT_USED((yystack_[2].value.s));
																				  (yylhs.value.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, yystack_[2].location));
																				  yyerrok; }
#line 1971 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 485 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); PARSE_CONTEXT.setCbExprModeReset(); }
#line 1977 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 86:
#line 488 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); 
		   																		  if ((yystack_[0].value.s)._empty) { CMPLELEMENTRY_EMPTY((yylhs.value.s), yystack_[0].location); COMP_SET_SYNTAXELEM((yystack_[0].value.s)._u.u, (yylhs.value.s)._elem); (yystack_[0].value.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, yystack_[0].location, specialSymbolKnownVal, true)); }
		   																		  else { CMPLELEM_SET((yylhs.value.s), (yystack_[0].value.s)); };
		   																		  (yylhs.value.s).setExp((yystack_[0].value.s)._u.exp); }
#line 1986 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 87:
#line 492 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); 
																				  if ((yystack_[2].value.s)._empty) { CMPLELEMENTRY_EMPTY((yystack_[2].value.s), yystack_[2].location); COMP_SET_SYNTAXELEM((yystack_[2].value.s)._u.u, (yystack_[2].value.s)._elem); (yystack_[2].value.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, yystack_[2].location, specialSymbolKnownVal, true)); }
																				  CMPLELEM_CONCAT((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s));
																				  (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CAT, (yystack_[0].value.s)._u.exp, true)); }
#line 1995 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 498 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); COMP_LIT_BLANK((yylhs.value.s)._u.u); }
#line 2001 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 499 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); (yystack_[0].value.s)._u.exp->checkLNPError(&PARSE_CONTEXT); }
#line 2007 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 502 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementInterval, yystack_[2].location, yystack_[0].location); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); NOT_USED((yystack_[1].value.s));
			 																	  (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_SET, (yystack_[0].value.s)._u.exp, true));
																				  COMP_CONSTRUCT((yylhs.value.s)._elem, ICS_CONSTRUCT_IV_LB, 2); }
#line 2015 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 505 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementInterval, yystack_[1].location, yystack_[0].location); CMPLELEMENTRY_EMPTY((yystack_[0].value.s), yystack_[0].location); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s));
																				  (yylhs.value.s).setExp((yystack_[1].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_SET, NULL, false));
																				  COMP_CONSTRUCT((yylhs.value.s)._elem, ICS_CONSTRUCT_IV_LB, 1); }
#line 2023 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 508 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_EMPTY((yystack_[1].value.s), yystack_[1].location); CMPLELEMENTRY((yylhs.value.s), SyntaxElementInterval, yystack_[1].location, yystack_[0].location); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s));
																				  (yylhs.value.s).setExp((yystack_[0].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_SET, NULL, false));
																				  COMP_CONSTRUCT((yylhs.value.s)._elem, ICS_CONSTRUCT_IV_WOLB, 1); }
#line 2031 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 511 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementInterval, yystack_[0].location, yystack_[0].location);
																				  CMPLELEMENTRY_EMPTY((yystack_[0].value.s), yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[0].value.s));
																				  CMPLELEMENTRY_EMPTY((yystack_[0].value.s), yystack_[0].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[0].value.s));
																				  (yylhs.value.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, yystack_[0].location));
																				  COMP_CONSTRUCT((yylhs.value.s)._elem, ICS_CONSTRUCT_IV_WOLB, 0); }
#line 2041 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 518 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 2047 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 521 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementSet, yystack_[2].location, yystack_[0].location); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[1].value.s)); CMPLELEM_CHILD((yylhs.value.s), (yystack_[0].value.s));
		  																		  if (!(yystack_[1].value.s)._u.exp->oneElemArr()) PARSE_CONTEXT.outParseError(ERROR_LVL_NORMAL, "step for algorithmic set must be a single value", yystack_[1].location);
		  																		  (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_SET, (yystack_[0].value.s)._u.exp, true)); delete (yystack_[1].value.s)._u.exp;
																				  COMP_CONSTRUCT((yylhs.value.s)._elem, ICS_CONSTRUCT_SET, 3); }
#line 2056 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 527 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); }
#line 2062 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 528 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); }
#line 2068 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 535 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementUnaryOp, yystack_[1].location, yystack_[0].location, ((yystack_[1].value.s)._u.b ? "+" : "-")); CMPLELEM_CHILD((yylhs.value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[0].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, NULL, false));
		  																		  COMP_OPERATION((yylhs.value.s)._elem, ((yystack_[1].value.s)._u.b ? ICS_OPER_ADD : ICS_OPER_SUB), 1); }
#line 2075 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 537 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_EMPTY((yystack_[0].value.s), yystack_[0].location); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementUnaryOp, yystack_[0].location, yystack_[0].location, ((yystack_[0].value.s)._u.b ? "*" : "/")); CMPLELEM_CHILD((yylhs.value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, yystack_[0].location));
																				  COMP_OPERATION((yylhs.value.s)._elem, ((yystack_[0].value.s)._u.b ? ICS_OPER_MUL : ICS_OPER_DIV), 0); }
#line 2082 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 539 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementUnaryOp, yystack_[1].location, yystack_[0].location, ((yystack_[1].value.s)._u.b ? "*" : "/")); CMPLELEM_CHILD((yylhs.value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[0].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, NULL, false));
																				  COMP_OPERATION((yylhs.value.s)._elem, ((yystack_[1].value.s)._u.b ? ICS_OPER_MUL : ICS_OPER_DIV), 1); }
#line 2089 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 541 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementUnaryOp, yystack_[1].location, yystack_[0].location, (yystack_[0].value.s)._name); CMPLELEM_CHILD((yylhs.value.s), (yystack_[1].value.s)); (yylhs.value.s).setExp((yystack_[1].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, NULL, false));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_TRP, 1); }
#line 2096 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 543 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementUnaryOp, yystack_[1].location, yystack_[0].location, (yystack_[1].value.s)._name); CMPLELEM_CHILD((yylhs.value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[0].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_LOG, NULL, false));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_NOT, 1); }
#line 2103 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 547 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementBinaryOp, yystack_[2].location, yystack_[0].location, ((yystack_[1].value.s)._u.b ? "+" : "-")); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, (yystack_[0].value.s)._u.exp, true));
		  																		  COMP_OPERATION((yylhs.value.s)._elem, ((yystack_[1].value.s)._u.b ? ICS_OPER_ADD : ICS_OPER_SUB), 2); }
#line 2110 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 549 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementBinaryOp, yystack_[2].location, yystack_[0].location, ((yystack_[1].value.s)._u.b ? "*" : "/")); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ((yystack_[1].value.s)._u.b ? ICS_OPER_MUL : ICS_OPER_DIV), 2); }
#line 2117 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 105:
#line 551 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementBinaryOp, yystack_[2].location, yystack_[0].location, "^"); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_EXP, 2); }
#line 2124 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 106:
#line 553 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementBinaryOp, yystack_[2].location, yystack_[0].location, (yystack_[1].value.s)._name); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_LOG_AND, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_AND, 2); }
#line 2131 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 107:
#line 555 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementBinaryOp, yystack_[2].location, yystack_[0].location, (yystack_[1].value.s)._name); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_LOG, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_OR, 2); }
#line 2138 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 108:
#line 557 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementBinaryOp, yystack_[2].location, yystack_[0].location, (yystack_[1].value.s)._name); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_IRR, 2); }
#line 2145 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 109:
#line 559 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementBinaryOp, yystack_[2].location, yystack_[0].location, (yystack_[1].value.s)._name); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_OBJTO, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_OBJTO, 2); }
#line 2152 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 110:
#line 561 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementBinaryOp, yystack_[1].location, yystack_[0].location, "in"); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[1].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_IN, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_IN, 2); }
#line 2159 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 111:
#line 563 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementBinaryOp, yystack_[1].location, yystack_[0].location, "of"); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[1].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_IN, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_OF, 2); }
#line 2166 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 112:
#line 565 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_ALT((yylhs.value.s), SyntaxElementBinaryOp, yystack_[1].location, yystack_[0].location, "", "*"); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[1].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_MUL, 2); }
#line 2173 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 113:
#line 569 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); (yylhs.value.s)._u.b = true; PARSE_CONTEXT.setCbExprModeReset(); }
#line 2179 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 114:
#line 570 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); (yylhs.value.s)._u.b = false; PARSE_CONTEXT.setCbExprModeReset(); }
#line 2185 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 115:
#line 573 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); (yylhs.value.s)._u.b = true; PARSE_CONTEXT.setCbExprModeReset(); }
#line 2191 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 116:
#line 574 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); (yylhs.value.s)._u.b = false; PARSE_CONTEXT.setCbExprModeReset(); }
#line 2197 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 117:
#line 577 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); PARSE_CONTEXT.setCbExprModeReset(); }
#line 2203 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 118:
#line 580 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[1].value.s); NOT_USED((yystack_[0].value.s)); }
#line 2209 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 119:
#line 581 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[1].value.s); NOT_USED((yystack_[0].value.s)); /* $1 doesn't mean multiplication here, but is delivered so by flex, because "in" is a keyword operator */ }
#line 2215 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 120:
#line 584 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[1].value.s); NOT_USED((yystack_[0].value.s)); }
#line 2221 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 121:
#line 585 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[1].value.s); NOT_USED((yystack_[0].value.s)); /* $1 doesn't mean multiplication here, but is delivered so by flex, because "of" is a keyword operator */ }
#line 2227 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 122:
#line 588 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementCompareOp, yystack_[2].location, yystack_[0].location, (yystack_[1].value.s)._name); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP, (yystack_[0].value.s)._u.exp, true));
		   																		  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_EQ, 2); }
#line 2234 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 123:
#line 590 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementCompareOp, yystack_[2].location, yystack_[0].location, (yystack_[1].value.s)._name); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP2, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_EQ2, 2); }
#line 2241 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 124:
#line 592 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementCompareOp, yystack_[2].location, yystack_[0].location, (yystack_[1].value.s)._name); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_NE, 2); }
#line 2248 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 125:
#line 594 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementCompareOp, yystack_[2].location, yystack_[0].location, (yystack_[1].value.s)._name); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP2, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_NE2, 2); }
#line 2255 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 126:
#line 596 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementCompareOp, yystack_[2].location, yystack_[0].location, (yystack_[1].value.s)._name); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_LT, 2); }
#line 2262 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 127:
#line 598 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementCompareOp, yystack_[2].location, yystack_[0].location, (yystack_[1].value.s)._name); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_GT, 2); }
#line 2269 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 128:
#line 600 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementCompareOp, yystack_[2].location, yystack_[0].location, (yystack_[1].value.s)._name); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_LE, 2); }
#line 2276 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 129:
#line 602 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementCompareOp, yystack_[2].location, yystack_[0].location, (yystack_[1].value.s)._name); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_GE, 2); }
#line 2283 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 130:
#line 607 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementSubSymbolOp, yystack_[2].location, yystack_[0].location, "."); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[2].value.s), (yystack_[0].value.s)); NOT_USED((yystack_[1].value.s));
			 																	  (yylhs.value.s).setExp((yystack_[2].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_SUB, (yystack_[0].value.s)._u.exp, true)); }
#line 2290 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 131:
#line 611 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); }
#line 2296 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 132:
#line 612 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementIncDec, yystack_[1].location, yystack_[0].location, ((yystack_[1].value.s)._u.i > 0 ? "prefix inc" : "prefix dec")); CMPLELEM_CHILD((yylhs.value.s), (yystack_[0].value.s));
																				  (yylhs.value.s).setExp((yystack_[0].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_INC, NULL, false));
																				  COMP_INCDEC_FETCH((yylhs.value.s)._elem, true, (yystack_[1].value.s)._u.i); }
#line 2304 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 133:
#line 615 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[1].value.s); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementIncDec, yystack_[1].location, yystack_[0].location, ((yystack_[0].value.s)._u.i > 0 ? "postfix inc" : "postfix dec")); CMPLELEM_CHILD((yylhs.value.s), (yystack_[1].value.s));
																				  (yylhs.value.s).setExp((yystack_[1].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_INC, NULL, false));
																				  COMP_INCDEC_FETCH((yylhs.value.s)._elem, false, (yystack_[0].value.s)._u.i); }
#line 2312 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 134:
#line 620 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s) = (yystack_[0].value.s); CMPLELEMENTRY_SYM((yylhs.value.s), SyntaxElementSymbol, yystack_[0].location, yystack_[0].location, (yystack_[0].value.s)._u.exp->sym());
																				  COMP_FETCH_SYM((yylhs.value.s)._elem, (yystack_[0].value.s)._u.exp); (yylhs.value.s)._u.exp->setLvalueSyntaxElem((yylhs.value.s)._elem); }
#line 2319 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 135:
#line 625 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementFuncCall, yystack_[1].location, yystack_[0].location); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s)); /* auch als Set-Konstruktor der Art 1(1)(n-1) */
			 																	  (yylhs.value.s).setExp((yystack_[1].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CALL, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_FUNC, 2); }
#line 2327 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 136:
#line 628 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init();
																				  if (PARSE_CONTEXT.modpt()->compatLineNamePref() && (yystack_[1].value.s)._u.exp->sym() && (yystack_[1].value.s)._u.exp->sym()->notDefined()) {
																					// no function call, $1 is a line name prefix
																					COMP_LNP_COMPAT((yystack_[1].value.s)._elem, (yystack_[1].value.s)._u.exp);
																					delete (yystack_[1].value.s)._u.exp; (yylhs.value.s) = (yystack_[0].value.s); (yylhs.value.s)._u.exp->setHasLNP(yystack_[1].location);
																					CMPLELEMENTRY((yylhs.value.s), SyntaxElementLineNamePrefix, yystack_[1].location, yystack_[1].location); CMPLELEM_CHILD((yylhs.value.s), (yystack_[1].value.s)); CMPLELEM_NEXT((yylhs.value.s), (yystack_[0].value.s));
																				  } else {
																				  	CMPLELEMENTRY((yylhs.value.s), SyntaxElementFuncCall, yystack_[1].location, yystack_[0].location); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s));
																				  	(yylhs.value.s).setExp((yystack_[1].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CALL, (yystack_[0].value.s)._u.exp, true));
																					COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_FUNC, 2);
																				} }
#line 2343 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 137:
#line 641 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY((yylhs.value.s), SyntaxElementIndexation, yystack_[1].location, yystack_[0].location); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s));
																				  (yylhs.value.s).setExp((yystack_[1].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_IND, (yystack_[0].value.s)._u.exp, true));
																				  COMP_OPERATION((yylhs.value.s)._elem, ICS_OPER_INDEX, 2); }
#line 2351 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 138:
#line 646 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementError, yystack_[1].location, yystack_[0].location, "illegal expression"); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[1].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, (yystack_[0].value.s)._u.exp, true)); }
#line 2357 "_CMPL_Parser.cc" // lalr1.cc:859
    break;

  case 139:
#line 647 "CMPL_Parser.yy" // lalr1.cc:859
    { (yylhs.value.s).init(); CMPLELEMENTRY_TXT((yylhs.value.s), SyntaxElementError, yystack_[1].location, yystack_[0].location, "illegal expression"); CMPLELEM_CHILD2((yylhs.value.s), (yystack_[1].value.s), (yystack_[0].value.s)); (yylhs.value.s).setExp((yystack_[1].value.s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, (yystack_[0].value.s)._u.exp, true)); }
#line 2363 "_CMPL_Parser.cc" // lalr1.cc:859
    break;


#line 2367 "_CMPL_Parser.cc" // lalr1.cc:859
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
  CMPL_Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  CMPL_Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const signed char CMPL_Parser::yypact_ninf_ = -63;

  const signed char CMPL_Parser::yytable_ninf_ = -89;

  const short int
  CMPL_Parser::yypact_[] =
  {
     535,   -46,   -63,   -63,   -63,   -63,   -63,    16,   -63,   487,
     -63,   743,   -22,   -63,   -63,   -63,   -63,   -63,   -63,   -63,
     -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,
     -63,   -63,   -63,   -23,   -63,   -63,   -63,   -25,   811,   -63,
     577,     1,   728,   -63,   -32,     3,   -63,   784,   -63,   444,
     -63,   402,   -63,   416,   -63,   -63,   -63,   838,   416,   838,
     838,   838,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,
     -63,   -63,     8,   916,     4,   -63,    10,   -12,   619,   -40,
      -2,   -63,   -23,   838,   838,   838,   838,   838,   838,   838,
     838,   838,   838,   -63,   -63,   838,   -63,   838,   -35,   838,
     -63,    25,   -63,   416,   838,   838,   -63,   -63,   -63,   -63,
     -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,   -63,    76,
      -5,   916,    -3,     6,     7,     9,   117,   117,   117,   117,
     176,   176,   -63,   -63,   -63,   -63,    -2,   -63,   743,   -63,
      31,    27,   838,   -63,   -63,   942,   967,   691,   691,   691,
     691,   691,   691,   691,   691,    76,   106,   -63,    47,   -63,
      42,   -63,   -63,   -63,   -63,   117,     5,    76,   -63,   -63,
     838,   -63,   -63,   -63,   674,   -63,   -40,   -63,   889,   -63,
     -63,   -63,   -63,   838,   916
  };

  const unsigned char
  CMPL_Parser::yydefact_[] =
  {
       0,     0,    13,    14,    15,    10,    11,     0,     2,     0,
       5,     0,     8,    12,     6,    18,     1,     4,   113,   114,
     115,   116,    94,   117,    82,    85,    35,    76,    75,    77,
      79,    78,    72,     0,     7,    53,    16,     0,     0,    66,
       0,     0,    73,    54,    69,    20,    55,     0,    56,     0,
      57,     0,    58,    93,    59,    60,    61,     0,    99,     0,
       0,     0,    62,    63,    64,    65,    68,     9,    70,    17,
      25,    19,    23,    22,     0,    43,     0,    36,     0,    48,
      41,    67,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   118,   120,     0,   101,     0,     0,     0,
     136,   135,   137,    91,     0,     0,    71,   138,   139,    26,
      27,    28,    29,    30,    31,    32,    21,   119,   121,   112,
       0,    89,     0,    86,     0,     0,    92,    98,   100,   102,
     110,   111,    24,    34,    33,    38,    41,    50,     0,    39,
       0,    44,     0,    42,   109,   107,   106,   122,   123,   124,
     125,   126,   127,   128,   129,   108,   105,   134,     0,   130,
     131,    74,    97,    96,    95,    90,   103,   104,    81,    80,
      88,    84,    83,    37,    73,    40,    48,    47,    51,   132,
     133,    87,    45,     0,    52
  };

  const short int
  CMPL_Parser::yypgoto_[] =
  {
     -63,   -63,    -8,   -63,   -63,   -10,   -63,    67,   -63,   -63,
     -63,   -63,   -63,   -63,   -30,   -63,   -29,   -63,   -63,   -63,
      26,   -63,   -62,   -63,   -63,   -63,   -63,   -63,   -11,   -63,
     -18,    30,   -41,   -63,   100,   -63,    40,   -63,   -42,   -63,
     -63,   142,   -63,   -63,   -63,   -63,   202,   244,   -63,   -63,
     -63,   -63,   -63,   -63,   -28,   -63,   -63,   -63
  };

  const short int
  CMPL_Parser::yydefgoto_[] =
  {
      -1,     7,     8,     9,    10,    11,    12,    13,    14,    37,
      38,    71,    72,   116,    39,    40,    76,   136,    77,    78,
      79,    80,   140,   141,   142,   139,   177,    41,   121,    43,
      44,    45,    46,    47,    48,    49,    50,    51,   122,   123,
      52,    53,    54,   164,    55,    56,    57,    58,    59,    60,
      61,    62,    63,   159,   160,    64,    65,    66
  };

  const short int
  CMPL_Parser::yytable_[] =
  {
      42,    17,    67,   108,    27,    28,    29,   109,   157,   125,
      32,    81,   100,    15,   -46,    68,    16,     2,   158,    32,
     -46,   106,     3,     4,     5,     6,   107,    73,    20,    21,
      95,    96,    97,    22,    69,    26,   119,    24,    25,    26,
      98,    25,   126,   100,   135,    75,   127,   128,   129,   130,
     131,   110,   111,   112,   113,   114,   168,   115,   169,   133,
     163,    27,    28,    29,   144,   134,   170,    32,   138,   171,
     137,   172,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   102,   162,   155,   175,   156,   176,    42,   100,
     157,   100,   165,   166,   167,   180,   100,   100,   100,   100,
     100,   100,    96,    97,    22,    70,   143,   173,    24,    25,
      26,    98,   132,   102,   182,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   174,   181,   161,
     179,   178,     0,    97,    22,   100,   100,   100,    24,    25,
      26,    98,   101,     0,   100,     0,     0,     0,   100,    24,
      25,    26,    98,     0,   100,     0,     0,     0,     0,   102,
       0,   102,     0,     0,     0,     0,   102,   102,   102,   102,
     102,   102,   184,   101,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   103,   102,   102,   102,   102,   102,
     102,   102,   102,   102,   102,   102,   102,    18,    19,    20,
      21,    95,    96,    97,    22,   102,   102,   102,    24,    25,
      26,    98,     0,     0,   102,   103,     0,     0,   102,   101,
       0,   101,     0,     0,   102,     0,   101,   101,   101,   101,
     101,   101,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   104,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,     0,     0,     0,
       0,   103,     0,   103,     0,   101,   101,   101,   103,   103,
     103,   103,   103,   103,   101,   104,     0,     0,   101,     0,
       0,     0,     0,     0,   101,     0,   105,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,     0,
       0,     0,     0,     0,     0,     0,     0,   103,   103,   103,
       0,     0,     0,     0,     0,     0,   103,   105,     0,     0,
     103,   104,     0,   104,     0,     0,   103,     0,   104,   104,
     104,   104,   104,   104,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   104,   104,   104,
     104,   104,   104,   104,   104,   104,   104,   104,   104,     0,
       0,     0,     0,   105,     0,   105,     0,   104,   104,   104,
     105,   105,   105,   105,   105,   105,   104,     0,     0,     0,
     104,     0,     0,     0,     0,     0,   104,     0,     0,   105,
     105,   105,   105,   105,   105,   105,   105,   105,   105,   105,
     105,     0,     0,   124,     0,     0,     0,     0,     0,   105,
     105,   105,     0,     0,     0,     0,     0,     0,   105,     0,
       0,     0,   105,    18,    19,    20,    21,     0,   105,     0,
      22,     0,     0,    23,    24,    25,    26,     0,    27,    28,
      29,     0,    30,    31,    32,   120,     0,    23,    24,    25,
      26,     0,    27,    28,    29,    33,    30,    31,    32,    35,
       0,     0,   -88,     0,   -88,    18,    19,    20,    21,    33,
       0,     0,    22,    35,     0,    23,    24,    25,    26,     0,
      27,    28,    29,     0,    30,    31,    32,    -3,     1,     0,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,    35,     0,     0,   -88,   -88,     0,     0,    -8,    -8,
      -8,    -8,     0,     0,     0,    -8,     0,     0,    -8,    -8,
      -8,    -8,     0,    -8,    -8,    -8,     2,    -8,    -8,    -8,
       0,     3,     4,     5,     6,    -3,     1,     0,     0,     0,
      -8,    -8,    -3,    -3,    -8,     0,    -8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    -8,    -8,    -8,    -8,
       0,     0,     0,    -8,     0,     0,    -8,    -8,    -8,    -8,
       0,    -8,    -8,    -8,     2,    -8,    -8,    -8,    74,     3,
       4,     5,     6,     0,     0,     0,     0,     0,    -8,    -8,
       0,     0,    -8,     0,    -8,     0,     0,     0,   -41,   -41,
     -41,   -41,     0,     0,     0,   -41,     0,     0,   -41,   -41,
     -41,   -41,     0,   -41,   -41,   -41,     0,   -41,   -41,   -41,
       1,     0,     0,     0,    75,     0,     0,     0,     0,     0,
     -41,   -41,     0,     0,   -41,     0,     0,   -41,     0,     0,
      -8,    -8,    -8,    -8,     0,     0,     0,    -8,     0,     0,
      -8,    -8,    -8,    -8,     0,    -8,    -8,    -8,     2,    -8,
      -8,    -8,     0,     3,     4,     5,     6,     0,     0,     0,
       0,     0,    -8,    -8,    -3,    -3,    -8,    82,    -8,     0,
       0,     0,     0,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    18,    19,    20,    21,    95,
      96,    97,    22,     0,     0,     0,    24,    25,    26,    98,
      93,    94,    18,    19,    20,    21,    95,    96,    97,    22,
       0,     0,     0,    24,    25,    26,    98,     0,     0,   -49,
     -49,    82,     0,     0,    99,     0,     0,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    18,
      19,    20,    21,    95,    96,    97,    22,     0,     0,     0,
      24,    25,    26,    98,    18,    19,    20,    21,     0,     0,
       0,    22,     0,     0,    23,    24,    25,    26,     0,    27,
      28,    29,     0,    30,    31,    32,     0,     0,    99,     0,
       0,     0,     0,     0,     0,     0,    33,    34,     0,     0,
      35,     0,    36,   117,   118,    18,    19,    20,    21,     0,
       0,     0,    22,     0,     0,    23,    24,    25,    26,     0,
      27,    28,    29,     0,    30,    31,    32,     0,     0,     0,
       0,     0,    18,    19,    20,    21,     0,    33,     0,    22,
       0,    35,    23,    24,    25,    26,     0,    27,    28,    29,
       0,    30,    31,    32,     0,     3,     4,     0,     0,    18,
      19,    20,    21,     0,    33,     0,    22,     0,    35,    23,
      24,    25,    26,     0,    27,    28,    29,     0,    30,    31,
      32,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    33,    82,   183,     0,    35,     0,     0,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      18,    19,    20,    21,    95,    96,    97,    22,     0,    82,
       0,    24,    25,    26,    98,    83,    84,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    18,    19,    20,
      21,    95,    96,    97,    22,     0,     0,     0,    24,    25,
      26,    98,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    18,    19,    20,    21,    95,    96,    97,
      22,     0,     0,     0,    24,    25,    26,    98,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,    18,    19,
      20,    21,    95,    96,    97,    22,     0,     0,     0,    24,
      25,    26,    98
  };

  const short int
  CMPL_Parser::yycheck_[] =
  {
      11,     9,    12,    44,    36,    37,    38,     4,    43,    51,
      42,    41,    42,    59,    54,    33,     0,    39,    53,    42,
      60,    53,    44,    45,    46,    47,    44,    38,    23,    24,
      25,    26,    27,    28,    59,    34,    47,    32,    33,    34,
      35,    33,    53,    73,    56,    47,    57,    58,    59,    60,
      61,    48,    49,    50,    51,    52,    61,    54,    61,    55,
     101,    36,    37,    38,    82,    55,    60,    42,    78,    62,
      78,    62,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    42,   101,    95,    54,    97,    60,    99,   119,
      43,   121,   103,   104,   105,    53,   126,   127,   128,   129,
     130,   131,    26,    27,    28,    38,    80,   136,    32,    33,
      34,    35,    72,    73,   176,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   138,   170,    99,
     158,   142,    -1,    27,    28,   165,   166,   167,    32,    33,
      34,    35,    42,    -1,   174,    -1,    -1,    -1,   178,    32,
      33,    34,    35,    -1,   184,    -1,    -1,    -1,    -1,   119,
      -1,   121,    -1,    -1,    -1,    -1,   126,   127,   128,   129,
     130,   131,   183,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,    21,    22,    23,
      24,    25,    26,    27,    28,   165,   166,   167,    32,    33,
      34,    35,    -1,    -1,   174,    73,    -1,    -1,   178,   119,
      -1,   121,    -1,    -1,   184,    -1,   126,   127,   128,   129,
     130,   131,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    42,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,    -1,    -1,    -1,
      -1,   119,    -1,   121,    -1,   165,   166,   167,   126,   127,
     128,   129,   130,   131,   174,    73,    -1,    -1,   178,    -1,
      -1,    -1,    -1,    -1,   184,    -1,    42,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   165,   166,   167,
      -1,    -1,    -1,    -1,    -1,    -1,   174,    73,    -1,    -1,
     178,   119,    -1,   121,    -1,    -1,   184,    -1,   126,   127,
     128,   129,   130,   131,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   145,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,    -1,
      -1,    -1,    -1,   119,    -1,   121,    -1,   165,   166,   167,
     126,   127,   128,   129,   130,   131,   174,    -1,    -1,    -1,
     178,    -1,    -1,    -1,    -1,    -1,   184,    -1,    -1,   145,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,   165,
     166,   167,    -1,    -1,    -1,    -1,    -1,    -1,   174,    -1,
      -1,    -1,   178,    21,    22,    23,    24,    -1,   184,    -1,
      28,    -1,    -1,    31,    32,    33,    34,    -1,    36,    37,
      38,    -1,    40,    41,    42,     1,    -1,    31,    32,    33,
      34,    -1,    36,    37,    38,    53,    40,    41,    42,    57,
      -1,    -1,    60,    -1,    62,    21,    22,    23,    24,    53,
      -1,    -1,    28,    57,    -1,    31,    32,    33,    34,    -1,
      36,    37,    38,    -1,    40,    41,    42,     0,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    57,    -1,    -1,    60,    61,    -1,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    28,    -1,    -1,    31,    32,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    45,    46,    47,     0,     1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    28,    -1,    -1,    31,    32,    33,    34,
      -1,    36,    37,    38,    39,    40,    41,    42,     1,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    53,    54,
      -1,    -1,    57,    -1,    59,    -1,    -1,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    28,    -1,    -1,    31,    32,
      33,    34,    -1,    36,    37,    38,    -1,    40,    41,    42,
       1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      53,    54,    -1,    -1,    57,    -1,    -1,    60,    -1,    -1,
      21,    22,    23,    24,    -1,    -1,    -1,    28,    -1,    -1,
      31,    32,    33,    34,    -1,    36,    37,    38,    39,    40,
      41,    42,    -1,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,     3,    59,    -1,
      -1,    -1,    -1,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    -1,    -1,    -1,    32,    33,    34,    35,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      -1,    -1,    -1,    32,    33,    34,    35,    -1,    -1,    55,
      56,     3,    -1,    -1,    60,    -1,    -1,     9,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    -1,    -1,    -1,
      32,    33,    34,    35,    21,    22,    23,    24,    -1,    -1,
      -1,    28,    -1,    -1,    31,    32,    33,    34,    -1,    36,
      37,    38,    -1,    40,    41,    42,    -1,    -1,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    -1,    -1,
      57,    -1,    59,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    28,    -1,    -1,    31,    32,    33,    34,    -1,
      36,    37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    21,    22,    23,    24,    -1,    53,    -1,    28,
      -1,    57,    31,    32,    33,    34,    -1,    36,    37,    38,
      -1,    40,    41,    42,    -1,    44,    45,    -1,    -1,    21,
      22,    23,    24,    -1,    53,    -1,    28,    -1,    57,    31,
      32,    33,    34,    -1,    36,    37,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,     3,     4,    -1,    57,    -1,    -1,     9,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    -1,     3,
      -1,    32,    33,    34,    35,     9,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    -1,    -1,    -1,    32,    33,
      34,    35,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    -1,    -1,    -1,    32,    33,    34,    35,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    -1,    -1,    32,
      33,    34,    35
  };

  const unsigned char
  CMPL_Parser::yystos_[] =
  {
       0,     1,    39,    44,    45,    46,    47,    64,    65,    66,
      67,    68,    69,    70,    71,    59,     0,    65,    21,    22,
      23,    24,    28,    31,    32,    33,    34,    36,    37,    38,
      40,    41,    42,    53,    54,    57,    59,    72,    73,    77,
      78,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   103,   104,   105,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   118,   119,   120,    68,    93,    59,
      70,    74,    75,    91,     1,    47,    79,    81,    82,    83,
      84,    77,     3,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    25,    26,    27,    35,    60,
      77,    97,    99,   104,   109,   110,    53,    93,    95,     4,
      48,    49,    50,    51,    52,    54,    76,    19,    20,    91,
       1,    91,   101,   102,     1,   101,    91,    91,    91,    91,
      91,    91,    99,    55,    55,    56,    80,    65,    68,    88,
      85,    86,    87,    83,    93,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    43,    53,   116,
     117,    94,    93,    95,   106,    91,    91,    91,    61,    61,
      60,    62,    62,    79,    91,    54,    60,    89,    91,   117,
      53,   101,    85,     4,    91
  };

  const unsigned char
  CMPL_Parser::yyr1_[] =
  {
       0,    63,    64,    65,    65,    66,    66,    67,    68,    68,
      69,    69,    69,    69,    70,    70,    71,    71,    71,    72,
      72,    73,    74,    74,    74,    75,    76,    76,    76,    76,
      76,    76,    76,    77,    77,    78,    79,    79,    80,    81,
      82,    83,    83,    84,    85,    85,    86,    86,    87,    88,
      88,    89,    89,    90,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    92,
      92,    92,    93,    94,    94,    95,    95,    95,    96,    96,
      97,    97,    98,    99,    99,   100,   101,   101,   102,   102,
     103,   103,   103,   103,   104,   105,   106,   106,   107,   107,
     107,   107,   107,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   109,   109,   110,   110,   111,   112,   112,
     113,   113,   114,   114,   114,   114,   114,   114,   114,   114,
     115,   116,   116,   116,   117,   118,   118,   119,   120,   120
  };

  const unsigned char
  CMPL_Parser::yyr2_[] =
  {
       0,     2,     1,     0,     2,     1,     1,     2,     0,     2,
       1,     1,     1,     1,     1,     1,     2,     3,     2,     2,
       1,     2,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     1,     3,     1,     2,
       3,     0,     2,     1,     1,     3,     0,     2,     0,     2,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       2,     2,     1,     1,     3,     1,     1,     1,     1,     1,
       3,     3,     1,     3,     3,     1,     1,     3,     0,     1,
       3,     2,     2,     1,     1,     3,     1,     1,     2,     1,
       2,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     1,     1,     1,     1,     1,     2,     2,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     2,     2,     1,     2,     2,     2,     2,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const CMPL_Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"operator `->`\"",
  "\"assign operator `:=`\"", "ASSIGN_ADD", "ASSIGN_SUB", "ASSIGN_MUL",
  "ASSIGN_DIV", "\"operator `||`\"", "\"operator `&&`\"",
  "\"operator `=`\"", "\"operator `==`\"", "\"operator `<>`\"",
  "\"operator `!=`\"", "\"operator `<`\"", "\"operator `>`\"",
  "\"operator `<=`\"", "\"operator `>=`\"", "\"operator `in`\"",
  "\"operator `of`\"", "'+'", "'-'", "'*'", "'/'", "\"operator `*>`\"",
  "\"transpose operator `T`\"", "'^'", "\"operator `..`\"", "NUMBER_SIGN",
  "INDEX_SIGN", "\"operator `!`\"", "'('", "'['", "\"`{`\"",
  "\"subsymbol operator `.`\"", "\"int literal\"", "\"double literal\"",
  "\"string literal\"", "\"linename prefix\"", "\"int literal factor\"",
  "\"double literal factor\"", "\"symbol\"", "\"subsymbol\"",
  "\"object type symbol\"", "\"data type symbol\"",
  "\"assign modificator\"", "\"order modificator\"",
  "\"assign operator `::=`\"", "\"assign operator `+=`\"",
  "\"assign operator `-=`\"", "\"assign operator `*=`\"",
  "\"assign operator `/=`\"", "\"increment/decrement operator\"",
  "\"`:`\"", "\"`}`\"", "\"`|`\"", "\"`&`\"", "\"`@`\"", "\"`;`\"", "','",
  "')'", "']'", "$accept", "cmpl", "cmplParts", "cmplPart", "directive",
  "directiveParts", "directivePart", "objDataType", "statement",
  "statementExpr", "assignLhsOp", "assignRhs", "objDataTypeRhs",
  "assignOp", "codeblock", "blockStart", "blockParts", "blockAltStart",
  "blockPart", "blockPartStart", "blockModifiers", "blockModifier",
  "blockHeaders", "blockHeader", "blockHeaderStart", "blockBody",
  "expressionWithCodeblockSymbolDef", "refcodeblock", "expression",
  "symbolIncDec", "symbol", "expressionList", "literal", "literalMult",
  "arrayExpr", "arrayStart", "tupleExpr", "tupleStart", "listParts",
  "listPart", "intervalExpr", "intervalOp", "setExpr", "setExprEnd",
  "unaryOp", "binaryOp", "numOpSignAdd", "numOpSignMult", "logOpSignNot",
  "inOpPre", "ofOpPre", "compareOp", "subsymbolOp", "subsymbolIncDec",
  "subsymbol", "functionCall", "indexation", "errorExpression", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  CMPL_Parser::yyrline_[] =
  {
       0,   237,   237,   240,   241,   244,   245,   248,   251,   252,
     255,   256,   257,   259,   263,   264,   272,   276,   279,   283,
     290,   305,   310,   311,   312,   316,   319,   320,   321,   322,
     323,   324,   325,   332,   336,   343,   347,   348,   351,   354,
     357,   360,   361,   364,   367,   371,   377,   378,   381,   384,
     392,   395,   396,   402,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   419,   420,   421,   425,   429,
     430,   434,   440,   445,   446,   449,   451,   453,   457,   460,
     466,   469,   474,   477,   480,   485,   488,   492,   498,   499,
     502,   505,   508,   511,   518,   521,   527,   528,   535,   537,
     539,   541,   543,   547,   549,   551,   553,   555,   557,   559,
     561,   563,   565,   569,   570,   573,   574,   577,   580,   581,
     584,   585,   588,   590,   592,   594,   596,   598,   600,   602,
     607,   611,   612,   615,   620,   625,   628,   641,   646,   647
  };

  // Print the state stack on the debug stream.
  void
  CMPL_Parser::yystack_print_ ()
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
  CMPL_Parser::yy_reduce_print_ (int yyrule)
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
  CMPL_Parser::token_number_type
  CMPL_Parser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      32,    61,    23,    21,    60,    22,     2,    24,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    33,     2,    62,    27,     2,     2,     2,     2,     2,
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
      15,    16,    17,    18,    19,    20,    25,    26,    28,    29,
      30,    31,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59
    };
    const unsigned int user_token_number_max_ = 307;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }


} // cmpl
#line 3113 "_CMPL_Parser.cc" // lalr1.cc:1167
#line 650 "CMPL_Parser.yy" // lalr1.cc:1168


void cmpl::CMPL_Parser::error(const cmpl::CMPL_Parser::location_type& l, const std::string& m)
{
	PARSE_CONTEXT.outParseError(ERROR_LVL_NORMAL, m, l, true);
}


