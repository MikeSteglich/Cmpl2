/* A Bison parser, made by GNU Bison 2.7.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

// Take the name prefix into account.
#define yylex   cmpllex

/* First part of user declarations.  */
/* Line 279 of lalr1.cc  */
#line 36 "CMPL_Parser.yy"

namespace cmpl
{
    class CompilerContext;
	class SyntaxElement;
}
/* Line 279 of lalr1.cc  */
#line 53 "CMPL_Parser.yy"

#include "../../CommonData/SyntaxElements.hh"
#include "CompilerUtil.hh"
#include "CompilerContext.hh"

#define CMPLCOMP_FOR_SCANNER    cmplcomp._scanner

// in the skeleton the definition of yyerrok is missing, thats why it is defined here
#define yyerrok     (yyerrstatus_ = 0)

/* Line 279 of lalr1.cc  */
#line 59 "_CMPL_Parser.cc"


#include "_CMPL_Parser.hh"

/* User implementation prologue.  */
/* Line 285 of lalr1.cc  */
#line 110 "CMPL_Parser.yy"

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

/* Line 285 of lalr1.cc  */
#line 112 "_CMPL_Parser.cc"


# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
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


/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location) YYUSE(Type)
# define YY_REDUCE_PRINT(Rule)        static_cast<void>(0)
# define YY_STACK_PRINT()             static_cast<void>(0)

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace cmpl {
/* Line 353 of lalr1.cc  */
#line 207 "_CMPL_Parser.cc"

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
              /* Fall through.  */
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
  {
  }

  CMPL_Parser::~CMPL_Parser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  CMPL_Parser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    std::ostream& yyo = debug_stream ();
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  CMPL_Parser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  CMPL_Parser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
        case 1: /* error */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 314 "_CMPL_Parser.cc"
        break;
      case 3: /* "operator `->`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 321 "_CMPL_Parser.cc"
        break;
      case 8: /* "assign operator `:=`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 328 "_CMPL_Parser.cc"
        break;
      case 9: /* "operator `||`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 335 "_CMPL_Parser.cc"
        break;
      case 10: /* "operator `&&`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 342 "_CMPL_Parser.cc"
        break;
      case 11: /* "operator `>=`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 349 "_CMPL_Parser.cc"
        break;
      case 12: /* "operator `<=`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 356 "_CMPL_Parser.cc"
        break;
      case 13: /* "operator `>`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 363 "_CMPL_Parser.cc"
        break;
      case 14: /* "operator `<`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 370 "_CMPL_Parser.cc"
        break;
      case 15: /* "operator `!=`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 377 "_CMPL_Parser.cc"
        break;
      case 16: /* "operator `<>`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 384 "_CMPL_Parser.cc"
        break;
      case 17: /* "operator `==`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 391 "_CMPL_Parser.cc"
        break;
      case 18: /* "operator `=`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 398 "_CMPL_Parser.cc"
        break;
      case 19: /* "operator `of`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 405 "_CMPL_Parser.cc"
        break;
      case 20: /* "operator `in`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 412 "_CMPL_Parser.cc"
        break;
      case 25: /* "operator `*>`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 419 "_CMPL_Parser.cc"
        break;
      case 26: /* "transpose operator `T`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 426 "_CMPL_Parser.cc"
        break;
      case 28: /* "operator `..`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 433 "_CMPL_Parser.cc"
        break;
      case 29: /* "operator `!`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 440 "_CMPL_Parser.cc"
        break;
      case 34: /* "`{`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 447 "_CMPL_Parser.cc"
        break;
      case 35: /* "subsymbol operator `.`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 454 "_CMPL_Parser.cc"
        break;
      case 36: /* "int literal" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 461 "_CMPL_Parser.cc"
        break;
      case 37: /* "double literal" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 468 "_CMPL_Parser.cc"
        break;
      case 38: /* "string literal" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 475 "_CMPL_Parser.cc"
        break;
      case 39: /* "linename prefix" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 482 "_CMPL_Parser.cc"
        break;
      case 40: /* "int literal factor" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 489 "_CMPL_Parser.cc"
        break;
      case 41: /* "double literal factor" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 496 "_CMPL_Parser.cc"
        break;
      case 42: /* "symbol" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 503 "_CMPL_Parser.cc"
        break;
      case 43: /* "subsymbol" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 510 "_CMPL_Parser.cc"
        break;
      case 44: /* "object type symbol" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 517 "_CMPL_Parser.cc"
        break;
      case 45: /* "data type symbol" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 524 "_CMPL_Parser.cc"
        break;
      case 46: /* "assign modificator" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 531 "_CMPL_Parser.cc"
        break;
      case 47: /* "order modificator" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 538 "_CMPL_Parser.cc"
        break;
      case 48: /* "assign operator `::=`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 545 "_CMPL_Parser.cc"
        break;
      case 49: /* "assign operator `+=`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 552 "_CMPL_Parser.cc"
        break;
      case 50: /* "assign operator `-=`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 559 "_CMPL_Parser.cc"
        break;
      case 51: /* "assign operator `*=`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 566 "_CMPL_Parser.cc"
        break;
      case 52: /* "assign operator `/=`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 573 "_CMPL_Parser.cc"
        break;
      case 53: /* "increment/decrement operator" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 580 "_CMPL_Parser.cc"
        break;
      case 54: /* "`:`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 587 "_CMPL_Parser.cc"
        break;
      case 55: /* "`}`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 594 "_CMPL_Parser.cc"
        break;
      case 56: /* "`|`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 601 "_CMPL_Parser.cc"
        break;
      case 57: /* "`&`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 608 "_CMPL_Parser.cc"
        break;
      case 58: /* "`@`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 615 "_CMPL_Parser.cc"
        break;
      case 59: /* "`;`" */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 622 "_CMPL_Parser.cc"
        break;
      case 64: /* cmpl */
/* Line 455 of lalr1.cc  */
#line 228 "CMPL_Parser.yy"
        { };
/* Line 455 of lalr1.cc  */
#line 629 "_CMPL_Parser.cc"
        break;
      case 65: /* cmplParts */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 636 "_CMPL_Parser.cc"
        break;
      case 66: /* cmplPart */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 643 "_CMPL_Parser.cc"
        break;
      case 67: /* directive */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 650 "_CMPL_Parser.cc"
        break;
      case 68: /* directiveParts */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 657 "_CMPL_Parser.cc"
        break;
      case 69: /* directivePart */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 664 "_CMPL_Parser.cc"
        break;
      case 70: /* objDataType */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 671 "_CMPL_Parser.cc"
        break;
      case 71: /* statement */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 678 "_CMPL_Parser.cc"
        break;
      case 72: /* statementExpr */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 685 "_CMPL_Parser.cc"
        break;
      case 73: /* assignLhsOp */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 692 "_CMPL_Parser.cc"
        break;
      case 74: /* assignRhs */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 699 "_CMPL_Parser.cc"
        break;
      case 75: /* objDataTypeRhs */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 706 "_CMPL_Parser.cc"
        break;
      case 76: /* assignOp */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 713 "_CMPL_Parser.cc"
        break;
      case 77: /* codeblock */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 720 "_CMPL_Parser.cc"
        break;
      case 78: /* blockStart */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 727 "_CMPL_Parser.cc"
        break;
      case 79: /* blockParts */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 734 "_CMPL_Parser.cc"
        break;
      case 80: /* blockAltStart */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 741 "_CMPL_Parser.cc"
        break;
      case 81: /* blockPart */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 748 "_CMPL_Parser.cc"
        break;
      case 82: /* blockPartStart */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 755 "_CMPL_Parser.cc"
        break;
      case 83: /* blockModifiers */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 762 "_CMPL_Parser.cc"
        break;
      case 84: /* blockModifier */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 769 "_CMPL_Parser.cc"
        break;
      case 85: /* blockHeaders */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 776 "_CMPL_Parser.cc"
        break;
      case 86: /* blockHeader */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 783 "_CMPL_Parser.cc"
        break;
      case 87: /* blockHeaderStart */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 790 "_CMPL_Parser.cc"
        break;
      case 88: /* blockBody */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 797 "_CMPL_Parser.cc"
        break;
      case 89: /* expressionWithCodeblockSymbolDef */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 804 "_CMPL_Parser.cc"
        break;
      case 90: /* refcodeblock */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 811 "_CMPL_Parser.cc"
        break;
      case 91: /* expression */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 818 "_CMPL_Parser.cc"
        break;
      case 92: /* symbolIncDec */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 825 "_CMPL_Parser.cc"
        break;
      case 93: /* symbol */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 832 "_CMPL_Parser.cc"
        break;
      case 94: /* expressionList */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 839 "_CMPL_Parser.cc"
        break;
      case 95: /* literal */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 846 "_CMPL_Parser.cc"
        break;
      case 96: /* literalMult */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 853 "_CMPL_Parser.cc"
        break;
      case 97: /* arrayExpr */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 860 "_CMPL_Parser.cc"
        break;
      case 98: /* arrayStart */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 867 "_CMPL_Parser.cc"
        break;
      case 99: /* tupleExpr */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 874 "_CMPL_Parser.cc"
        break;
      case 100: /* tupleStart */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 881 "_CMPL_Parser.cc"
        break;
      case 101: /* listParts */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 888 "_CMPL_Parser.cc"
        break;
      case 102: /* listPart */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 895 "_CMPL_Parser.cc"
        break;
      case 103: /* intervalExpr */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 902 "_CMPL_Parser.cc"
        break;
      case 104: /* intervalOp */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 909 "_CMPL_Parser.cc"
        break;
      case 105: /* setExpr */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 916 "_CMPL_Parser.cc"
        break;
      case 106: /* setExprEnd */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 923 "_CMPL_Parser.cc"
        break;
      case 107: /* unaryOp */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 930 "_CMPL_Parser.cc"
        break;
      case 108: /* binaryOp */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 937 "_CMPL_Parser.cc"
        break;
      case 109: /* numOpSignAdd */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 944 "_CMPL_Parser.cc"
        break;
      case 110: /* numOpSignMult */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 951 "_CMPL_Parser.cc"
        break;
      case 111: /* logOpSignNot */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 958 "_CMPL_Parser.cc"
        break;
      case 112: /* inOpPre */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 965 "_CMPL_Parser.cc"
        break;
      case 113: /* ofOpPre */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 972 "_CMPL_Parser.cc"
        break;
      case 114: /* compareOp */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 979 "_CMPL_Parser.cc"
        break;
      case 115: /* subsymbolOp */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 986 "_CMPL_Parser.cc"
        break;
      case 116: /* subsymbolIncDec */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 993 "_CMPL_Parser.cc"
        break;
      case 117: /* subsymbol */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 1000 "_CMPL_Parser.cc"
        break;
      case 118: /* functionCall */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 1007 "_CMPL_Parser.cc"
        break;
      case 119: /* indexation */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 1014 "_CMPL_Parser.cc"
        break;
      case 120: /* errorExpression */
/* Line 455 of lalr1.cc  */
#line 229 "CMPL_Parser.yy"
        { if (!((*yyvaluep).s)._empty) { PARSE_CONTEXT.insertErrElem(((*yyvaluep).s)._elem); }  /*if ($$._tp == semanticValueExpr) { delete $$._u.exp; }*/ };
/* Line 455 of lalr1.cc  */
#line 1021 "_CMPL_Parser.cc"
        break;

	default:
	  break;
      }
  }

  void
  CMPL_Parser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
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
#endif

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
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    // State.
    int yyn;
    int yylen = 0;
    int yystate = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    static semantic_type yyval_default;
    semantic_type yylval = yyval_default;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
        YYCDEBUG << "Reading a token: ";
        yychar = yylex (&yylval, &yylloc, CMPLCOMP_FOR_SCANNER, cmplcomp);
      }

    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yy_table_value_is_error_ (yyn))
	  goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    // Compute the default @$.
    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }

    // Perform the reduction.
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
          case 2:
