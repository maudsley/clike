// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.



// First part of user prologue.
#line 23 "./src/clike/parser.yy"

#include "ast_builder.h"
#include "lexer.h"
#undef yylex
#define yylex lexer.yylex

#include <cstdio>
#include <iostream>

#line 50 "./src/clike/parser.cpp"


#include "parser.h"




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

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
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
    while (false)
# endif


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
      *yycdebug_ << '\n';                       \
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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "./src/clike/parser.yy"
namespace clike {
#line 147 "./src/clike/parser.cpp"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
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
              else
                goto append;

            append:
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
  parser::parser (clike::lexer& lexer_yyarg, clike::syntax_tree_builder& ast_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      lexer (lexer_yyarg),
      ast (ast_yyarg)
  {}

  parser::~parser ()
  {}

  parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
    , location (std::move (that.location))
  {
    switch (this->type_get ())
    {
      case 79: // IDENTIFIER
      case 80: // INTCONST
      case 81: // HEXCONST
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

  }
#endif

  template <typename Base>
  parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->type_get ())
    {
      case 79: // IDENTIFIER
      case 80: // INTCONST
      case 81: // HEXCONST
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  bool
  parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 79: // IDENTIFIER
      case 80: // INTCONST
      case 81: // HEXCONST
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_type.
  parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  void
  parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  void
  parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  int
  parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }


  // by_state.
  parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  parser::symbol_number_type
  parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  parser::stack_symbol_type::stack_symbol_type ()
  {}

  parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 79: // IDENTIFIER
      case 80: // INTCONST
      case 81: // HEXCONST
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 79: // IDENTIFIER
      case 80: // INTCONST
      case 81: // HEXCONST
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 79: // IDENTIFIER
      case 80: // INTCONST
      case 81: // HEXCONST
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  parser::stack_symbol_type&
  parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 79: // IDENTIFIER
      case 80: // INTCONST
      case 81: // HEXCONST
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  parser::debug_level_type
  parser::debug_level () const
  {
    return yydebug_;
  }

  void
  parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  parser::state_type
  parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  parser::operator() ()
  {
    return parse ();
  }

  int
  parser::parse ()
  {
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

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.type = yytranslate_ (yylex (&yyla.value, &yyla.location));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

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
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 79: // IDENTIFIER
      case 80: // INTCONST
      case 81: // HEXCONST
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 4:
#line 136 "./src/clike/parser.yy"
                      {ast.struct_declaration(yystack_[0].location,yystack_[0].value.as < std::string > ());}
#line 715 "./src/clike/parser.cpp"
    break;

  case 5:
#line 136 "./src/clike/parser.yy"
                                                                                                            {ast.struct_declaration_end();}
#line 721 "./src/clike/parser.cpp"
    break;

  case 8:
#line 154 "./src/clike/parser.yy"
                                                                {ast.function_begin(yystack_[3].location,yystack_[3].value.as < std::string > ());}
#line 727 "./src/clike/parser.cpp"
    break;

  case 9:
#line 154 "./src/clike/parser.yy"
                                                                                                                {ast.function_end();}
#line 733 "./src/clike/parser.cpp"
    break;

  case 10:
#line 155 "./src/clike/parser.yy"
                                                   {ast.function_begin(yystack_[2].location,yystack_[2].value.as < std::string > ());}
#line 739 "./src/clike/parser.cpp"
    break;

  case 11:
#line 155 "./src/clike/parser.yy"
                                                                                                   {ast.function_end();}
#line 745 "./src/clike/parser.cpp"
    break;

  case 13:
#line 203 "./src/clike/parser.yy"
             {ast.type_specifier(yystack_[0].location,yystack_[0].value.as < std::string > (),false);}
#line 751 "./src/clike/parser.cpp"
    break;

  case 14:
#line 204 "./src/clike/parser.yy"
                     {ast.type_specifier(yystack_[1].location,yystack_[0].value.as < std::string > (),true);}
#line 757 "./src/clike/parser.cpp"
    break;

  case 15:
#line 229 "./src/clike/parser.yy"
                                                         {ast.struct_field_declaration();}
#line 763 "./src/clike/parser.cpp"
    break;

  case 20:
#line 280 "./src/clike/parser.yy"
             {ast.direct_declarator(yystack_[0].location,yystack_[0].value.as < std::string > ());}
#line 769 "./src/clike/parser.cpp"
    break;

  case 23:
#line 285 "./src/clike/parser.yy"
                                 {ast.direct_declarator_array_size(yystack_[1].location);}
#line 775 "./src/clike/parser.cpp"
    break;

  case 27:
#line 305 "./src/clike/parser.yy"
                                                                        {ast.ternary_operator(yystack_[4].location);}
#line 781 "./src/clike/parser.cpp"
    break;

  case 29:
#line 312 "./src/clike/parser.yy"
                                                      {ast.binary_operator<ast_binary_logical_or>(yystack_[1].location);}
#line 787 "./src/clike/parser.cpp"
    break;

  case 31:
#line 319 "./src/clike/parser.yy"
                                                          {ast.binary_operator<ast_binary_logical_and>(yystack_[1].location);}
#line 793 "./src/clike/parser.cpp"
    break;

  case 33:
#line 326 "./src/clike/parser.yy"
                                                       {ast.binary_operator<ast_binary_bitwise_or>(yystack_[1].location);}
#line 799 "./src/clike/parser.cpp"
    break;

  case 35:
#line 333 "./src/clike/parser.yy"
                                               {ast.binary_operator<ast_binary_bitwise_xor>(yystack_[1].location);}
#line 805 "./src/clike/parser.cpp"
    break;

  case 37:
#line 340 "./src/clike/parser.yy"
                                           {ast.binary_operator<ast_binary_bitwise_and>(yystack_[1].location);}
#line 811 "./src/clike/parser.cpp"
    break;

  case 39:
#line 348 "./src/clike/parser.yy"
                                                   {ast.binary_operator<ast_binary_inequality_eq>(yystack_[1].location);}
#line 817 "./src/clike/parser.cpp"
    break;

  case 40:
#line 349 "./src/clike/parser.yy"
                                                    {ast.binary_operator<ast_binary_inequality_neq>(yystack_[1].location);}
#line 823 "./src/clike/parser.cpp"
    break;

  case 42:
#line 359 "./src/clike/parser.yy"
                                                 {ast.binary_operator<ast_binary_inequality_lt>(yystack_[1].location);}
#line 829 "./src/clike/parser.cpp"
    break;

  case 43:
#line 360 "./src/clike/parser.yy"
                                                 {ast.binary_operator<ast_binary_inequality_gt>(yystack_[1].location);}
#line 835 "./src/clike/parser.cpp"
    break;

  case 44:
#line 361 "./src/clike/parser.yy"
                                                   {ast.binary_operator<ast_binary_inequality_lte>(yystack_[1].location);}
#line 841 "./src/clike/parser.cpp"
    break;

  case 45:
#line 362 "./src/clike/parser.yy"
                                                   {ast.binary_operator<ast_binary_inequality_gte>(yystack_[1].location);}
#line 847 "./src/clike/parser.cpp"
    break;

  case 47:
#line 370 "./src/clike/parser.yy"
                                                {ast.binary_operator<ast_binary_bitwise_shl>(yystack_[1].location);}
#line 853 "./src/clike/parser.cpp"
    break;

  case 48:
#line 371 "./src/clike/parser.yy"
                                                {ast.binary_operator<ast_binary_bitwise_shr>(yystack_[1].location);}
#line 859 "./src/clike/parser.cpp"
    break;

  case 50:
#line 379 "./src/clike/parser.yy"
                                                       {ast.binary_operator<ast_binary_arith_add>(yystack_[1].location);}
#line 865 "./src/clike/parser.cpp"
    break;

  case 51:
#line 380 "./src/clike/parser.yy"
                                                        {ast.binary_operator<ast_binary_arith_sub>(yystack_[1].location);}
#line 871 "./src/clike/parser.cpp"
    break;

  case 53:
#line 389 "./src/clike/parser.yy"
                                                  {ast.binary_operator<ast_binary_arith_mul>(yystack_[1].location);}
#line 877 "./src/clike/parser.cpp"
    break;

  case 54:
#line 390 "./src/clike/parser.yy"
                                                  {ast.binary_operator<ast_binary_arith_div>(yystack_[1].location);}
#line 883 "./src/clike/parser.cpp"
    break;

  case 55:
#line 391 "./src/clike/parser.yy"
                                                  {ast.binary_operator<ast_binary_arith_mod>(yystack_[1].location);}
#line 889 "./src/clike/parser.cpp"
    break;

  case 58:
#line 409 "./src/clike/parser.yy"
                              {ast.prefix_operator<ast_binary_arith_add>(yystack_[1].location);}
#line 895 "./src/clike/parser.cpp"
    break;

  case 59:
#line 410 "./src/clike/parser.yy"
                                {ast.prefix_operator<ast_binary_arith_sub>(yystack_[1].location);}
#line 901 "./src/clike/parser.cpp"
    break;

  case 60:
#line 411 "./src/clike/parser.yy"
                          {ast.unary_operator<ast_unary_arith_negate>(yystack_[1].location);}
#line 907 "./src/clike/parser.cpp"
    break;

  case 61:
#line 412 "./src/clike/parser.yy"
                          {ast.unary_operator<ast_unary_bitwise_negate>(yystack_[1].location);}
#line 913 "./src/clike/parser.cpp"
    break;

  case 62:
#line 413 "./src/clike/parser.yy"
                         {ast.unary_operator<ast_unary_logical_negate>(yystack_[1].location);}
#line 919 "./src/clike/parser.cpp"
    break;

  case 64:
#line 436 "./src/clike/parser.yy"
                                     {ast.function_call_parameters_end(yystack_[2].location);}
#line 925 "./src/clike/parser.cpp"
    break;

  case 66:
#line 437 "./src/clike/parser.yy"
                                                                  {ast.function_call_parameters_end(yystack_[2].location);}
#line 931 "./src/clike/parser.cpp"
    break;

  case 68:
#line 441 "./src/clike/parser.yy"
                               {ast.postfix_array_index(yystack_[1].location);}
#line 937 "./src/clike/parser.cpp"
    break;

  case 70:
#line 442 "./src/clike/parser.yy"
                   {ast.postfix_dot_identifier(yystack_[0].location,yystack_[0].value.as < std::string > ());}
#line 943 "./src/clike/parser.cpp"
    break;

  case 72:
#line 443 "./src/clike/parser.yy"
             {ast.postfix_operator<ast_binary_arith_add>(yystack_[0].location);}
#line 949 "./src/clike/parser.cpp"
    break;

  case 74:
#line 444 "./src/clike/parser.yy"
               {ast.postfix_operator<ast_binary_arith_sub>(yystack_[0].location);}
#line 955 "./src/clike/parser.cpp"
    break;

  case 77:
#line 449 "./src/clike/parser.yy"
                        {ast.function_call_parameter(yystack_[0].location);}
#line 961 "./src/clike/parser.cpp"
    break;

  case 78:
#line 450 "./src/clike/parser.yy"
                          {ast.function_call_parameter(yystack_[0].location);}
#line 967 "./src/clike/parser.cpp"
    break;

  case 80:
#line 458 "./src/clike/parser.yy"
             {ast.primary_expression_identifier(yystack_[0].location,yystack_[0].value.as < std::string > ());}
#line 973 "./src/clike/parser.cpp"
    break;

  case 83:
#line 468 "./src/clike/parser.yy"
           {ast.primary_expression_constant_suffix(yystack_[0].location,yystack_[0].value.as < std::string > ());}
#line 979 "./src/clike/parser.cpp"
    break;

  case 84:
#line 469 "./src/clike/parser.yy"
             {ast.primary_expression_constant_suffix(yystack_[0].location,yystack_[0].value.as < std::string > ());}
#line 985 "./src/clike/parser.cpp"
    break;

  case 89:
#line 487 "./src/clike/parser.yy"
                                                  {ast.assignment_operator(yystack_[1].location);}
#line 991 "./src/clike/parser.cpp"
    break;

  case 90:
#line 488 "./src/clike/parser.yy"
                                                 {ast.assignment_expression<ast_binary_arith_mul>(yystack_[1].location);}
#line 997 "./src/clike/parser.cpp"
    break;

  case 91:
#line 489 "./src/clike/parser.yy"
                                                 {ast.assignment_expression<ast_binary_arith_div>(yystack_[1].location);}
#line 1003 "./src/clike/parser.cpp"
    break;

  case 92:
#line 490 "./src/clike/parser.yy"
                                                 {ast.assignment_expression<ast_binary_arith_mod>(yystack_[1].location);}
#line 1009 "./src/clike/parser.cpp"
    break;

  case 93:
#line 491 "./src/clike/parser.yy"
                                                  {ast.assignment_expression<ast_binary_arith_add>(yystack_[1].location);}
#line 1015 "./src/clike/parser.cpp"
    break;

  case 94:
#line 492 "./src/clike/parser.yy"
                                                   {ast.assignment_expression<ast_binary_arith_sub>(yystack_[1].location);}
#line 1021 "./src/clike/parser.cpp"
    break;

  case 95:
#line 493 "./src/clike/parser.yy"
                                                    {ast.assignment_expression<ast_binary_bitwise_shl>(yystack_[1].location);}
#line 1027 "./src/clike/parser.cpp"
    break;

  case 96:
#line 494 "./src/clike/parser.yy"
                                                    {ast.assignment_expression<ast_binary_bitwise_shr>(yystack_[1].location);}
#line 1033 "./src/clike/parser.cpp"
    break;

  case 97:
#line 495 "./src/clike/parser.yy"
                                                 {ast.assignment_expression<ast_binary_bitwise_and>(yystack_[1].location);}
#line 1039 "./src/clike/parser.cpp"
    break;

  case 98:
#line 496 "./src/clike/parser.yy"
                                                 {ast.assignment_expression<ast_binary_bitwise_xor>(yystack_[1].location);}
#line 1045 "./src/clike/parser.cpp"
    break;

  case 99:
#line 497 "./src/clike/parser.yy"
                                                {ast.assignment_expression<ast_binary_bitwise_or>(yystack_[1].location);}
#line 1051 "./src/clike/parser.cpp"
    break;

  case 103:
#line 535 "./src/clike/parser.yy"
                                          {ast.parameter_declaration(yystack_[1].location);}
#line 1057 "./src/clike/parser.cpp"
    break;

  case 104:
#line 536 "./src/clike/parser.yy"
                                                     {ast.parameter_declaration(yystack_[1].location);}
#line 1063 "./src/clike/parser.cpp"
    break;

  case 107:
#line 589 "./src/clike/parser.yy"
                                                            {ast.declaration(yystack_[2].location);}
#line 1069 "./src/clike/parser.cpp"
    break;

  case 108:
#line 601 "./src/clike/parser.yy"
                                       {ast.init_declarator(true);}
#line 1075 "./src/clike/parser.cpp"
    break;

  case 109:
#line 602 "./src/clike/parser.yy"
                      {ast.init_declarator(false);}
#line 1081 "./src/clike/parser.cpp"
    break;

  case 113:
#line 615 "./src/clike/parser.yy"
           {ast.initializer_list_begin(yystack_[0].location);}
#line 1087 "./src/clike/parser.cpp"
    break;

  case 115:
#line 616 "./src/clike/parser.yy"
           {ast.initializer_list_begin(yystack_[0].location);}
#line 1093 "./src/clike/parser.cpp"
    break;

  case 117:
#line 622 "./src/clike/parser.yy"
              {ast.initializer_list_element(yystack_[0].location);}
#line 1099 "./src/clike/parser.cpp"
    break;

  case 118:
#line 623 "./src/clike/parser.yy"
                                       {ast.initializer_list_element(yystack_[0].location);}
#line 1105 "./src/clike/parser.cpp"
    break;

  case 119:
#line 630 "./src/clike/parser.yy"
         {ast.scope_begin();}
#line 1111 "./src/clike/parser.cpp"
    break;

  case 120:
#line 630 "./src/clike/parser.yy"
                                                         {ast.scope_end();}
#line 1117 "./src/clike/parser.cpp"
    break;

  case 132:
#line 664 "./src/clike/parser.yy"
                                 {ast.case_statement(yystack_[2].location, yystack_[1].location, false);}
#line 1123 "./src/clike/parser.cpp"
    break;

  case 134:
#line 665 "./src/clike/parser.yy"
                  {ast.case_statement(yystack_[1].location, yystack_[1].location, true);}
#line 1129 "./src/clike/parser.cpp"
    break;

  case 137:
#line 671 "./src/clike/parser.yy"
                         {ast.expression_statement();}
#line 1135 "./src/clike/parser.cpp"
    break;

  case 138:
#line 677 "./src/clike/parser.yy"
                              {ast.conditional_begin(yystack_[3].location,yystack_[1].location);}
#line 1141 "./src/clike/parser.cpp"
    break;

  case 140:
#line 678 "./src/clike/parser.yy"
                                           {ast.switch_begin(yystack_[4].location,yystack_[2].location);}
#line 1147 "./src/clike/parser.cpp"
    break;

  case 141:
#line 678 "./src/clike/parser.yy"
                                                                                                 {ast.switch_end(yystack_[7].location);}
#line 1153 "./src/clike/parser.cpp"
    break;

  case 142:
#line 679 "./src/clike/parser.yy"
                                           {ast.switch_begin(yystack_[4].location,yystack_[2].location);}
#line 1159 "./src/clike/parser.cpp"
    break;

  case 143:
#line 679 "./src/clike/parser.yy"
                                                                             {ast.switch_end(yystack_[6].location);}
#line 1165 "./src/clike/parser.cpp"
    break;

  case 144:
#line 683 "./src/clike/parser.yy"
                 {ast.conditional_else();}
#line 1171 "./src/clike/parser.cpp"
    break;

  case 145:
#line 683 "./src/clike/parser.yy"
                                                     {ast.conditional_end(true);}
#line 1177 "./src/clike/parser.cpp"
    break;

  case 146:
#line 684 "./src/clike/parser.yy"
                           {ast.conditional_end(false);}
#line 1183 "./src/clike/parser.cpp"
    break;

  case 147:
#line 703 "./src/clike/parser.yy"
        {ast.iteration_begin();}
#line 1189 "./src/clike/parser.cpp"
    break;

  case 148:
#line 703 "./src/clike/parser.yy"
                                                          {ast.iteration_statements(yystack_[2].location,true,false);}
#line 1195 "./src/clike/parser.cpp"
    break;

  case 149:
#line 703 "./src/clike/parser.yy"
                                                                                                               {ast.iteration_end(true);}
#line 1201 "./src/clike/parser.cpp"
    break;

  case 150:
#line 704 "./src/clike/parser.yy"
       {ast.iteration_begin();}
#line 1207 "./src/clike/parser.cpp"
    break;

  case 151:
#line 704 "./src/clike/parser.yy"
                                                                         {ast.iteration_statements(yystack_[2].location,true,false);}
#line 1213 "./src/clike/parser.cpp"
    break;

  case 152:
#line 704 "./src/clike/parser.yy"
                                                                                                                              {ast.iteration_end(false);}
#line 1219 "./src/clike/parser.cpp"
    break;

  case 153:
#line 705 "./src/clike/parser.yy"
                                                     {ast.iteration_statements(yystack_[4].location,false,false);}
#line 1225 "./src/clike/parser.cpp"
    break;

  case 154:
#line 705 "./src/clike/parser.yy"
                                                                                                           {ast.iteration_end(true);}
#line 1231 "./src/clike/parser.cpp"
    break;

  case 155:
#line 706 "./src/clike/parser.yy"
                                                                {ast.iteration_statements(yystack_[5].location,false,true);}
#line 1237 "./src/clike/parser.cpp"
    break;

  case 156:
#line 706 "./src/clike/parser.yy"
                                                                                                                     {ast.iteration_end(true);}
#line 1243 "./src/clike/parser.cpp"
    break;

  case 157:
#line 707 "./src/clike/parser.yy"
                                                                {ast.iteration_statements(yystack_[2].location,true,false);}
#line 1249 "./src/clike/parser.cpp"
    break;

  case 158:
#line 707 "./src/clike/parser.yy"
                                                                                                                     {ast.iteration_end(true);}
#line 1255 "./src/clike/parser.cpp"
    break;

  case 159:
#line 708 "./src/clike/parser.yy"
                                                                           {ast.iteration_statements(yystack_[3].location,true,true);}
#line 1261 "./src/clike/parser.cpp"
    break;

  case 160:
#line 708 "./src/clike/parser.yy"
                                                                                                                               {ast.iteration_end(true);}
#line 1267 "./src/clike/parser.cpp"
    break;

  case 161:
#line 712 "./src/clike/parser.yy"
      {ast.iteration_begin();}
#line 1273 "./src/clike/parser.cpp"
    break;

  case 162:
#line 720 "./src/clike/parser.yy"
                     {ast.continue_statement(yystack_[1].location);}
#line 1279 "./src/clike/parser.cpp"
    break;

  case 163:
#line 721 "./src/clike/parser.yy"
                    {ast.break_statement(yystack_[1].location);}
#line 1285 "./src/clike/parser.cpp"
    break;

  case 164:
#line 722 "./src/clike/parser.yy"
                                {ast.return_statement(yystack_[2].location,yystack_[1].location);}
#line 1291 "./src/clike/parser.cpp"
    break;


#line 1295 "./src/clike/parser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
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
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

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
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
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
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
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
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
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
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
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
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
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
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
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


  const short parser::yypact_ninf_ = -244;

  const short parser::yytable_ninf_ = -143;

  const short
  parser::yypact_[] =
  {
     -19,   -73,   -71,  -244,    38,   -19,  -244,  -244,   -28,  -244,
    -244,  -244,  -244,  -244,    54,    67,    48,   -21,  -244,    -9,
      41,  -244,    36,   -21,   114,   128,   -21,  -244,  -244,  -244,
     -21,  -244,   149,   126,  -244,   150,   151,  -244,   147,   162,
     152,  -244,   128,  -244,    36,  -244,  -244,   248,   166,   321,
    -244,  -244,  -244,  -244,   321,   321,   321,   321,   321,   321,
    -244,  -244,  -244,   176,   178,   170,   321,   171,   321,   181,
     110,  -244,  -244,    36,  -244,    25,   167,   163,   160,   173,
      56,   121,    37,     8,    19,  -244,   377,  -244,   116,  -244,
     195,   196,  -244,  -244,  -244,  -244,   161,  -244,  -244,  -244,
    -244,   190,  -244,  -244,  -244,   188,  -244,  -244,  -244,   191,
    -244,  -244,  -244,   248,   193,  -244,  -244,   321,   202,  -244,
     321,   213,  -244,   203,   222,   225,   321,   321,   321,   321,
     321,   321,   321,   321,   321,   321,   321,   321,   321,   321,
     321,   321,   321,   321,   321,   321,   321,   321,   321,   321,
     321,   321,   321,   321,   321,   321,   153,    97,   321,  -244,
    -244,  -244,  -244,   321,  -244,  -244,  -244,    40,  -244,  -244,
     180,   321,   217,  -244,   219,  -244,   248,   301,    36,  -244,
     229,   167,   163,   160,   173,    56,   121,   121,    37,    37,
      37,    37,     8,     8,    19,    19,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,   221,   230,   223,   109,   109,   196,    33,   152,
     224,   231,   227,   248,  -244,  -244,   232,  -244,  -244,  -244,
     321,   109,   109,  -244,   237,  -244,  -244,  -244,  -244,   306,
     242,  -244,   321,  -244,   235,  -244,   248,   236,   301,  -244,
    -244,  -244,   109,   321,   109,  -244,   241,   312,   246,   248,
     248,   239,   200,  -244,  -244,  -244,     5,  -244,  -244,  -244,
     248,  -244,  -244,   256,  -244,  -244,   214,  -244,  -244,   301,
    -244,  -244,   248,   248,  -244,   245,  -244,   248,  -244,  -244,
    -244,   248,  -244,  -244,  -244
  };

  const unsigned char
  parser::yydefact_[] =
  {
       0,     0,     0,    13,     0,     6,     2,     3,     0,    12,
      14,     4,     1,     7,     0,     0,     0,     0,    10,     0,
       0,   101,     0,    17,     0,     0,     0,    20,   103,   104,
       0,     8,     0,    18,    16,     0,   119,    11,     0,   100,
      22,   102,     0,    15,     0,     5,   121,     0,   105,     0,
      21,     9,    19,   136,     0,     0,     0,     0,     0,     0,
     161,   150,   147,     0,     0,     0,     0,     0,     0,     0,
      80,    83,    84,     0,    88,    26,    28,    30,    32,    34,
      36,    38,    41,    46,    49,    52,    56,    57,    76,    81,
       0,    87,   128,   124,   131,   122,     0,   123,   129,   125,
     126,     0,   127,   106,    80,     0,    62,    56,    61,     0,
      58,    59,    60,     0,     0,   162,   163,     0,     0,    25,
       0,     0,   134,   109,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    72,
      74,    63,   137,     0,    85,   120,   130,     0,    23,    82,
       0,     0,     0,   132,     0,   164,     0,     0,     0,   107,
       0,    29,    31,    33,    35,    37,    40,    39,    42,    44,
      43,    45,    47,    48,    50,    51,    53,    54,    55,    89,
      97,    95,    96,    99,    98,    93,    94,    90,    91,    92,
      70,    64,     0,    77,     0,    76,    76,    87,     0,    22,
       0,     0,     0,     0,   138,   135,   115,   112,   108,   110,
       0,    76,    76,    66,     0,    68,    73,    75,    86,     0,
       0,    24,     0,   148,   140,   133,     0,     0,     0,    27,
      71,    65,    76,     0,    76,   153,     0,     0,     0,     0,
       0,     0,   146,   139,   114,   117,     0,    67,    79,    69,
       0,   155,   157,     0,   151,   149,     0,   143,   144,     0,
     116,   154,     0,     0,   159,     0,   141,     0,   118,   156,
     158,     0,   152,   145,   160
  };

  const short
  parser::yypgoto_[] =
  {
    -244,  -244,  -244,  -244,   266,  -244,  -244,  -244,   333,  -244,
    -244,   250,   233,   -16,  -244,    57,  -244,  -244,   -64,  -244,
     154,   155,   156,   148,   158,     2,    23,    11,     6,   -39,
     -45,  -244,  -244,  -244,  -114,  -244,  -244,  -244,  -244,    26,
    -244,  -244,  -244,   -49,    63,  -123,  -244,   260,   252,   243,
    -244,  -244,   112,  -243,  -244,  -244,  -244,    10,  -244,   -95,
     125,    44,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,  -244,
    -244,  -244,  -244
  };

  const short
  parser::yydefgoto_[] =
  {
      -1,     4,     5,    15,     6,     7,    42,    25,    73,     9,
      23,    24,    32,    33,    40,    50,   219,   118,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,   232,   252,   161,   254,   231,   215,   216,   212,
     234,    88,    89,    90,   164,    91,    38,    20,    21,    29,
      92,   124,   125,   228,   247,   248,   266,    93,    47,    94,
      95,    96,    97,   223,   176,    98,    99,   246,   260,   261,
     263,   287,   100,   114,   259,   113,   285,   270,   282,   283,
     291,   101,   102
  };

  const short
  parser::yytable_[] =
  {
     105,   166,   119,    28,    26,   265,    10,   109,    11,   107,
     107,   279,   110,   111,   107,   106,   108,   280,   170,   121,
     112,   107,   199,   200,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   126,   213,    37,   288,   239,    12,     1,
     217,     1,    54,    55,    53,   140,    56,    30,   141,    54,
      55,    14,    51,    56,   227,    31,   127,   123,     3,     2,
       3,   142,    18,   143,   138,   144,   139,    16,   172,    57,
      27,   174,    58,    59,   132,   133,    57,   180,    17,    58,
      59,   225,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
       1,   236,   237,   196,   197,   198,    54,    55,     1,   214,
      56,   211,   104,    71,    72,    27,   156,   250,   251,    70,
      71,    72,   221,   156,   158,   227,    35,     3,   245,   157,
     213,   158,    44,    57,   186,   187,    58,    59,   267,    36,
     269,   134,   135,   136,   137,   159,   194,   195,   160,   192,
     193,   262,   159,    43,    45,   160,   227,   188,   189,   190,
     191,    48,   123,    46,   275,    53,   249,    49,    30,   240,
      54,    55,    36,   165,    56,   281,   104,    71,    72,    26,
     115,   166,   116,   117,   120,   107,   122,   289,   290,   -13,
     256,   128,   293,   258,   130,   129,   294,    57,   131,   162,
      58,    59,   163,   167,   168,   169,   171,   173,   273,    60,
      61,    62,    63,    64,    65,    66,    67,   175,    53,    68,
     177,     1,    69,    54,    55,    36,   286,    56,   178,   179,
     220,   222,   210,   224,   230,   233,   -78,   242,   244,   235,
      70,    71,    72,   253,  -113,   243,   257,  -142,   264,   292,
      57,   277,    53,    58,    59,   271,   278,    54,    55,    36,
     274,    56,    60,    61,    62,    63,    64,    65,    66,    67,
     284,    13,    68,    34,     1,    69,   241,    52,   184,   268,
     238,   181,    41,   182,    57,   183,    39,    58,    59,   185,
     229,   103,   218,    70,    71,    72,    60,    61,    62,    63,
      64,    65,    66,    67,   276,     0,    68,     0,     1,    69,
      54,    55,   226,     0,    56,    54,    55,     0,     0,    56,
     255,    54,    55,     0,     0,    56,   272,    70,    71,    72,
      54,    55,     0,     8,    56,     0,     0,    57,     8,     0,
      58,    59,    57,     0,     0,    58,    59,     0,    57,    19,
      22,    58,    59,     0,     0,     0,    22,    57,     0,    19,
      58,    59,     0,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     104,    71,    72,     0,     0,   104,    71,    72,     0,     0,
       0,   104,    71,    72,   145,     0,     0,     0,     0,     0,
     104,    71,    72,   146,     0,   147,     0,   148,     0,     0,
     149,     0,   150,     0,     0,   151,     0,     0,   152,     0,
     153,     0,   154,     0,   155
  };

  const short
  parser::yycheck_[] =
  {
      49,    96,    66,    19,    13,   248,    79,    56,    79,    54,
      55,     6,    57,    58,    59,    54,    55,    12,   113,    68,
      59,    66,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   155,     8,   157,    25,   279,     4,     0,    60,
     163,    60,     9,    10,     4,    37,    13,     6,    40,     9,
      10,    79,    42,    13,   177,    14,    31,    73,    79,    78,
      79,    42,    14,    44,    27,    46,    29,    13,   117,    36,
      79,   120,    39,    40,    18,    19,    36,   126,    11,    39,
      40,   176,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
      60,   215,   216,   142,   143,   144,     9,    10,    60,   158,
      13,    14,    79,    80,    81,    79,     7,   231,   232,    79,
      80,    81,   171,     7,    15,   248,    12,    79,   223,    13,
     253,    15,     6,    36,   132,   133,    39,    40,   252,    11,
     254,    20,    21,    22,    23,    36,   140,   141,    39,   138,
     139,   246,    36,     4,     4,    39,   279,   134,   135,   136,
     137,    14,   178,    12,   259,     4,   230,    15,     6,   218,
       9,    10,    11,    12,    13,   270,    79,    80,    81,    13,
       4,   276,     4,    13,    13,   230,     5,   282,   283,    79,
     239,    24,   287,   242,    34,    32,   291,    36,    25,     4,
      39,    40,     6,    13,    16,    14,    13,     5,   257,    48,
      49,    50,    51,    52,    53,    54,    55,     4,     4,    58,
      17,    60,    61,     9,    10,    11,    12,    13,     6,     4,
      50,    14,    79,    14,     5,    14,     6,    13,    11,    16,
      79,    80,    81,     6,    12,    14,     4,    12,    12,     4,
      36,    12,     4,    39,    40,    14,    56,     9,    10,    11,
      14,    13,    48,    49,    50,    51,    52,    53,    54,    55,
      14,     5,    58,    23,    60,    61,   219,    44,   130,   253,
     217,   127,    30,   128,    36,   129,    26,    39,    40,   131,
     178,    48,   167,    79,    80,    81,    48,    49,    50,    51,
      52,    53,    54,    55,   260,    -1,    58,    -1,    60,    61,
       9,    10,    11,    -1,    13,     9,    10,    -1,    -1,    13,
      14,     9,    10,    -1,    -1,    13,    14,    79,    80,    81,
       9,    10,    -1,     0,    13,    -1,    -1,    36,     5,    -1,
      39,    40,    36,    -1,    -1,    39,    40,    -1,    36,    16,
      17,    39,    40,    -1,    -1,    -1,    23,    36,    -1,    26,
      39,    40,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      79,    80,    81,    -1,    -1,    79,    80,    81,    -1,    -1,
      -1,    79,    80,    81,    17,    -1,    -1,    -1,    -1,    -1,
      79,    80,    81,    26,    -1,    28,    -1,    30,    -1,    -1,
      33,    -1,    35,    -1,    -1,    38,    -1,    -1,    41,    -1,
      43,    -1,    45,    -1,    47
  };

  const unsigned char
  parser::yystos_[] =
  {
       0,    60,    78,    79,    84,    85,    87,    88,    91,    92,
      79,    79,     0,    87,    79,    86,    13,    11,    14,    91,
     130,   131,    91,    93,    94,    90,    13,    79,    96,   132,
       6,    14,    95,    96,    94,    12,    11,   140,   129,   130,
      97,   131,    89,     4,     6,     4,    12,   141,    14,    15,
      98,   140,    95,     4,     9,    10,    13,    36,    39,    40,
      48,    49,    50,    51,    52,    53,    54,    55,    58,    61,
      79,    80,    81,    91,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   124,   125,
     126,   128,   133,   140,   142,   143,   144,   145,   148,   149,
     155,   164,   165,   132,    79,   126,   112,   113,   112,   126,
     113,   113,   112,   158,   156,     4,     4,    13,   100,   101,
      13,   126,     5,    96,   134,   135,     8,    31,    24,    32,
      34,    25,    18,    19,    20,    21,    22,    23,    27,    29,
      37,    40,    42,    44,    46,    17,    26,    28,    30,    33,
      35,    38,    41,    43,    45,    47,     7,    13,    15,    36,
      39,   117,     4,     6,   127,    12,   142,    13,    16,    14,
     142,    13,   126,     5,   126,     4,   147,    17,     6,     4,
     126,   103,   104,   105,   106,   107,   108,   108,   109,   109,
     109,   109,   110,   110,   111,   111,   112,   112,   112,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
      79,    14,   122,   128,   126,   120,   121,   128,   143,    99,
      50,   126,    14,   146,    14,   142,    11,   128,   136,   135,
       5,   119,   115,    14,   123,    16,   117,   117,   127,     4,
     126,    98,    13,    14,    11,   142,   150,   137,   138,   101,
     117,   117,   116,     6,   118,    14,   126,     4,   126,   157,
     151,   152,   142,   153,    12,   136,   139,   117,   122,   117,
     160,    14,    14,   126,    14,   142,   144,    12,    56,     6,
      12,   142,   161,   162,    14,   159,    12,   154,   136,   142,
     142,   163,     4,   142,   142
  };

  const unsigned char
  parser::yyr1_[] =
  {
       0,    83,    84,    85,    86,    85,    87,    87,    89,    88,
      90,    88,    91,    92,    92,    93,    94,    94,    95,    95,
      97,    96,    98,    99,    98,   100,   101,   101,   102,   102,
     103,   103,   104,   104,   105,   105,   106,   106,   107,   107,
     107,   108,   108,   108,   108,   108,   109,   109,   109,   110,
     110,   110,   111,   111,   111,   111,   112,   113,   113,   113,
     113,   113,   113,   114,   115,   114,   116,   114,   118,   117,
     119,   117,   120,   117,   121,   117,   117,   122,   123,   122,
     124,   124,   124,   125,   125,   126,   127,   127,   128,   128,
     128,   128,   128,   128,   128,   128,   128,   128,   128,   128,
     129,   130,   130,   131,   131,   132,   132,   133,   134,   134,
     135,   135,   136,   137,   136,   138,   136,   139,   139,   141,
     140,   140,   142,   142,   142,   142,   142,   142,   143,   143,
     144,   144,   146,   145,   147,   145,   148,   148,   150,   149,
     151,   149,   152,   149,   154,   153,   153,   156,   157,   155,
     158,   159,   155,   160,   155,   161,   155,   162,   155,   163,
     155,   164,   165,   165,   165
  };

  const signed char
  parser::yyr2_[] =
  {
       0,     2,     1,     1,     0,     7,     1,     2,     0,     7,
       0,     6,     1,     1,     2,     3,     2,     1,     1,     3,
       0,     3,     0,     0,     5,     1,     1,     5,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     3,     1,     3,
       3,     1,     3,     3,     3,     3,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     3,     1,     1,     2,     2,
       2,     2,     2,     2,     0,     5,     0,     6,     0,     5,
       0,     4,     0,     3,     0,     3,     0,     1,     0,     4,
       1,     1,     3,     1,     1,     2,     3,     0,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     3,     2,     2,     3,     4,     3,     3,     1,
       3,     1,     1,     0,     3,     0,     4,     1,     3,     0,
       4,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     0,     5,     0,     4,     1,     2,     0,     6,
       0,     8,     0,     7,     0,     4,     1,     0,     0,     7,
       0,     0,     9,     0,     7,     0,     8,     0,     8,     0,
       9,     1,     2,     2,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const parser::yytname_[] =
  {
  "$end", "error", "$undefined", "SYMBOL", "SEMICOLON", "COLON", "COMMA",
  "DOT", "QMARK", "BANG", "TILDE", "LBRACE", "RBRACE", "LPAREN", "RPAREN",
  "LBRACKET", "RBRACKET", "EQUALS", "NOTEQ", "EQEQ", "LTHAN", "LTHANEQ",
  "GTHAN", "GTHANEQ", "ANDAND", "AND", "ANDEQ", "LSHIFT", "LSHIFTEQ",
  "RSHIFT", "RSHIFTEQ", "OROR", "OR", "OREQ", "XOR", "XOREQ", "PLUSPLUS",
  "PLUS", "PLUSEQ", "MINUSMINUS", "MINUS", "MINUSEQ", "MUL", "MULEQ",
  "DIV", "DIVEQ", "MOD", "MODEQ", "FOR", "DO", "WHILE", "CONTINUE",
  "BREAK", "SWITCH", "CASE", "IF", "ELSE", "GOTO", "RETURN", "AUTO",
  "CONST", "DEFAULT", "EXTERN", "REGISTER", "STATIC", "TYPEDEF", "SIZEOF",
  "VOLATILE", "SIGNED", "UNSIGNED", "LONG", "SHORT", "VOID", "BOOL",
  "CHAR", "INT", "FLOAT", "DOUBLE", "STRUCT", "IDENTIFIER", "INTCONST",
  "HEXCONST", "NOELSE", "$accept", "translation_unit",
  "external_declaration", "$@1", "multiple_external_declarations",
  "function_definition", "$@2", "$@3", "declaration_specifier",
  "type_specifier", "struct_declaration", "multiple_struct_declarations",
  "struct_declarator_list", "direct_declarator", "$@4",
  "direct_declarator_prime", "$@5", "constant_expression",
  "conditional_expression", "logical_or_expression",
  "logical_and_expression", "inclusive_or_expression",
  "exclusive_or_expression", "and_expression", "equality_expression",
  "relational_expression", "shift_expression", "additive_expression",
  "multiplicative_expression", "cast_expression", "unary_expression",
  "postfix_expression", "$@6", "$@7", "optional_postfix_expression", "$@8",
  "$@9", "$@10", "$@11", "function_call_parameter_list", "$@12",
  "primary_expression", "constant", "expression", "expression_prime",
  "assignment_expression", "parameter_type_list", "parameter_list",
  "parameter_declaration", "direct_abstract_declarator", "declaration",
  "init_declarator", "multiple_init_declarators", "initializer", "$@13",
  "$@14", "initializer_list", "compound_statement", "$@15", "statement",
  "basic_statement", "multiple_statements", "labeled_statement", "$@16",
  "$@17", "expression_statement", "selection_statement", "$@18", "$@19",
  "$@20", "selection_rest", "$@21", "iteration_statement", "$@22", "$@23",
  "$@24", "$@25", "$@26", "$@27", "$@28", "$@29", "for_loop",
  "jump_statement", YY_NULLPTR
  };

#if YYDEBUG
  const short
  parser::yyrline_[] =
  {
       0,   129,   129,   135,   136,   136,   141,   142,   154,   154,
     155,   155,   163,   203,   204,   229,   234,   235,   244,   245,
     280,   280,   284,   285,   285,   298,   304,   305,   311,   312,
     318,   319,   325,   326,   332,   333,   339,   340,   347,   348,
     349,   358,   359,   360,   361,   362,   369,   370,   371,   378,
     379,   380,   388,   389,   390,   391,   397,   408,   409,   410,
     411,   412,   413,   435,   436,   436,   437,   437,   441,   441,
     442,   442,   443,   443,   444,   444,   445,   449,   450,   450,
     458,   459,   460,   468,   469,   475,   479,   480,   486,   487,
     488,   489,   490,   491,   492,   493,   494,   495,   496,   497,
     520,   527,   528,   535,   536,   554,   555,   589,   601,   602,
     606,   607,   614,   615,   615,   616,   616,   622,   623,   630,
     630,   631,   641,   642,   643,   644,   645,   646,   650,   651,
     655,   656,   664,   664,   665,   665,   670,   671,   677,   677,
     678,   678,   679,   679,   683,   683,   684,   703,   703,   703,
     704,   704,   704,   705,   705,   706,   706,   707,   707,   708,
     708,   712,   720,   721,   722
  };

  // Print the state stack on the debug stream.
  void
  parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  parser::token_number_type
  parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82
    };
    const int user_token_number_max_ = 337;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

#line 5 "./src/clike/parser.yy"
} // clike
#line 1994 "./src/clike/parser.cpp"

#line 725 "./src/clike/parser.yy"