/* Line 670 of lalr1.cc  */
#line 237 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PROTO_PC_OUTL("Parse cmpl End"); SET_CMPLELEM((yysemantic_stack_[(1) - (1)].s), (yylocation_stack_[(1) - (1)])); COMP_END((yysemantic_stack_[(1) - (1)].s)._elem); }
    break;

  case 3:
/* Line 670 of lalr1.cc  */
#line 240 "CMPL_Parser.yy"
    { (yyval.s).init(); }
    break;

  case 4:
/* Line 670 of lalr1.cc  */
#line 241 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEM_CONCAT((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s)); }
    break;

  case 5:
/* Line 670 of lalr1.cc  */
#line 244 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeStatementStart(); PARSE_CONTEXT.setDirectiveFromCurrent(&(yylocation_stack_[(1) - (1)])); }
    break;

  case 6:
/* Line 670 of lalr1.cc  */
#line 245 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeStatementStart(); PARSE_CONTEXT.clearModificators(); }
    break;

  case 7:
/* Line 670 of lalr1.cc  */
#line 248 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementDirective, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (1)].s)); NOT_USED((yysemantic_stack_[(2) - (2)].s)); }
    break;

  case 8:
/* Line 670 of lalr1.cc  */
#line 251 "CMPL_Parser.yy"
    { (yyval.s).init(); }
    break;

  case 9:
/* Line 670 of lalr1.cc  */
#line 252 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEM_CONCAT((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s)); }
    break;

  case 10:
/* Line 670 of lalr1.cc  */
#line 255 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementModificator, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]), (yysemantic_stack_[(1) - (1)].s)._name); PARSE_CONTEXT.setModificator(&(yylocation_stack_[(1) - (1)]), (ModificatorKey) (yysemantic_stack_[(1) - (1)].s)._u.i); }
    break;

  case 11:
/* Line 670 of lalr1.cc  */
#line 256 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementModificator, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]), (yysemantic_stack_[(1) - (1)].s)._name); PARSE_CONTEXT.setModificator(&(yylocation_stack_[(1) - (1)]), (ModificatorKey) (yysemantic_stack_[(1) - (1)].s)._u.i); }
    break;

  case 12:
/* Line 670 of lalr1.cc  */
#line 257 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); CMPLELEM_SET((yyval.s), (yysemantic_stack_[(1) - (1)].s)); PARSE_CONTEXT.setModificator(&(yylocation_stack_[(1) - (1)]), (yysemantic_stack_[(1) - (1)].s)._u.exp->sym(), (SPECIALSYMBOL_IS_OBJTYPE((yysemantic_stack_[(1) - (1)].s)._u.exp->sym()->special())));
																				  delete (yysemantic_stack_[(1) - (1)].s)._u.exp; }
    break;

  case 13:
/* Line 670 of lalr1.cc  */
#line 259 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementLineNamePrefix, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
																				  PARSE_CONTEXT.setLineNamePref((yyval.s)._elem, &(yylocation_stack_[(1) - (1)]), (yysemantic_stack_[(1) - (1)].s)._u.s); }
    break;

  case 14:
/* Line 670 of lalr1.cc  */
#line 263 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); CMPLELEMENTRY_SYM((yyval.s), SyntaxElementSymbol, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]), (yysemantic_stack_[(1) - (1)].s)._u.exp->sym()); }
    break;

  case 15:
/* Line 670 of lalr1.cc  */
#line 264 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); CMPLELEMENTRY_SYM((yyval.s), SyntaxElementSymbol, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]), (yysemantic_stack_[(1) - (1)].s)._u.exp->sym()); }
    break;

  case 16:
/* Line 670 of lalr1.cc  */
#line 272 "CMPL_Parser.yy"
    { (yyval.s).init();
		   																		  if (!(yysemantic_stack_[(2) - (1)].s)._empty && PARSE_CONTEXT.testCompControlCB((yysemantic_stack_[(2) - (1)].s)._elem, (yylocation_stack_[(2) - (1)]), false)) { CMPLELEMENTRY((yyval.s), SyntaxElementStatement, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (1)].s)); }
																				  else { CMPLELEMENTRY_EMPTY((yysemantic_stack_[(2) - (2)].s), (yylocation_stack_[(2) - (2)])); CMPLELEMENTRY((yyval.s), SyntaxElementStatement, (yylocation_stack_[(2) - (2)]), (yylocation_stack_[(2) - (2)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (2)].s)); }
																				  PARSE_CONTEXT.endOfStatement((yyval.s)._elem); }
    break;

  case 17:
/* Line 670 of lalr1.cc  */
#line 276 "CMPL_Parser.yy"
    { (yyval.s).init();
																				  if ((yysemantic_stack_[(3) - (2)].s)._u.b) PARSE_CONTEXT.testCompControlCB((yysemantic_stack_[(3) - (1)].s)._elem, (yylocation_stack_[(3) - (1)]), true);
																				  CMPLELEMENTRY((yyval.s), SyntaxElementStatement, ((yysemantic_stack_[(3) - (1)].s)._empty ? ((yylocation_stack_[(3) - (2)])) : ((yylocation_stack_[(3) - (1)]))), (yylocation_stack_[(3) - (3)])); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (2)].s)); PARSE_CONTEXT.endOfStatement((yyval.s)._elem); NOT_USED((yysemantic_stack_[(3) - (3)].s)); }
    break;

  case 18:
/* Line 670 of lalr1.cc  */
#line 279 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_ERR((yysemantic_stack_[(2) - (1)].s), (yylocation_stack_[(2) - (1)])); CMPLELEMENTRY((yyval.s), SyntaxElementStatement, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (1)].s)); PARSE_CONTEXT.endOfStatement((yyval.s)._elem); NOT_USED((yysemantic_stack_[(2) - (2)].s));
																				  yyerrok; }
    break;

  case 19:
/* Line 670 of lalr1.cc  */
#line 283 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementAssignRhs, (yylocation_stack_[(2) - (2)]), (yylocation_stack_[(2) - (2)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (2)].s)); CMPLELEM_SET((yysemantic_stack_[(2) - (2)].s), (yyval.s));
			  																	  CMPLELEMENTRY_TXT((yyval.s), SyntaxElementAssignment, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]), (yysemantic_stack_[(2) - (1)].s)._u.exp->assignOp()); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s));
																				  if ((yysemantic_stack_[(2) - (1)].s)._u.exp->isRefAssign()) { (yysemantic_stack_[(2) - (2)].s)._u.exp->compChangeFetchLvalue(&PARSE_CONTEXT); }
																				  COMP_ASSIGN((yyval.s)._elem, (yysemantic_stack_[(2) - (1)].s)._u.exp, (yysemantic_stack_[(2) - (2)].s)._u.exp);
																				  (yysemantic_stack_[(2) - (2)].s)._u.exp->checkClearLvalSyms(&PARSE_CONTEXT);
																				  (yysemantic_stack_[(2) - (1)].s)._u.exp->assignSpecialToConst((yysemantic_stack_[(2) - (2)].s)._u.exp->special());
																				  delete (yysemantic_stack_[(2) - (1)].s)._u.exp; delete (yysemantic_stack_[(2) - (2)].s)._u.exp; (yyval.s)._u.b = false; }
    break;

  case 20:
/* Line 670 of lalr1.cc  */
#line 290 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s);
																				  bool controlCB = false;
																				  bool amEmpty = PARSE_CONTEXT.assignModCurrentEmpty(true);
																				  if ((yysemantic_stack_[(1) - (1)].s)._u.exp->setAssignIfLhs(&PARSE_CONTEXT)) {
																				  	(yysemantic_stack_[(1) - (1)].s)._u.exp->checkLNPError(&PARSE_CONTEXT);
																				  	CMPLELEMENTRY((yyval.s), SyntaxElementAssignLhs, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(1) - (1)].s));
																					COMP_ASSIGN((yyval.s)._elem, (yysemantic_stack_[(1) - (1)].s)._u.exp, NULL); }
																				  else {
																				    controlCB = PARSE_CONTEXT.assignModControlCB(&(yylocation_stack_[(1) - (1)]));
																					if (!controlCB) {
																				  		if (!amEmpty) PARSE_CONTEXT.outParseError(ERROR_LVL_NORMAL, "statement cannot have assign modificators", (yylocation_stack_[(1) - (1)]));
																						COMP_ASSIGN((yyval.s)._elem, NULL, (yysemantic_stack_[(1) - (1)].s)._u.exp); } }
																				  delete (yysemantic_stack_[(1) - (1)].s)._u.exp; (yyval.s)._u.b = controlCB; }
    break;

  case 21:
/* Line 670 of lalr1.cc  */
#line 305 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(2) - (1)].s); CMPLELEMENTRY((yyval.s), SyntaxElementAssignLhs, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (1)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (1)].s));
			 																	  (yysemantic_stack_[(2) - (1)].s)._u.exp->checkLNPError(&PARSE_CONTEXT);
			 																	  (yyval.s)._u.exp->setAssignLhs(&PARSE_CONTEXT, (yysemantic_stack_[(2) - (2)].s)._name, &(yylocation_stack_[(2) - (2)])); }
    break;

  case 22:
/* Line 670 of lalr1.cc  */
#line 310 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); (yysemantic_stack_[(1) - (1)].s)._u.exp->checkLNPError(&PARSE_CONTEXT); }
    break;

  case 23:
/* Line 670 of lalr1.cc  */
#line 311 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); }
    break;

  case 24:
/* Line 670 of lalr1.cc  */
#line 312 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementIndexation, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)])); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s));
																				  (yyval.s).setExp((yysemantic_stack_[(2) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_IND, (yysemantic_stack_[(2) - (2)].s)._u.exp, true)); }
    break;

  case 25:
/* Line 670 of lalr1.cc  */
#line 316 "CMPL_Parser.yy"
    { COMP_FETCH_SYM((yyval.s)._elem, (yysemantic_stack_[(1) - (1)].s)._u.exp); (yyval.s)._u.exp->checkSetCbhExpr(&PARSE_CONTEXT); }
    break;

  case 26:
/* Line 670 of lalr1.cc  */
#line 319 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 27:
/* Line 670 of lalr1.cc  */
#line 320 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 28:
/* Line 670 of lalr1.cc  */
#line 321 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 29:
/* Line 670 of lalr1.cc  */
#line 322 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 30:
/* Line 670 of lalr1.cc  */
#line 323 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 31:
/* Line 670 of lalr1.cc  */
#line 324 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 32:
/* Line 670 of lalr1.cc  */
#line 325 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 33:
/* Line 670 of lalr1.cc  */
#line 332 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementCodeblock, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(3) - (2)].s)); NOT_USED((yysemantic_stack_[(3) - (1)].s)); NOT_USED((yysemantic_stack_[(3) - (3)].s));
		   																		  (yyval.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yyval.s)._elem->loc(), specialSymbolNo, false, true));
																				  (yyval.s)._u.fnc.exp = (yyval.s)._u.exp; (yyval.s)._u.fnc.cntLocal = PARSE_CONTEXT.funcParseScopeInfo((yyval.s)._u.fnc.useSubs);
		   																		  PARSE_CONTEXT.endParseScope((yyval.s)._elem, (yylocation_stack_[(3) - (3)])); }
    break;

  case 34:
/* Line 670 of lalr1.cc  */
#line 336 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_ERR((yysemantic_stack_[(3) - (2)].s), (yylocation_stack_[(3) - (2)])); CMPLELEMENTRY((yyval.s), SyntaxElementCodeblock, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(3) - (2)].s)); NOT_USED((yysemantic_stack_[(3) - (1)].s)); NOT_USED((yysemantic_stack_[(3) - (3)].s));
																				  (yyval.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yyval.s)._elem->loc(), specialSymbolNo, false, true));
																				  (yyval.s)._u.fnc.exp = (yyval.s)._u.exp; (yyval.s)._u.fnc.cntLocal = PARSE_CONTEXT.funcParseScopeInfo((yyval.s)._u.fnc.useSubs);
																				  PARSE_CONTEXT.endParseScope((yyval.s)._elem, (yylocation_stack_[(3) - (3)]));
																				  yyerrok; }
    break;

  case 35:
/* Line 670 of lalr1.cc  */
#line 343 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.startParseScope((yyval.s)._elem, (yylocation_stack_[(1) - (1)]), parseScopeTypeBlock, (yysemantic_stack_[(1) - (1)].s)._u.sptt);
																				  PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 36:
/* Line 670 of lalr1.cc  */
#line 347 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); }
    break;

  case 37:
/* Line 670 of lalr1.cc  */
#line 348 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEM_CONCAT((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); NOT_USED((yysemantic_stack_[(3) - (2)].s)); }
    break;

  case 38:
/* Line 670 of lalr1.cc  */
#line 351 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.startParseScope((yyval.s)._elem, (yylocation_stack_[(1) - (1)]), parseScopeTypePart); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 39:
/* Line 670 of lalr1.cc  */
#line 354 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementBlockPart, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)])); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s)); delete (yysemantic_stack_[(2) - (1)].s)._u.exp; PARSE_CONTEXT.setPartParseScopeElem((yyval.s)._elem); }
    break;

  case 40:
/* Line 670 of lalr1.cc  */
#line 357 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(3) - (2)].s); PARSE_CONTEXT.startParseScope((yysemantic_stack_[(3) - (3)].s)._elem, (yylocation_stack_[(3) - (3)]), parseScopeTypeBody); PARSE_CONTEXT.setCbExprModeCBBodyStart(); NOT_USED((yysemantic_stack_[(3) - (1)].s)); }
    break;

  case 41:
/* Line 670 of lalr1.cc  */
#line 360 "CMPL_Parser.yy"
    { (yyval.s).init(); }
    break;

  case 42:
/* Line 670 of lalr1.cc  */
#line 361 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEM_CONCAT((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s)); }
    break;

  case 43:
/* Line 670 of lalr1.cc  */
#line 364 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementModificator, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]), (yysemantic_stack_[(1) - (1)].s)._name); PARSE_CONTEXT.setParseScopeParBlockPart(ICPAR_BLOCK_ORDERED); }
    break;

  case 44:
/* Line 670 of lalr1.cc  */
#line 367 "CMPL_Parser.yy"
    { (yyval.s).init();
			 																	  if ((yysemantic_stack_[(1) - (1)].s)._empty) { CMPLELEMENTRY_EMPTY((yysemantic_stack_[(1) - (1)].s), (yylocation_stack_[(1) - (1)])); (yysemantic_stack_[(1) - (1)].s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yylocation_stack_[(1) - (1)]))); }
			 																	  CMPLELEMENTRY((yyval.s), SyntaxElementBlockHeader, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(1) - (1)].s));
																				  (yyval.s).setExp((yysemantic_stack_[(1) - (1)].s)._u.exp); }
    break;

  case 45:
/* Line 670 of lalr1.cc  */
#line 371 "CMPL_Parser.yy"
    { (yyval.s).init();
																				  if ((yysemantic_stack_[(3) - (1)].s)._empty) { CMPLELEMENTRY_EMPTY((yysemantic_stack_[(3) - (1)].s), (yylocation_stack_[(3) - (1)])); (yysemantic_stack_[(3) - (1)].s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yylocation_stack_[(3) - (1)]))); }
																				  CMPLELEMENTRY((yyval.s), SyntaxElementBlockHeader, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (1)])); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s));
																				  (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CBHCAT, (yysemantic_stack_[(3) - (3)].s)._u.exp, true)); }
    break;

  case 46:
/* Line 670 of lalr1.cc  */
#line 377 "CMPL_Parser.yy"
    { (yyval.s).init(); }
    break;

  case 47:
/* Line 670 of lalr1.cc  */
#line 378 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(2) - (2)].s); (yyval.s)._u.exp->setAssignCbh(&PARSE_CONTEXT); COMP_CBHEADER_END((yyval.s)._elem, (yyval.s)._u.exp, (yysemantic_stack_[(2) - (1)].s)._u.cbr.a); (yyval.s)._u.exp->resetCbhExpr(); }
    break;

  case 48:
/* Line 670 of lalr1.cc  */
#line 381 "CMPL_Parser.yy"
    { (yyval.s).init(); COMP_CBHEADER_START(NULL, (yyval.s)._u.cbr.a); }
    break;

  case 49:
/* Line 670 of lalr1.cc  */
#line 384 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementBlockBody, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)])); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s));
		   																		  if (!(yysemantic_stack_[(2) - (1)].s)._empty) {
																				  	if (!PARSE_CONTEXT.assignModCurrentEmpty()) PARSE_CONTEXT.outParseError(ERROR_LVL_NORMAL, "expression as code block body cannot have assign modificators", (yylocation_stack_[(2) - (1)]));
																					if (PARSE_CONTEXT.hasLineNamePref()) PARSE_CONTEXT.outParseError(ERROR_LVL_NORMAL, "expression as code block body cannot have line name prefix", (yylocation_stack_[(2) - (1)]));
																				  }
																				  (yysemantic_stack_[(2) - (2)].s)._u.exp->checkLNPError(&PARSE_CONTEXT); (yysemantic_stack_[(2) - (2)].s)._u.exp->checkClearLvalSyms(&PARSE_CONTEXT);
																				  if ((yysemantic_stack_[(2) - (2)].s)._u.exp->ncSymAccess()) PARSE_CONTEXT.setParseScopeParBlockPart(ICPAR_BLOCK_NCSYM);
		   																		  delete (yysemantic_stack_[(2) - (2)].s)._u.exp; }
    break;

  case 50:
/* Line 670 of lalr1.cc  */
#line 392 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementBlockBody, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(1) - (1)].s)); PARSE_CONTEXT.setParseScopeParBlockPart(ICPAR_BLOCK_STMNT); }
    break;

  case 51:
/* Line 670 of lalr1.cc  */
#line 395 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); (yysemantic_stack_[(1) - (1)].s)._u.exp->checkLNPError(&PARSE_CONTEXT); }
    break;

  case 52:
/* Line 670 of lalr1.cc  */
#line 396 "CMPL_Parser.yy"
    { (yysemantic_stack_[(3) - (1)].s)._u.exp->checkCbhAssignError(&PARSE_CONTEXT, (yylocation_stack_[(3) - (2)]));
																				  (yyval.s).init(); CMPLELEMENTRY_ALT((yyval.s), SyntaxElementCompareOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), (yysemantic_stack_[(3) - (1)].s)._name, "=="); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); NOT_USED((yysemantic_stack_[(3) - (2)].s));
																				  (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, ICS_OPER_EQ2, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_EQ, 2); }
    break;

  case 53:
/* Line 670 of lalr1.cc  */
#line 402 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); (yyval.s)._u.cbr.b = (yysemantic_stack_[(1) - (1)].s)._u.b; COMP_FUNC_START((yyval.s)._elem, (yyval.s)._u.cbr.a); }
    break;

  case 54:
/* Line 670 of lalr1.cc  */
#line 408 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeResetStorePrv(); }
    break;

  case 55:
/* Line 670 of lalr1.cc  */
#line 409 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 56:
/* Line 670 of lalr1.cc  */
#line 410 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 57:
/* Line 670 of lalr1.cc  */
#line 411 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 58:
/* Line 670 of lalr1.cc  */
#line 412 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 59:
/* Line 670 of lalr1.cc  */
#line 413 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 60:
/* Line 670 of lalr1.cc  */
#line 414 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 61:
/* Line 670 of lalr1.cc  */
#line 415 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 62:
/* Line 670 of lalr1.cc  */
#line 416 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 63:
/* Line 670 of lalr1.cc  */
#line 417 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 64:
/* Line 670 of lalr1.cc  */
#line 418 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 65:
/* Line 670 of lalr1.cc  */
#line 419 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 66:
/* Line 670 of lalr1.cc  */
#line 420 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 67:
/* Line 670 of lalr1.cc  */
#line 421 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(2) - (2)].s); (yyval.s)._u.exp = (yysemantic_stack_[(2) - (2)].s)._u.fnc.exp; (yyval.s)._u.exp->resetVolaExp();
																				  CMPLELEMENTRY_TXT((yyval.s), SyntaxElementFunction, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]), ((yysemantic_stack_[(2) - (1)].s)._u.cbr.b ? "pure" : "nonpure")); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (2)].s));
																				  COMP_FUNC_END((yyval.s)._elem, (yysemantic_stack_[(2) - (1)].s)._u.cbr.a, (yysemantic_stack_[(2) - (2)].s)._u.fnc.cntLocal, (yysemantic_stack_[(2) - (2)].s)._u.fnc.useSubs);
																				  PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 68:
/* Line 670 of lalr1.cc  */
#line 425 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset();
																				  PARSE_CONTEXT.outParseError(ERROR_LVL_NORMAL, "illegal expression, maybe missing operation sign", (yylocation_stack_[(1) - (1)])); }
    break;

  case 69:
/* Line 670 of lalr1.cc  */
#line 429 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); (yyval.s)._u.exp->checkSetCbhExpr(&PARSE_CONTEXT); }
    break;

  case 70:
/* Line 670 of lalr1.cc  */
#line 430 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(2) - (2)].s); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementIncDec, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]), ((yysemantic_stack_[(2) - (1)].s)._u.i > 0 ? "prefix inc" : "prefix dec")); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (2)].s));
																				  (yyval.s).setExp((yysemantic_stack_[(2) - (2)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_INC, NULL, false));
																				  (yyval.s)._u.exp->checkSetCbhExpr(&PARSE_CONTEXT);
																				  COMP_INCDEC_FETCH((yyval.s)._elem, true, (yysemantic_stack_[(2) - (1)].s)._u.i); }
    break;

  case 71:
/* Line 670 of lalr1.cc  */
#line 434 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(2) - (1)].s); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementIncDec, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]), ((yysemantic_stack_[(2) - (2)].s)._u.i > 0 ? "postfix inc" : "postfix dec")); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (1)].s));
																				  (yyval.s).setExp((yysemantic_stack_[(2) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_INC, NULL, false));
																				  (yyval.s)._u.exp->checkSetCbhExpr(&PARSE_CONTEXT);
																				  COMP_INCDEC_FETCH((yyval.s)._elem, false, (yysemantic_stack_[(2) - (2)].s)._u.i); }
    break;

  case 72:
/* Line 670 of lalr1.cc  */
#line 440 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); CMPLELEMENTRY_SYM((yyval.s), SyntaxElementSymbol, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]), (yysemantic_stack_[(1) - (1)].s)._u.exp->sym());
		 																		  COMP_FETCH_SYM((yyval.s)._elem, (yysemantic_stack_[(1) - (1)].s)._u.exp);
																				  (yyval.s)._u.exp->setLvalueSyntaxElem((yyval.s)._elem); }
    break;

  case 73:
/* Line 670 of lalr1.cc  */
#line 445 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); }
    break;

  case 74:
/* Line 670 of lalr1.cc  */
#line 446 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEM_CONCAT((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CAT, (yysemantic_stack_[(3) - (3)].s)._u.exp, true)); }
    break;

  case 75:
/* Line 670 of lalr1.cc  */
#line 449 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); CMPLELEMENTRY((yyval.s), SyntaxElementLitDouble, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
		  																		  COMP_LIT_VALUE((yyval.s)._elem, (yysemantic_stack_[(1) - (1)].s)._u.s, ICS_LIT_REAL); (yyval.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yylocation_stack_[(1) - (1)]))); }
    break;

  case 76:
/* Line 670 of lalr1.cc  */
#line 451 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); CMPLELEMENTRY((yyval.s), SyntaxElementLitInt, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
																				  COMP_LIT_VALUE((yyval.s)._elem, (yysemantic_stack_[(1) - (1)].s)._u.s, ICS_LIT_INT); (yyval.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yylocation_stack_[(1) - (1)]))); }
    break;

  case 77:
/* Line 670 of lalr1.cc  */
#line 453 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); CMPLELEMENTRY((yyval.s), SyntaxElementLitString, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
																				  COMP_LIT_VALUE((yyval.s)._elem, (yysemantic_stack_[(1) - (1)].s)._u.s, ICS_LIT_STR); (yyval.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yylocation_stack_[(1) - (1)]))); }
    break;

  case 78:
/* Line 670 of lalr1.cc  */
#line 457 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); CMPLELEMENTRY((yyval.s), SyntaxElementLitDouble, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
			 																	  COMP_LIT_VALUE((yyval.s)._elem, (yysemantic_stack_[(1) - (1)].s)._u.s, ICS_LIT_REAL); (yyval.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yylocation_stack_[(1) - (1)])));
			 																	  PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 79:
/* Line 670 of lalr1.cc  */
#line 460 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); CMPLELEMENTRY((yyval.s), SyntaxElementLitInt, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
																				  COMP_LIT_VALUE((yyval.s)._elem, (yysemantic_stack_[(1) - (1)].s)._u.s, ICS_LIT_INT); (yyval.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yylocation_stack_[(1) - (1)])));
																				  PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 80:
/* Line 670 of lalr1.cc  */
#line 466 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementArray, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(3) - (2)].s)); NOT_USED((yysemantic_stack_[(3) - (1)].s));
		   																		  if ((yysemantic_stack_[(3) - (2)].s)._u.exp->listCnt() || (yysemantic_stack_[(3) - (2)].s)._u.exp->empty()) { COMP_CONSTRUCT((yyval.s)._elem, ICS_CONSTRUCT_ARRAY, ((yysemantic_stack_[(3) - (2)].s)._u.exp->listCnt() ?: 1)); }
		   																		  (yyval.s).setExp((yysemantic_stack_[(3) - (2)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_ARR, NULL, false)); }
    break;

  case 81:
/* Line 670 of lalr1.cc  */
#line 469 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_ERR((yysemantic_stack_[(3) - (2)].s), (yylocation_stack_[(3) - (2)])); CMPLELEMENTRY((yyval.s), SyntaxElementArray, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(3) - (2)].s)); NOT_USED((yysemantic_stack_[(3) - (1)].s));
																				  (yyval.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yylocation_stack_[(3) - (1)])));
																				  yyerrok; }
    break;

  case 82:
/* Line 670 of lalr1.cc  */
#line 474 "CMPL_Parser.yy"
    { (yyval.s).init(); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 83:
/* Line 670 of lalr1.cc  */
#line 477 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementTupel, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(3) - (2)].s)); NOT_USED((yysemantic_stack_[(3) - (1)].s));
		   																		  COMP_CONSTRUCT((yyval.s)._elem, ICS_CONSTRUCT_TUPEL, ((yysemantic_stack_[(3) - (2)].s)._u.exp->listCnt() ?: 1));
		   																		  (yyval.s).setExp((yysemantic_stack_[(3) - (2)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_TUP, NULL, false)); }
    break;

  case 84:
/* Line 670 of lalr1.cc  */
#line 480 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_ERR((yysemantic_stack_[(3) - (2)].s), (yylocation_stack_[(3) - (2)])); CMPLELEMENTRY((yyval.s), SyntaxElementTupel, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(3) - (2)].s)); NOT_USED((yysemantic_stack_[(3) - (1)].s));
																				  (yyval.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yylocation_stack_[(3) - (1)])));
																				  yyerrok; }
    break;

  case 85:
/* Line 670 of lalr1.cc  */
#line 485 "CMPL_Parser.yy"
    { (yyval.s).init(); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 86:
/* Line 670 of lalr1.cc  */
#line 488 "CMPL_Parser.yy"
    { (yyval.s).init(); 
		   																		  if ((yysemantic_stack_[(1) - (1)].s)._empty) { CMPLELEMENTRY_EMPTY((yyval.s), (yylocation_stack_[(1) - (1)])); COMP_SET_SYNTAXELEM((yysemantic_stack_[(1) - (1)].s)._u.u, (yyval.s)._elem); (yysemantic_stack_[(1) - (1)].s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yylocation_stack_[(1) - (1)]), specialSymbolKnownVal, true)); }
		   																		  else { CMPLELEM_SET((yyval.s), (yysemantic_stack_[(1) - (1)].s)); };
		   																		  (yyval.s).setExp((yysemantic_stack_[(1) - (1)].s)._u.exp); }
    break;

  case 87:
/* Line 670 of lalr1.cc  */
#line 492 "CMPL_Parser.yy"
    { (yyval.s).init(); 
																				  if ((yysemantic_stack_[(3) - (1)].s)._empty) { CMPLELEMENTRY_EMPTY((yysemantic_stack_[(3) - (1)].s), (yylocation_stack_[(3) - (1)])); COMP_SET_SYNTAXELEM((yysemantic_stack_[(3) - (1)].s)._u.u, (yysemantic_stack_[(3) - (1)].s)._elem); (yysemantic_stack_[(3) - (1)].s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yylocation_stack_[(3) - (1)]), specialSymbolKnownVal, true)); }
																				  CMPLELEM_CONCAT((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s));
																				  (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CAT, (yysemantic_stack_[(3) - (3)].s)._u.exp, true)); }
    break;

  case 88:
/* Line 670 of lalr1.cc  */
#line 498 "CMPL_Parser.yy"
    { (yyval.s).init(); COMP_LIT_BLANK((yyval.s)._u.u); }
    break;

  case 89:
/* Line 670 of lalr1.cc  */
#line 499 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); (yysemantic_stack_[(1) - (1)].s)._u.exp->checkLNPError(&PARSE_CONTEXT); }
    break;

  case 90:
/* Line 670 of lalr1.cc  */
#line 502 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementInterval, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)])); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); NOT_USED((yysemantic_stack_[(3) - (2)].s));
			 																	  (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_SET, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
																				  COMP_CONSTRUCT((yyval.s)._elem, ICS_CONSTRUCT_IV_LB, 2); }
    break;

  case 91:
/* Line 670 of lalr1.cc  */
#line 505 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementInterval, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)])); CMPLELEMENTRY_EMPTY((yysemantic_stack_[(2) - (2)].s), (yylocation_stack_[(2) - (2)])); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s));
																				  (yyval.s).setExp((yysemantic_stack_[(2) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_SET, NULL, false));
																				  COMP_CONSTRUCT((yyval.s)._elem, ICS_CONSTRUCT_IV_LB, 1); }
    break;

  case 92:
/* Line 670 of lalr1.cc  */
#line 508 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_EMPTY((yysemantic_stack_[(2) - (1)].s), (yylocation_stack_[(2) - (1)])); CMPLELEMENTRY((yyval.s), SyntaxElementInterval, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)])); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s));
																				  (yyval.s).setExp((yysemantic_stack_[(2) - (2)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_SET, NULL, false));
																				  COMP_CONSTRUCT((yyval.s)._elem, ICS_CONSTRUCT_IV_WOLB, 1); }
    break;

  case 93:
/* Line 670 of lalr1.cc  */
#line 511 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementInterval, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]));
																				  CMPLELEMENTRY_EMPTY((yysemantic_stack_[(1) - (1)].s), (yylocation_stack_[(1) - (1)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(1) - (1)].s));
																				  CMPLELEMENTRY_EMPTY((yysemantic_stack_[(1) - (1)].s), (yylocation_stack_[(1) - (1)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(1) - (1)].s));
																				  (yyval.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yylocation_stack_[(1) - (1)])));
																				  COMP_CONSTRUCT((yyval.s)._elem, ICS_CONSTRUCT_IV_WOLB, 0); }
    break;

  case 94:
/* Line 670 of lalr1.cc  */
#line 518 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 95:
/* Line 670 of lalr1.cc  */
#line 521 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementSet, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)])); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (2)].s)); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(3) - (3)].s));
		  																		  if (!(yysemantic_stack_[(3) - (2)].s)._u.exp->oneElemArr()) PARSE_CONTEXT.outParseError(ERROR_LVL_NORMAL, "step for algorithmic set must be a single value", (yylocation_stack_[(3) - (2)]));
		  																		  (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_SET, (yysemantic_stack_[(3) - (3)].s)._u.exp, true)); delete (yysemantic_stack_[(3) - (2)].s)._u.exp;
																				  COMP_CONSTRUCT((yyval.s)._elem, ICS_CONSTRUCT_SET, 3); }
    break;

  case 96:
/* Line 670 of lalr1.cc  */
#line 527 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); }
    break;

  case 97:
/* Line 670 of lalr1.cc  */
#line 528 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); }
    break;

  case 98:
/* Line 670 of lalr1.cc  */
#line 535 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementUnaryOp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]), ((yysemantic_stack_[(2) - (1)].s)._u.b ? "+" : "-")); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (2)].s)); (yyval.s).setExp((yysemantic_stack_[(2) - (2)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, NULL, false));
		  																		  COMP_OPERATION((yyval.s)._elem, ((yysemantic_stack_[(2) - (1)].s)._u.b ? ICS_OPER_ADD : ICS_OPER_SUB), 1); }
    break;

  case 99:
/* Line 670 of lalr1.cc  */
#line 537 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_EMPTY((yysemantic_stack_[(1) - (1)].s), (yylocation_stack_[(1) - (1)])); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementUnaryOp, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]), ((yysemantic_stack_[(1) - (1)].s)._u.b ? "*" : "/")); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(1) - (1)].s)); (yyval.s).setExp(new ExprParseInfo(&PARSE_CONTEXT, (yylocation_stack_[(1) - (1)])));
																				  COMP_OPERATION((yyval.s)._elem, ((yysemantic_stack_[(1) - (1)].s)._u.b ? ICS_OPER_MUL : ICS_OPER_DIV), 0); }
    break;

  case 100:
/* Line 670 of lalr1.cc  */
#line 539 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementUnaryOp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]), ((yysemantic_stack_[(2) - (1)].s)._u.b ? "*" : "/")); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (2)].s)); (yyval.s).setExp((yysemantic_stack_[(2) - (2)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, NULL, false));
																				  COMP_OPERATION((yyval.s)._elem, ((yysemantic_stack_[(2) - (1)].s)._u.b ? ICS_OPER_MUL : ICS_OPER_DIV), 1); }
    break;

  case 101:
/* Line 670 of lalr1.cc  */
#line 541 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementUnaryOp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]), (yysemantic_stack_[(2) - (2)].s)._name); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (1)].s)); (yyval.s).setExp((yysemantic_stack_[(2) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, NULL, false));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_TRP, 1); }
    break;

  case 102:
/* Line 670 of lalr1.cc  */
#line 543 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementUnaryOp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]), (yysemantic_stack_[(2) - (1)].s)._name); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (2)].s)); (yyval.s).setExp((yysemantic_stack_[(2) - (2)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_LOG, NULL, false));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_NOT, 1); }
    break;

  case 103:
/* Line 670 of lalr1.cc  */
#line 547 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementBinaryOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), ((yysemantic_stack_[(3) - (2)].s)._u.b ? "+" : "-")); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
		  																		  COMP_OPERATION((yyval.s)._elem, ((yysemantic_stack_[(3) - (2)].s)._u.b ? ICS_OPER_ADD : ICS_OPER_SUB), 2); }
    break;

  case 104:
/* Line 670 of lalr1.cc  */
#line 549 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementBinaryOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), ((yysemantic_stack_[(3) - (2)].s)._u.b ? "*" : "/")); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ((yysemantic_stack_[(3) - (2)].s)._u.b ? ICS_OPER_MUL : ICS_OPER_DIV), 2); }
    break;

  case 105:
/* Line 670 of lalr1.cc  */
#line 551 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementBinaryOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), "^"); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_EXP, 2); }
    break;

  case 106:
/* Line 670 of lalr1.cc  */
#line 553 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementBinaryOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), (yysemantic_stack_[(3) - (2)].s)._name); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_LOG_AND, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_AND, 2); }
    break;

  case 107:
/* Line 670 of lalr1.cc  */
#line 555 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementBinaryOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), (yysemantic_stack_[(3) - (2)].s)._name); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_LOG, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_OR, 2); }
    break;

  case 108:
/* Line 670 of lalr1.cc  */
#line 557 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementBinaryOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), (yysemantic_stack_[(3) - (2)].s)._name); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_IRR, 2); }
    break;

  case 109:
/* Line 670 of lalr1.cc  */
#line 559 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementBinaryOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), (yysemantic_stack_[(3) - (2)].s)._name); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_OBJTO, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_OBJTO, 2); }
    break;

  case 110:
/* Line 670 of lalr1.cc  */
#line 561 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementBinaryOp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]), "in"); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s)); (yyval.s).setExp((yysemantic_stack_[(2) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_IN, (yysemantic_stack_[(2) - (2)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_IN, 2); }
    break;

  case 111:
/* Line 670 of lalr1.cc  */
#line 563 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementBinaryOp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]), "of"); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s)); (yyval.s).setExp((yysemantic_stack_[(2) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_IN, (yysemantic_stack_[(2) - (2)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_OF, 2); }
    break;

  case 112:
/* Line 670 of lalr1.cc  */
#line 565 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_ALT((yyval.s), SyntaxElementBinaryOp, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]), "", "*"); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s)); (yyval.s).setExp((yysemantic_stack_[(2) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, (yysemantic_stack_[(2) - (2)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_MUL, 2); }
    break;

  case 113:
/* Line 670 of lalr1.cc  */
#line 569 "CMPL_Parser.yy"
    { (yyval.s).init(); (yyval.s)._u.b = true; PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 114:
/* Line 670 of lalr1.cc  */
#line 570 "CMPL_Parser.yy"
    { (yyval.s).init(); (yyval.s)._u.b = false; PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 115:
/* Line 670 of lalr1.cc  */
#line 573 "CMPL_Parser.yy"
    { (yyval.s).init(); (yyval.s)._u.b = true; PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 116:
/* Line 670 of lalr1.cc  */
#line 574 "CMPL_Parser.yy"
    { (yyval.s).init(); (yyval.s)._u.b = false; PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 117:
/* Line 670 of lalr1.cc  */
#line 577 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); PARSE_CONTEXT.setCbExprModeReset(); }
    break;

  case 118:
/* Line 670 of lalr1.cc  */
#line 580 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(2) - (1)].s); NOT_USED((yysemantic_stack_[(2) - (2)].s)); }
    break;

  case 119:
/* Line 670 of lalr1.cc  */
#line 581 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(2) - (1)].s); NOT_USED((yysemantic_stack_[(2) - (2)].s)); /* $1 doesn't mean multiplication here, but is delivered so by flex, because "in" is a keyword operator */ }
    break;

  case 120:
/* Line 670 of lalr1.cc  */
#line 584 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(2) - (1)].s); NOT_USED((yysemantic_stack_[(2) - (2)].s)); }
    break;

  case 121:
/* Line 670 of lalr1.cc  */
#line 585 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(2) - (1)].s); NOT_USED((yysemantic_stack_[(2) - (2)].s)); /* $1 doesn't mean multiplication here, but is delivered so by flex, because "of" is a keyword operator */ }
    break;

  case 122:
/* Line 670 of lalr1.cc  */
#line 588 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementCompareOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), (yysemantic_stack_[(3) - (2)].s)._name); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
		   																		  COMP_OPERATION((yyval.s)._elem, ICS_OPER_EQ, 2); }
    break;

  case 123:
/* Line 670 of lalr1.cc  */
#line 590 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementCompareOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), (yysemantic_stack_[(3) - (2)].s)._name); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP2, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_EQ2, 2); }
    break;

  case 124:
/* Line 670 of lalr1.cc  */
#line 592 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementCompareOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), (yysemantic_stack_[(3) - (2)].s)._name); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_NE, 2); }
    break;

  case 125:
/* Line 670 of lalr1.cc  */
#line 594 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementCompareOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), (yysemantic_stack_[(3) - (2)].s)._name); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP2, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_NE2, 2); }
    break;

  case 126:
/* Line 670 of lalr1.cc  */
#line 596 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementCompareOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), (yysemantic_stack_[(3) - (2)].s)._name); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_LT, 2); }
    break;

  case 127:
/* Line 670 of lalr1.cc  */
#line 598 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementCompareOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), (yysemantic_stack_[(3) - (2)].s)._name); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_GT, 2); }
    break;

  case 128:
/* Line 670 of lalr1.cc  */
#line 600 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementCompareOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), (yysemantic_stack_[(3) - (2)].s)._name); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_LE, 2); }
    break;

  case 129:
/* Line 670 of lalr1.cc  */
#line 602 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementCompareOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), (yysemantic_stack_[(3) - (2)].s)._name); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CMP, (yysemantic_stack_[(3) - (3)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_GE, 2); }
    break;

  case 130:
/* Line 670 of lalr1.cc  */
#line 607 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementSubSymbolOp, (yylocation_stack_[(3) - (1)]), (yylocation_stack_[(3) - (3)]), "."); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(3) - (1)].s), (yysemantic_stack_[(3) - (3)].s)); NOT_USED((yysemantic_stack_[(3) - (2)].s));
			 																	  (yyval.s).setExp((yysemantic_stack_[(3) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_SUB, (yysemantic_stack_[(3) - (3)].s)._u.exp, true)); }
    break;

  case 131:
/* Line 670 of lalr1.cc  */
#line 611 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); }
    break;

  case 132:
/* Line 670 of lalr1.cc  */
#line 612 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(2) - (2)].s); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementIncDec, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]), ((yysemantic_stack_[(2) - (1)].s)._u.i > 0 ? "prefix inc" : "prefix dec")); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (2)].s));
																				  (yyval.s).setExp((yysemantic_stack_[(2) - (2)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_INC, NULL, false));
																				  COMP_INCDEC_FETCH((yyval.s)._elem, true, (yysemantic_stack_[(2) - (1)].s)._u.i); }
    break;

  case 133:
/* Line 670 of lalr1.cc  */
#line 615 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(2) - (1)].s); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementIncDec, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]), ((yysemantic_stack_[(2) - (2)].s)._u.i > 0 ? "postfix inc" : "postfix dec")); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (1)].s));
																				  (yyval.s).setExp((yysemantic_stack_[(2) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_INC, NULL, false));
																				  COMP_INCDEC_FETCH((yyval.s)._elem, false, (yysemantic_stack_[(2) - (2)].s)._u.i); }
    break;

  case 134:
/* Line 670 of lalr1.cc  */
#line 620 "CMPL_Parser.yy"
    { (yyval.s) = (yysemantic_stack_[(1) - (1)].s); CMPLELEMENTRY_SYM((yyval.s), SyntaxElementSymbol, (yylocation_stack_[(1) - (1)]), (yylocation_stack_[(1) - (1)]), (yysemantic_stack_[(1) - (1)].s)._u.exp->sym());
																				  COMP_FETCH_SYM((yyval.s)._elem, (yysemantic_stack_[(1) - (1)].s)._u.exp); (yyval.s)._u.exp->setLvalueSyntaxElem((yyval.s)._elem); }
    break;

  case 135:
/* Line 670 of lalr1.cc  */
#line 625 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementFuncCall, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)])); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s)); /* auch als Set-Konstruktor der Art 1(1)(n-1) */
			 																	  (yyval.s).setExp((yysemantic_stack_[(2) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CALL, (yysemantic_stack_[(2) - (2)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_FUNC, 2); }
    break;

  case 136:
/* Line 670 of lalr1.cc  */
#line 628 "CMPL_Parser.yy"
    { (yyval.s).init();
																				  if (PARSE_CONTEXT.modpt()->compatLineNamePref() && (yysemantic_stack_[(2) - (1)].s)._u.exp->sym() && (yysemantic_stack_[(2) - (1)].s)._u.exp->sym()->notDefined()) {
																					// no function call, $1 is a line name prefix
																					COMP_LNP_COMPAT((yysemantic_stack_[(2) - (1)].s)._elem, (yysemantic_stack_[(2) - (1)].s)._u.exp);
																					delete (yysemantic_stack_[(2) - (1)].s)._u.exp; (yyval.s) = (yysemantic_stack_[(2) - (2)].s); (yyval.s)._u.exp->setHasLNP((yylocation_stack_[(2) - (1)]));
																					CMPLELEMENTRY((yyval.s), SyntaxElementLineNamePrefix, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (1)])); CMPLELEM_CHILD((yyval.s), (yysemantic_stack_[(2) - (1)].s)); CMPLELEM_NEXT((yyval.s), (yysemantic_stack_[(2) - (2)].s));
																				  } else {
																				  	CMPLELEMENTRY((yyval.s), SyntaxElementFuncCall, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)])); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s));
																				  	(yyval.s).setExp((yysemantic_stack_[(2) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_CALL, (yysemantic_stack_[(2) - (2)].s)._u.exp, true));
																					COMP_OPERATION((yyval.s)._elem, ICS_OPER_FUNC, 2);
																				} }
    break;

  case 137:
/* Line 670 of lalr1.cc  */
#line 641 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY((yyval.s), SyntaxElementIndexation, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)])); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s));
																				  (yyval.s).setExp((yysemantic_stack_[(2) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_IND, (yysemantic_stack_[(2) - (2)].s)._u.exp, true));
																				  COMP_OPERATION((yyval.s)._elem, ICS_OPER_INDEX, 2); }
    break;

  case 138:
/* Line 670 of lalr1.cc  */
#line 646 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementError, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]), "illegal expression"); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s)); (yyval.s).setExp((yysemantic_stack_[(2) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, (yysemantic_stack_[(2) - (2)].s)._u.exp, true)); }
    break;

  case 139:
/* Line 670 of lalr1.cc  */
#line 647 "CMPL_Parser.yy"
    { (yyval.s).init(); CMPLELEMENTRY_TXT((yyval.s), SyntaxElementError, (yylocation_stack_[(2) - (1)]), (yylocation_stack_[(2) - (2)]), "illegal expression"); CMPLELEM_CHILD2((yyval.s), (yysemantic_stack_[(2) - (1)].s), (yysemantic_stack_[(2) - (2)].s)); (yyval.s).setExp((yysemantic_stack_[(2) - (1)].s)._u.exp->oper(&PARSE_CONTEXT, EXPR_INFO_OP_NUM, (yysemantic_stack_[(2) - (2)].s)._u.exp, true)); }
    break;


/* Line 670 of lalr1.cc  */
#line 2202 "_CMPL_Parser.cc"
      default:
        break;
      }

    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action
       invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
       yychar.  In the case of YYABORT or YYACCEPT, an incorrect
       destructor might then be invoked immediately.  In the case of
       YYERROR, subsequent parser actions might lead to an incorrect
       destructor call or verbose syntax error message before the
       lookahead is translated.  */
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	if (yychar == yyempty_)
	  yytoken = yyempty_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */
        if (yychar <= yyeof_)
          {
            /* Return failure if at end of input.  */
            if (yychar == yyeof_)
              YYABORT;
          }
        else
          {
            yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
            yychar = yyempty_;
          }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
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

    yyerror_range[1] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
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

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	  YYABORT;

	yyerror_range[1] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystate_stack_.height ())
      {
        yydestruct_ ("Cleanup: popping",
                     yystos_[yystate_stack_[0]],
                     &yysemantic_stack_[0],
                     &yylocation_stack_[0]);
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
        if (yychar != yyempty_)
          {
            /* Make sure we have latest lookahead translation.  See
               comments at user semantic actions for why this is
               necessary.  */
            yytoken = yytranslate_ (yychar);
            yydestruct_ (YY_NULL, yytoken, &yylval, &yylloc);
          }

        while (1 < yystate_stack_.height ())
          {
            yydestruct_ (YY_NULL,
                         yystos_[yystate_stack_[0]],
                         &yysemantic_stack_[0],
                         &yylocation_stack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  // Generate an error message.
  std::string
  CMPL_Parser::yysyntax_error_ (int yystate, int yytoken)
  {
    std::string yyres;
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
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yychar.
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
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
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

    char const* yyformat = YY_NULL;
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


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char CMPL_Parser::yypact_ninf_ = -90;
  const short int
  CMPL_Parser::yypact_[] =
  {
       535,   -43,   -90,   -90,   -90,   -90,   -90,    18,   -90,   487,
     -90,   743,   111,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -23,   -90,   -90,   -90,   -39,   806,   -90,
     577,    -9,   728,   -90,   -32,     5,   -90,   784,   -90,   444,
     -90,   402,   -90,   917,   -90,   -90,   -90,   832,   917,   832,
     832,   832,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,     2,   910,    -4,   -90,    -3,   -19,   619,   -46,
      -2,   -90,   -23,   832,   832,   832,   832,   832,   832,   832,
     832,   832,   832,   -90,   -90,   832,   -90,   832,   -36,   832,
     -90,   -14,   -90,   917,   832,   832,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,    76,
     -17,   910,     0,     3,     4,     7,   130,   130,   130,   130,
     176,   176,   -90,   -90,   -90,   -90,    -2,   -90,   743,   -90,
       8,    11,   832,   -90,   -90,   965,   990,   691,   691,   691,
     691,   691,   691,   691,   691,    76,   106,   -90,    15,   -90,
      12,   -90,   -90,   -90,   -90,   130,     6,    76,   -90,   -90,
     832,   -90,   -90,   -90,   674,   -90,   -46,   -90,   883,   -90,
     -90,   -90,   -90,   832,   910
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
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
       0,     0,     0,   120,   118,     0,   101,     0,     0,     0,
     136,   135,   137,    91,     0,     0,    71,   138,   139,    26,
      27,    28,    29,    30,    31,    32,    21,   121,   119,   112,
       0,    89,     0,    86,     0,     0,    92,    98,   100,   102,
     110,   111,    24,    34,    33,    38,    41,    50,     0,    39,
       0,    44,     0,    42,   109,   107,   106,   129,   128,   127,
     126,   125,   124,   123,   122,   108,   105,   134,     0,   130,
     131,    74,    97,    96,    95,    90,   103,   104,    81,    80,
      88,    84,    83,    37,    73,    40,    48,    47,    51,   132,
     133,    87,    45,     0,    52
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  CMPL_Parser::yypgoto_[] =
  {
       -90,   -90,    -8,   -90,   -90,   -10,   -90,    29,   -90,   -90,
     -90,   -90,   -90,   -90,   -30,   -90,   -51,   -90,   -90,   -90,
      10,   -90,   -89,   -90,   -90,   -90,   -90,   -90,   -11,   -90,
     -18,    30,   -41,   -90,   100,   -90,    40,   -90,   -42,   -90,
     -90,   142,   -90,   -90,   -90,   -90,   202,   244,   -90,   -90,
     -90,   -90,   -90,   -90,   -63,   -90,   -90,   -90
  };

  /* YYDEFGOTO[NTERM-NUM].  */
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

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char CMPL_Parser::yytable_ninf_ = -89;
  const short int
  CMPL_Parser::yytable_[] =
  {
        42,    17,    67,   108,    27,    28,    29,   157,   -46,   125,
      32,    81,   100,   109,   -46,    68,    15,   158,    16,    32,
      69,   106,    27,    28,    29,    26,   107,    73,    32,    20,
      21,    95,    96,    97,    22,    25,   119,   135,    24,    25,
      26,    98,   126,   100,   168,    75,   127,   128,   129,   130,
     131,   133,   134,   110,   111,   112,   113,   114,   157,   115,
     163,   169,   175,   170,   144,   180,   171,    70,   138,   172,
     137,   176,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   102,   162,   155,   173,   156,   182,    42,   100,
     143,   100,   165,   166,   167,   179,   100,   100,   100,   100,
     100,   100,    96,    97,    22,     0,     0,     0,    24,    25,
      26,    98,   132,   102,     0,   100,   100,   100,   100,   100,
     100,   100,   100,   100,   100,   100,   100,   174,   181,   161,
       0,   178,     0,    97,    22,   100,   100,   100,    24,    25,
      26,    98,   101,     0,   100,     0,     0,     0,   100,     0,
       2,     0,     0,     0,   100,     3,     4,     5,     6,   102,
       0,   102,    24,    25,    26,    98,   102,   102,   102,   102,
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
      22,    23,     0,     0,    24,    25,    26,     0,    27,    28,
      29,     0,    30,    31,    32,   120,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,    35,
       0,     0,   -88,     0,   -88,    18,    19,    20,    21,     0,
       0,     0,    22,    23,     0,     0,    24,    25,    26,     0,
      27,    28,    29,     0,    30,    31,    32,    -3,     1,     0,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,    35,     0,     0,   -88,   -88,     0,     0,    -8,    -8,
      -8,    -8,     0,     0,     0,    -8,    -8,     0,     0,    -8,
      -8,    -8,     0,    -8,    -8,    -8,     2,    -8,    -8,    -8,
       0,     3,     4,     5,     6,    -3,     1,     0,     0,     0,
      -8,    -8,    -3,    -3,    -8,     0,    -8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    -8,    -8,    -8,    -8,
       0,     0,     0,    -8,    -8,     0,     0,    -8,    -8,    -8,
       0,    -8,    -8,    -8,     2,    -8,    -8,    -8,    74,     3,
       4,     5,     6,     0,     0,     0,     0,     0,    -8,    -8,
       0,     0,    -8,     0,    -8,     0,     0,     0,   -41,   -41,
     -41,   -41,     0,     0,     0,   -41,   -41,     0,     0,   -41,
     -41,   -41,     0,   -41,   -41,   -41,     0,   -41,   -41,   -41,
       1,     0,     0,     0,    75,     0,     0,     0,     0,     0,
     -41,   -41,     0,     0,   -41,     0,     0,   -41,     0,     0,
      -8,    -8,    -8,    -8,     0,     0,     0,    -8,    -8,     0,
       0,    -8,    -8,    -8,     0,    -8,    -8,    -8,     2,    -8,
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
       0,    22,    23,     0,     0,    24,    25,    26,     0,    27,
      28,    29,     0,    30,    31,    32,     0,     0,    99,     0,
       0,     0,     0,     0,     0,     0,    33,    34,     0,     0,
      35,     0,    36,   117,   118,    18,    19,    20,    21,     0,
       0,     0,    22,    23,     0,     0,    24,    25,    26,     0,
      27,    28,    29,     0,    30,    31,    32,    18,    19,    20,
      21,     0,     0,     0,    22,    23,     0,    33,    24,    25,
      26,    35,    27,    28,    29,     0,    30,    31,    32,     0,
       3,     4,     0,    18,    19,    20,    21,     0,     0,    33,
      22,    23,     0,    35,    24,    25,    26,     0,    27,    28,
      29,     0,    30,    31,    32,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,    82,     0,     0,    35,
       0,   183,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    18,    19,    20,    21,    95,    96,
      97,    22,     0,    82,     0,    24,    25,    26,    98,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    18,    19,    20,    21,    95,    96,    97,    22,     0,
       0,     0,    24,    25,    26,    98,    23,     0,     0,    24,
      25,    26,     0,    27,    28,    29,     0,    30,    31,    32,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      33,     0,     0,     0,    35,    84,    85,    86,    87,    88,
      89,    90,    91,    92,    93,    94,    18,    19,    20,    21,
      95,    96,    97,    22,     0,     0,     0,    24,    25,    26,
      98,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    18,    19,    20,    21,    95,    96,    97,    22,     0,
       0,     0,    24,    25,    26,    98
  };

  /* YYCHECK.  */
  const short int
  CMPL_Parser::yycheck_[] =
  {
        11,     9,    12,    44,    36,    37,    38,    43,    54,    51,
      42,    41,    42,     8,    60,    33,    59,    53,     0,    42,
      59,    53,    36,    37,    38,    34,    44,    38,    42,    23,
      24,    25,    26,    27,    28,    33,    47,    56,    32,    33,
      34,    35,    53,    73,    61,    47,    57,    58,    59,    60,
      61,    55,    55,    48,    49,    50,    51,    52,    43,    54,
     101,    61,    54,    60,    82,    53,    62,    38,    78,    62,
      78,    60,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    42,   101,    95,   136,    97,   176,    99,   119,
      80,   121,   103,   104,   105,   158,   126,   127,   128,   129,
     130,   131,    26,    27,    28,    -1,    -1,    -1,    32,    33,
      34,    35,    72,    73,    -1,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   138,   170,    99,
      -1,   142,    -1,    27,    28,   165,   166,   167,    32,    33,
      34,    35,    42,    -1,   174,    -1,    -1,    -1,   178,    -1,
      39,    -1,    -1,    -1,   184,    44,    45,    46,    47,   119,
      -1,   121,    32,    33,    34,    35,   126,   127,   128,   129,
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
      28,    29,    -1,    -1,    32,    33,    34,    -1,    36,    37,
      38,    -1,    40,    41,    42,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    57,
      -1,    -1,    60,    -1,    62,    21,    22,    23,    24,    -1,
      -1,    -1,    28,    29,    -1,    -1,    32,    33,    34,    -1,
      36,    37,    38,    -1,    40,    41,    42,     0,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,
      -1,    57,    -1,    -1,    60,    61,    -1,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    28,    29,    -1,    -1,    32,
      33,    34,    -1,    36,    37,    38,    39,    40,    41,    42,
      -1,    44,    45,    46,    47,     0,     1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    21,    22,    23,    24,
      -1,    -1,    -1,    28,    29,    -1,    -1,    32,    33,    34,
      -1,    36,    37,    38,    39,    40,    41,    42,     1,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    53,    54,
      -1,    -1,    57,    -1,    59,    -1,    -1,    -1,    21,    22,
      23,    24,    -1,    -1,    -1,    28,    29,    -1,    -1,    32,
      33,    34,    -1,    36,    37,    38,    -1,    40,    41,    42,
       1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      53,    54,    -1,    -1,    57,    -1,    -1,    60,    -1,    -1,
      21,    22,    23,    24,    -1,    -1,    -1,    28,    29,    -1,
      -1,    32,    33,    34,    -1,    36,    37,    38,    39,    40,
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
      -1,    28,    29,    -1,    -1,    32,    33,    34,    -1,    36,
      37,    38,    -1,    40,    41,    42,    -1,    -1,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    -1,    -1,
      57,    -1,    59,    19,    20,    21,    22,    23,    24,    -1,
      -1,    -1,    28,    29,    -1,    -1,    32,    33,    34,    -1,
      36,    37,    38,    -1,    40,    41,    42,    21,    22,    23,
      24,    -1,    -1,    -1,    28,    29,    -1,    53,    32,    33,
      34,    57,    36,    37,    38,    -1,    40,    41,    42,    -1,
      44,    45,    -1,    21,    22,    23,    24,    -1,    -1,    53,
      28,    29,    -1,    57,    32,    33,    34,    -1,    36,    37,
      38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,     3,    -1,    -1,    57,
      -1,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    -1,     3,    -1,    32,    33,    34,    35,     9,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      -1,    -1,    32,    33,    34,    35,    29,    -1,    -1,    32,
      33,    34,    -1,    36,    37,    38,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    -1,    -1,    -1,    57,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    -1,    -1,    -1,    32,    33,    34,
      35,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    -1,
      -1,    -1,    32,    33,    34,    35
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  CMPL_Parser::yystos_[] =
  {
         0,     1,    39,    44,    45,    46,    47,    64,    65,    66,
      67,    68,    69,    70,    71,    59,     0,    65,    21,    22,
      23,    24,    28,    29,    32,    33,    34,    36,    37,    38,
      40,    41,    42,    53,    54,    57,    59,    72,    73,    77,
      78,    90,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   103,   104,   105,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   118,   119,   120,    68,    93,    59,
      70,    74,    75,    91,     1,    47,    79,    81,    82,    83,
      84,    77,     3,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    25,    26,    27,    35,    60,
      77,    97,    99,   104,   109,   110,    53,    93,    95,     8,
      48,    49,    50,    51,    52,    54,    76,    19,    20,    91,
       1,    91,   101,   102,     1,   101,    91,    91,    91,    91,
      91,    91,    99,    55,    55,    56,    80,    65,    68,    88,
      85,    86,    87,    83,    93,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    43,    53,   116,
     117,    94,    93,    95,   106,    91,    91,    91,    61,    61,
      60,    62,    62,    79,    91,    54,    60,    89,    91,   117,
      53,   101,    85,     8,    91
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  CMPL_Parser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,    43,    45,    42,    47,   276,   277,    94,   278,   279,
     280,   281,    40,    91,   282,   283,   284,   285,   286,   287,
     288,   289,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
      44,    41,    93
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
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

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
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


  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const CMPL_Parser::yytname_[] =
  {
    "\"end of file\"", "error", "$undefined", "\"operator `->`\"",
  "ASSIGN_DIV", "ASSIGN_MUL", "ASSIGN_SUB", "ASSIGN_ADD",
  "\"assign operator `:=`\"", "\"operator `||`\"", "\"operator `&&`\"",
  "\"operator `>=`\"", "\"operator `<=`\"", "\"operator `>`\"",
  "\"operator `<`\"", "\"operator `!=`\"", "\"operator `<>`\"",
  "\"operator `==`\"", "\"operator `=`\"", "\"operator `of`\"",
  "\"operator `in`\"", "'+'", "'-'", "'*'", "'/'", "\"operator `*>`\"",
  "\"transpose operator `T`\"", "'^'", "\"operator `..`\"",
  "\"operator `!`\"", "INDEX_SIGN", "NUMBER_SIGN", "'('", "'['", "\"`{`\"",
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
  "subsymbol", "functionCall", "indexation", "errorExpression", YY_NULL
  };

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const CMPL_Parser::rhs_number_type
  CMPL_Parser::yyrhs_[] =
  {
        64,     0,    -1,    65,    -1,    -1,    66,    65,    -1,    67,
      -1,    71,    -1,    68,    54,    -1,    -1,    69,    68,    -1,
      46,    -1,    47,    -1,    70,    -1,    39,    -1,    44,    -1,
      45,    -1,    68,    59,    -1,    68,    72,    59,    -1,     1,
      59,    -1,    73,    74,    -1,    94,    -1,    94,    76,    -1,
      91,    -1,    75,    -1,    75,    99,    -1,    70,    -1,     8,
      -1,    48,    -1,    49,    -1,    50,    -1,    51,    -1,    52,
      -1,    54,    -1,    78,    79,    55,    -1,    78,     1,    55,
      -1,    34,    -1,    81,    -1,    81,    80,    79,    -1,    56,
      -1,    82,    88,    -1,    83,    85,    54,    -1,    -1,    84,
      83,    -1,    47,    -1,    86,    -1,    86,    60,    85,    -1,
      -1,    87,    89,    -1,    -1,    68,    91,    -1,    65,    -1,
      91,    -1,    91,     8,    91,    -1,    57,    -1,    92,    -1,
      95,    -1,    97,    -1,    99,    -1,   103,    -1,   105,    -1,
     107,    -1,   108,    -1,   114,    -1,   115,    -1,   118,    -1,
     119,    -1,    77,    -1,    90,    77,    -1,   120,    -1,    93,
      -1,    53,    93,    -1,    93,    53,    -1,    42,    -1,    91,
      -1,    91,    60,    94,    -1,    37,    -1,    36,    -1,    38,
      -1,    41,    -1,    40,    -1,    98,   101,    61,    -1,    98,
       1,    61,    -1,    32,    -1,   100,   101,    62,    -1,   100,
       1,    62,    -1,    33,    -1,   102,    -1,   102,    60,   101,
      -1,    -1,    91,    -1,    91,   104,    91,    -1,    91,   104,
      -1,   104,    91,    -1,   104,    -1,    28,    -1,    91,    97,
     106,    -1,    95,    -1,    93,    -1,   109,    91,    -1,   110,
      -1,   110,    91,    -1,    91,    26,    -1,   111,    91,    -1,
      91,   109,    91,    -1,    91,   110,    91,    -1,    91,    27,
      91,    -1,    91,    10,    91,    -1,    91,     9,    91,    -1,
      91,    25,    91,    -1,    91,     3,    93,    -1,   112,    91,
      -1,   113,    91,    -1,    96,    91,    -1,    21,    -1,    22,
      -1,    23,    -1,    24,    -1,    29,    -1,    91,    20,    -1,
      96,    20,    -1,    91,    19,    -1,    96,    19,    -1,    91,
      18,    91,    -1,    91,    17,    91,    -1,    91,    16,    91,
      -1,    91,    15,    91,    -1,    91,    14,    91,    -1,    91,
      13,    91,    -1,    91,    12,    91,    -1,    91,    11,    91,
      -1,    91,    35,   116,    -1,   117,    -1,    53,   117,    -1,
     117,    53,    -1,    43,    -1,    91,    97,    -1,    91,    77,
      -1,    91,    99,    -1,    93,    93,    -1,    93,    95,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  CMPL_Parser::yyprhs_[] =
  {
         0,     0,     3,     5,     6,     9,    11,    13,    16,    17,
      20,    22,    24,    26,    28,    30,    32,    35,    39,    42,
      45,    47,    50,    52,    54,    57,    59,    61,    63,    65,
      67,    69,    71,    73,    77,    81,    83,    85,    89,    91,
      94,    98,    99,   102,   104,   106,   110,   111,   114,   115,
     118,   120,   122,   126,   128,   130,   132,   134,   136,   138,
     140,   142,   144,   146,   148,   150,   152,   154,   157,   159,
     161,   164,   167,   169,   171,   175,   177,   179,   181,   183,
     185,   189,   193,   195,   199,   203,   205,   207,   211,   212,
     214,   218,   221,   224,   226,   228,   232,   234,   236,   239,
     241,   244,   247,   250,   254,   258,   262,   266,   270,   274,
     278,   281,   284,   287,   289,   291,   293,   295,   297,   300,
     303,   306,   309,   313,   317,   321,   325,   329,   333,   337,
     341,   345,   347,   350,   353,   355,   358,   361,   364,   367
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
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
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  CMPL_Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
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
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int CMPL_Parser::yyeof_ = 0;
  const int CMPL_Parser::yylast_ = 1025;
  const int CMPL_Parser::yynnts_ = 58;
  const int CMPL_Parser::yyempty_ = -2;
  const int CMPL_Parser::yyfinal_ = 16;
  const int CMPL_Parser::yyterror_ = 1;
  const int CMPL_Parser::yyerrcode_ = 256;
  const int CMPL_Parser::yyntokens_ = 63;

  const unsigned int CMPL_Parser::yyuser_token_number_max_ = 307;
  const CMPL_Parser::token_number_type CMPL_Parser::yyundef_token_ = 2;


} // cmpl
/* Line 1141 of lalr1.cc  */
#line 3095 "_CMPL_Parser.cc"
/* Line 1142 of lalr1.cc  */
#line 650 "CMPL_Parser.yy"


void cmpl::CMPL_Parser::error(const cmpl::CMPL_Parser::location_type& l, const std::string& m)
{
	PARSE_CONTEXT.outParseError(ERROR_LVL_NORMAL, m, l, true);
}


