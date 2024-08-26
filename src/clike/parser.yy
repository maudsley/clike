%skeleton "lalr1.cc"
%require "3.0"

%defines
%define api.namespace {clike}
%define parser_class_name {parser}
%define api.value.type variant
%define parse.assert
%define parse.trace
%define parse.error verbose

%code requires {
  namespace clike {
    class lexer;
    class syntax_tree_builder;
  }
}

%locations
%parse-param {clike::lexer& lexer}
%parse-param {clike::syntax_tree_builder& ast}

%{
#include "ast_builder.h"
#include "lexer.h"
#undef yylex
#define yylex lexer.yylex

#include <cstdio>
#include <iostream>
%}

%token SYMBOL /* default rule */

%token SEMICOLON
%token COLON
%token COMMA
%token DOT
%token QMARK
%token BANG
%token TILDE

%token LBRACE
%token RBRACE
%token LPAREN
%token RPAREN
%token LBRACKET
%token RBRACKET

%token EQUALS
%token NOTEQ
%token EQEQ
%token LTHAN
%token LTHANEQ
%token GTHAN
%token GTHANEQ

%token ANDAND
%token AND
%token ANDEQ
%token LSHIFT
%token LSHIFTEQ
%token RSHIFT
%token RSHIFTEQ
%token OROR
%token OR
%token OREQ
%token XOR
%token XOREQ
%token PLUSPLUS
%token PLUS
%token PLUSEQ
%token MINUSMINUS
%token MINUS
%token MINUSEQ
%token MUL
%token MULEQ
%token DIV
%token DIVEQ
%token MOD
%token MODEQ

%token FOR
%token DO
%token WHILE
%token CONTINUE
%token BREAK
%token SWITCH
%token CASE
%token IF
%token ELSE
%token GOTO
%token RETURN

%token AUTO
%token CONST
%token DEFAULT
%token EXTERN
%token REGISTER
%token STATIC
%token TYPEDEF
%token SIZEOF

%token VOLATILE
%token SIGNED
%token UNSIGNED
%token LONG
%token SHORT
%token VOID
%token BOOL
%token CHAR
%token INT
%token FLOAT
%token DOUBLE

%token STRUCT

%token <std::string> IDENTIFIER
%token <std::string> INTCONST
%token <std::string> HEXCONST

%nonassoc NOELSE
%nonassoc ELSE

%%

//<translation-unit> ::= {<external-declaration>}*
translation_unit:
  multiple_external_declarations
  ;

//<external-declaration> ::= <function-definition>
//                         | <declaration>
external_declaration:
  function_definition
  | STRUCT IDENTIFIER {ast.struct_declaration(@2,$2);} LBRACE multiple_struct_declarations RBRACE SEMICOLON {ast.struct_declaration_end();}
//  | declaration
  ;

multiple_external_declarations:
  external_declaration
  | external_declaration multiple_external_declarations
  ;

//<function-definition> ::= {<declaration-specifier>}* <declarator> {<declaration>}* <compound-statement>
//function_definition:
  //direct_declarator compound_statement
  //| direct_declarator multiple_declarations compound_statement
  //| multiple_declaration_specifiers direct_declarator compound_statement
  //| multiple_declaration_specifiers direct_declarator multiple_declarations compound_statement
  //;

function_definition:
  declaration_specifier IDENTIFIER LPAREN parameter_list RPAREN {ast.function_begin(@2,$2);} compound_statement {ast.function_end();}
  | declaration_specifier IDENTIFIER LPAREN RPAREN {ast.function_begin(@2,$2);} compound_statement {ast.function_end();}
  ;

//<declaration-specifier> ::= <storage-class-specifier>
//                          | <type-specifier>
//                          | <type-qualifier>
declaration_specifier:
//  multiple_storage_class_specifiers type_specifier
  type_specifier
  ;

//<declarator> ::= {<pointer>}? <direct-declarator>
//declarator:
//  // no pointers
//  direct_declarator
//  ;

//<storage-class-specifier> ::= auto
//                            | register
//                            | static
//                            | extern
//                            | typedef
//storage_class_specifier:
  //AUTO
  //| REGISTER
  //| STATIC
  //| EXTERN
  //| TYPEDEF
  //;

//multiple_storage_class_specifiers:
  //storage_class_specifier multiple_storage_class_specifiers
  //| storage_class_specifier
  //;

//<type-specifier> ::= void
//                   | char
//                   | short
//                   | int
//                   | long
//                   | float
//                   | double
//                   | signed
//                   | unsigned
//                   | <struct-or-union-specifier>
//                   | <enum-specifier>
//                   | <typedef-name>
type_specifier:
  IDENTIFIER {ast.type_specifier(@1,$1,false);}
  | CONST IDENTIFIER {ast.type_specifier(@1,$2,true);}
//  numeric_type_specifier // done
//  | STRUCT IDENTIFIER {ast.struct_identifier($2);}
//  | VOID
//  | STRUCT IDENTIFIER LBRACE multiple_struct_declarations RBRACE
//  | enum_specifier
  ;

//<struct-or-union-specifier> ::= <struct-or-union> <identifier> { {<struct-declaration>}+ }
//                              | <struct-or-union> { {<struct-declaration>}+ }
//                              | <struct-or-union> <identifier>
//struct_or_union_specifier:
//  STRUCT IDENTIFIER LBRACE multiple_struct_declarations RBRACE
//  | STRUCT LBRACE multiple_struct_declarations RBRACE
//  | STRUCT IDENTIFIER
//  ;

//<struct-or-union> ::= struct
//                    | union
//struct_or_union:
//  STRUCT
//  ;

//<struct-declaration> ::= {<specifier-qualifier>}* <struct-declarator-list>
struct_declaration:
  declaration_specifier struct_declarator_list SEMICOLON {ast.struct_field_declaration();}
//  | struct_declarator_list SEMICOLON {ast.wont_implement(@1);}
  ;

multiple_struct_declarations:
  struct_declaration multiple_struct_declarations
  | struct_declaration
  ;

//<specifier-qualifier> ::= <type-specifier>
//                        | <type-qualifier>

//<struct-declarator-list> ::= <struct-declarator>
//                           | <struct-declarator-list> , <struct-declarator>
struct_declarator_list:
  direct_declarator // done
  | direct_declarator COMMA struct_declarator_list
  ;

//<struct-declarator> ::= <declarator>
//                      | <declarator> : <constant-expression>
//                      | : <constant-expression>
//struct_declarator:
//  direct_declarator
//  | direct_declarator COLON constant_expression
//  | COLON constant_expression
//  ;

//<type-qualifier> ::= const
//                   | volatile
//type_qualifier:
  //CONST {ast.wont_implement(@1);}
  //| VOLATILE  {ast.wont_implement(@1);}
  //;

//multiple_type_qualifiers:
  //type_qualifier multiple_type_qualifiers
  //| type_qualifier
  //;

//multiple_specifier_qualifiers:
  //type_specifier
  //| multiple_type_qualifiers type_specifier
  //;

//<direct-declarator> ::= <identifier>
//                      | ( <declarator> )
//                      | <direct-declarator> [ {<constant-expression>}? ]
//                      | <direct-declarator> ( <parameter-type-list> )
//                      | <direct-declarator> ( {<identifier>}* )
direct_declarator:
  IDENTIFIER {ast.direct_declarator(@1,$1);} direct_declarator_prime
  ;

direct_declarator_prime:
  %empty
  | LBRACKET expression RBRACKET {ast.direct_declarator_array_size(@2);} direct_declarator_prime
//  | LPAREN parameter_type_list RPAREN direct_declarator_prime {ast.wont_implement(@1);}
//  | LPAREN RPAREN direct_declarator_prime {ast.wont_implement(@1);}
//  | LPAREN multiple_identifiers RPAREN direct_declarator_prime {ast.wont_implement(@1);}
  ;

//multiple_identifiers:
  //IDENTIFIER multiple_identifiers
  //| IDENTIFIER
  //;

//<constant-expression> ::= <conditional-expression>
constant_expression:
  conditional_expression
  ;

//<conditional-expression> ::= <logical-or-expression>
//                           | <logical-or-expression> ? <expression> : <conditional-expression>
conditional_expression:
  logical_or_expression
  | logical_or_expression QMARK expression COLON conditional_expression {ast.ternary_operator(@1);}
  ;

//<logical-or-expression> ::= <logical-and-expression>
//                          | <logical-or-expression> || <logical-and-expression>
logical_or_expression:
  logical_and_expression
  | logical_or_expression OROR logical_and_expression {ast.binary_operator<ast_binary_logical_or>(@2);}
  ;

//<logical-and-expression> ::= <inclusive-or-expression>
//                           | <logical-and-expression> && <inclusive-or-expression>
logical_and_expression:
  inclusive_or_expression
  | logical_and_expression ANDAND inclusive_or_expression {ast.binary_operator<ast_binary_logical_and>(@2);}
  ;

//<inclusive-or-expression> ::= <exclusive-or-expression>
//                            | <inclusive-or-expression> | <exclusive-or-expression>
inclusive_or_expression:
  exclusive_or_expression
  | inclusive_or_expression OR exclusive_or_expression {ast.binary_operator<ast_binary_bitwise_or>(@2);}
  ;

//<exclusive-or-expression> ::= <and-expression>
//                            | <exclusive-or-expression> ^ <and-expression>
exclusive_or_expression:
  and_expression
  | exclusive_or_expression XOR and_expression {ast.binary_operator<ast_binary_bitwise_xor>(@2);}
  ;

//<and-expression> ::= <equality-expression>
//                   | <and-expression> & <equality-expression>
and_expression:
  equality_expression
  | and_expression AND equality_expression {ast.binary_operator<ast_binary_bitwise_and>(@2);}
  ;

//<equality-expression> ::= <relational-expression>
//                        | <equality-expression> == <relational-expression>
//                        | <equality-expression> != <relational-expression>
equality_expression:
  relational_expression
  | equality_expression EQEQ relational_expression {ast.binary_operator<ast_binary_inequality_eq>(@2);}
  | equality_expression NOTEQ relational_expression {ast.binary_operator<ast_binary_inequality_neq>(@2);}
  ;

//<relational-expression> ::= <shift-expression>
//                          | <relational-expression> < <shift-expression>
//                          | <relational-expression> > <shift-expression>
//                          | <relational-expression> <= <shift-expression>
//                          | <relational-expression> >= <shift-expression>
relational_expression:
  shift_expression
  | relational_expression LTHAN shift_expression {ast.binary_operator<ast_binary_inequality_lt>(@2);}
  | relational_expression GTHAN shift_expression {ast.binary_operator<ast_binary_inequality_gt>(@2);}
  | relational_expression LTHANEQ shift_expression {ast.binary_operator<ast_binary_inequality_lte>(@2);}
  | relational_expression GTHANEQ shift_expression {ast.binary_operator<ast_binary_inequality_gte>(@2);}
  ;

//<shift-expression> ::= <additive-expression>
//                     | <shift-expression> << <additive-expression>
//                     | <shift-expression> >> <additive-expression>
shift_expression:
  additive_expression
  | shift_expression LSHIFT additive_expression {ast.binary_operator<ast_binary_bitwise_shl>(@2);}
  | shift_expression RSHIFT additive_expression {ast.binary_operator<ast_binary_bitwise_shr>(@2);}
  ;

//<additive-expression> ::= <multiplicative-expression>
//                        | <additive-expression> + <multiplicative-expression>
//                        | <additive-expression> - <multiplicative-expression>
additive_expression:
  multiplicative_expression
  | additive_expression PLUS multiplicative_expression {ast.binary_operator<ast_binary_arith_add>(@2);}
  | additive_expression MINUS multiplicative_expression {ast.binary_operator<ast_binary_arith_sub>(@2);}
  ;

//<multiplicative-expression> ::= <cast-expression>
//                              | <multiplicative-expression> * <cast-expression>
//                              | <multiplicative-expression> / <cast-expression>
//                              | <multiplicative-expression> % <cast-expression>
multiplicative_expression:
  cast_expression
  | multiplicative_expression MUL cast_expression {ast.binary_operator<ast_binary_arith_mul>(@2);}
  | multiplicative_expression DIV cast_expression {ast.binary_operator<ast_binary_arith_div>(@2);}
  | multiplicative_expression MOD cast_expression {ast.binary_operator<ast_binary_arith_mod>(@2);}
  ;

//<cast-expression> ::= <unary-expression>
//                    | ( <type-name> ) <cast-expression>
cast_expression:
  unary_expression
//  | LPAREN type_name RPAREN cast_expression {ast.wont_implement(@1);}
  ;

//<unary-expression> ::= <postfix-expression>
//                     | ++ <unary-expression>
//                     | -- <unary-expression>
//                     | <unary-operator> <cast-expression>
//                     | sizeof <unary-expression>
//                     | sizeof <type-name>
unary_expression:
  postfix_expression
  | PLUSPLUS unary_expression {ast.prefix_operator<ast_binary_arith_add>(@1);}
  | MINUSMINUS unary_expression {ast.prefix_operator<ast_binary_arith_sub>(@1);}
  | MINUS cast_expression {ast.unary_operator<ast_unary_arith_negate>(@1);}
  | TILDE cast_expression {ast.unary_operator<ast_unary_bitwise_negate>(@1);}
  | BANG cast_expression {ast.unary_operator<ast_unary_logical_negate>(@1);}
  ;

//<postfix-expression> ::= <primary-expression>
//                       | <postfix-expression> [ <expression> ]
//                       | <postfix-expression> ( {<assignment-expression>}* )
//                       | <postfix-expression> . <identifier>
//                       | <postfix-expression> -> <identifier>
//                       | <postfix-expression> ++
//                       | <postfix-expression> --
//postfix_expression:
//  primary_expression
//  | postfix_expression LBRACKET expression RBRACKET
//  | postfix_expression LPAREN RPAREN
//  | postfix_expression LPAREN function_call_parameter_list RPAREN
//  | postfix_expression DOT IDENTIFIER
//  | postfix_expression MINUS GTHAN IDENTIFIER
//  | postfix_expression PLUSPLUS
//  | postfix_expression MINUSMINUS
//  ;

postfix_expression:
  primary_expression optional_postfix_expression
  | primary_expression LPAREN RPAREN {ast.function_call_parameters_end(@1);} optional_postfix_expression
  | primary_expression LPAREN function_call_parameter_list RPAREN {ast.function_call_parameters_end(@2);} optional_postfix_expression
  ;

optional_postfix_expression:
  LBRACKET expression RBRACKET {ast.postfix_array_index(@2);} optional_postfix_expression
  | DOT IDENTIFIER {ast.postfix_dot_identifier(@2,$2);} optional_postfix_expression
  | PLUSPLUS {ast.postfix_operator<ast_binary_arith_add>(@1);} optional_postfix_expression
  | MINUSMINUS {ast.postfix_operator<ast_binary_arith_sub>(@1);} optional_postfix_expression
  | %empty
  ;

function_call_parameter_list:
  assignment_expression {ast.function_call_parameter(@1);}
  | assignment_expression {ast.function_call_parameter(@1);} COMMA function_call_parameter_list
  ;

//<primary-expression> ::= <identifier>
//                       | <constant>
//                       | <string>
//                       | ( <expression> )
primary_expression:
  IDENTIFIER {ast.primary_expression_identifier(@1,$1);}
  | constant // done
  | LPAREN expression RPAREN
  ;

//<constant> ::= <integer-constant>
//             | <character-constant>
//             | <floating-constant>
//             | <enumeration-constant>
constant:
  INTCONST {ast.primary_expression_constant_suffix(@1,$1);}
  | HEXCONST {ast.primary_expression_constant_suffix(@1,$1);}
  ;

//<expression> ::= <assignment-expression>
//               | <expression> , <assignment-expression>
expression:
  assignment_expression expression_prime
  ;

expression_prime:
  COMMA assignment_expression expression_prime
  | %empty
  ;

//<assignment-expression> ::= <conditional-expression>
//                          | <unary-expression> <assignment-operator> <assignment-expression>
assignment_expression:
  conditional_expression
  | unary_expression EQUALS assignment_expression {ast.assignment_operator(@2);}
  | unary_expression MULEQ assignment_expression {ast.assignment_expression<ast_binary_arith_mul>(@2);}
  | unary_expression DIVEQ assignment_expression {ast.assignment_expression<ast_binary_arith_div>(@2);}
  | unary_expression MODEQ assignment_expression {ast.assignment_expression<ast_binary_arith_mod>(@2);}
  | unary_expression PLUSEQ assignment_expression {ast.assignment_expression<ast_binary_arith_add>(@2);}
  | unary_expression MINUSEQ assignment_expression {ast.assignment_expression<ast_binary_arith_sub>(@2);}
  | unary_expression LSHIFTEQ assignment_expression {ast.assignment_expression<ast_binary_bitwise_shl>(@2);}
  | unary_expression RSHIFTEQ assignment_expression {ast.assignment_expression<ast_binary_bitwise_shr>(@2);}
  | unary_expression ANDEQ assignment_expression {ast.assignment_expression<ast_binary_bitwise_and>(@2);}
  | unary_expression XOREQ assignment_expression {ast.assignment_expression<ast_binary_bitwise_xor>(@2);}
  | unary_expression OREQ assignment_expression {ast.assignment_expression<ast_binary_bitwise_or>(@2);}
  ;

//<assignment-operator> ::= =
//                        | *=
//                        | /=
//                        | %=
//                        | +=
//                        | -=
//                        | <<=
//                        | >>=
//                        | &=
//                        | ^=
//                        | |=

//<type-name> ::= {<specifier-qualifier>}+ {<abstract-declarator>}?
//type_name:
  //multiple_specifier_qualifiers direct_abstract_declarator
  //;

//<parameter-type-list> ::= <parameter-list>
//                        | <parameter-list> , ...
parameter_type_list:
  parameter_list
//  | parameter_list COMMA LDOTS
  ;

//<parameter-list> ::= <parameter-declaration>
//                   | <parameter-list> , <parameter-declaration>
parameter_list:
  parameter_declaration 
  | parameter_list COMMA parameter_declaration
  ;

//<parameter-declaration> ::= {<declaration-specifier>}+ <declarator>
//                          | {<declaration-specifier>}+ <abstract-declarator>
//                          | {<declaration-specifier>}+
parameter_declaration:
  declaration_specifier direct_declarator {ast.parameter_declaration(@1);}
  | declaration_specifier direct_abstract_declarator {ast.parameter_declaration(@1);}
//  | declaration_specifier {ast.parameter_declaration(@1);}
  ;

//<abstract-declarator> ::= <pointer>
//                        | <pointer> <direct-abstract-declarator>
//                        | <direct-abstract-declarator>
//abstract_declarator:
//  // no pointers
//  direct_abstract_declarator
//  ;

//<direct-abstract-declarator> ::=  ( <abstract-declarator> )
//                               | {<direct-abstract-declarator>}? [ {<constant-expression>}? ]
//                               | {<direct-abstract-declarator>}? ( {<parameter-type-list>}? )
direct_abstract_declarator:
//   LBRACKET INTCONST RBRACKET // done
//  | LBRACKET INTCONST RBRACKET direct_abstract_declarator // done
   LPAREN parameter_type_list RPAREN
  | LPAREN parameter_type_list RPAREN direct_abstract_declarator
  ;

//<enum-specifier> ::= enum <identifier> { <enumerator-list> }
//                   | enum { <enumerator-list> }
//                   | enum <identifier>
//enum_specifier:
//  ENUM IDENTIFIER LBRACE enumerator_list RBRACE
//  | ENUM LBRACE enumerator_list RBRACE
//  | ENUM IDENTIFIER
//  ;

//<enumerator-list> ::= <enumerator>
//                    | <enumerator-list> , <enumerator>
//enumerator_list:
//  enumerator
//  | enumerator_list COMMA enumerator
//  ;

//<enumerator> ::= <identifier>
//               | <identifier> = <constant-expression>
//enumerator:
//  IDENTIFIER
//  | IDENTIFIER EQUALS constant_expression
//  ;
//  ;

//<typedef-name> ::= <identifier>
//typedef_name:
//  IDENTIFIER
//  ;

//<declaration> ::=  {<declaration-specifier>}+ {<init-declarator>}* ;
declaration:
  declaration_specifier multiple_init_declarators SEMICOLON {ast.declaration(@1);}
//  | multiple_declaration_specifiers SEMICOLON {ast.declaration();}
  ;

//multiple_declarations:
//  declaration multiple_declarations // done
//  | declaration // done
//  ;

//<init-declarator> ::= <declarator>
//                    | <declarator> = <initializer>
init_declarator:
  direct_declarator EQUALS initializer {ast.init_declarator(true);}
  | direct_declarator {ast.init_declarator(false);}
  ;

multiple_init_declarators:
  init_declarator COMMA multiple_init_declarators
  | init_declarator
  ;

//<initializer> ::= <assignment-expression>
//                | { <initializer-list> }
//                | { <initializer-list> , }
initializer:
  assignment_expression
  | LBRACE {ast.initializer_list_begin(@1);} RBRACE
  | LBRACE {ast.initializer_list_begin(@1);} initializer_list RBRACE
  ;

//<initializer-list> ::= <initializer>
//                     | <initializer-list> , <initializer>
initializer_list:
  initializer {ast.initializer_list_element(@1);}
  | initializer_list COMMA initializer {ast.initializer_list_element(@3);}
  ;

//<compound-statement> ::= { {<declaration>}* {<statement>}* }
compound_statement:
//  LBRACE multiple_declarations multiple_statements RBRACE
//  | LBRACE multiple_declarations RBRACE
  LBRACE {ast.scope_begin();} multiple_statements RBRACE {ast.scope_end();}
  | LBRACE RBRACE
  ;

//<statement> ::= <labeled-statement>
//              | <expression-statement>
//              | <compound-statement>
//              | <selection-statement>
//              | <iteration-statement>
//              | <jump-statement>
statement:
  basic_statement
  | labeled_statement
  | compound_statement
  | selection_statement
  | iteration_statement
  | jump_statement
  ;

basic_statement:
  declaration
  | expression_statement
  ;

multiple_statements:
  multiple_statements statement
  | statement
  ;

//<labeled-statement> ::= <identifier> : <statement>
//                      | case <constant-expression> : <statement>
//                      | default : <statement>
labeled_statement:
//  IDENTIFIER COLON statement
  CASE constant_expression COLON {ast.case_statement(@1, @2, false);} statement
  | DEFAULT COLON {ast.case_statement(@1, @1, true);} statement
  ;

//<expression-statement> ::= {<expression>}? ;
expression_statement:
  SEMICOLON
  | expression SEMICOLON {ast.expression_statement();}

//<selection-statement> ::= if ( <expression> ) <statement>
//                        | if ( <expression> ) <statement> else <statement>
//                        | switch ( <expression> ) <statement>
selection_statement:
  IF LPAREN expression RPAREN {ast.conditional_begin(@1,@3);} selection_rest
  | SWITCH LPAREN expression RPAREN LBRACE {ast.switch_begin(@1,@3);} multiple_statements RBRACE {ast.switch_end(@1);}
  | SWITCH LPAREN expression RPAREN LBRACE {ast.switch_begin(@1,@3);} RBRACE {ast.switch_end(@1);}
  ;

selection_rest:
  statement ELSE {ast.conditional_else();} statement {ast.conditional_end(true);}
  | statement %prec NOELSE {ast.conditional_end(false);}
  ;

//<iteration-statement> ::= while ( <expression> ) <statement>
//                        | do <statement> while ( <expression> ) ;
//                        | for ( {<expression>}? ; {<expression>}? ; {<expression>}? ) <statement>
//iteration_statement:
//  WHILE LPAREN expression RPAREN statement
//  | DO statement WHILE LPAREN expression RPAREN SEMICOLON
//  | FOR LPAREN expression SEMICOLON expression SEMICOLON expression RPAREN statement
//  | FOR LPAREN SEMICOLON expression SEMICOLON expression RPAREN statement
//  | FOR LPAREN expression SEMICOLON SEMICOLON expression RPAREN statement
//  | FOR LPAREN SEMICOLON SEMICOLON expression RPAREN statement
//  | FOR LPAREN expression SEMICOLON expression SEMICOLON RPAREN statement
//  | FOR LPAREN SEMICOLON expression SEMICOLON RPAREN statement
//  | FOR LPAREN expression SEMICOLON SEMICOLON RPAREN statement
//  | FOR LPAREN SEMICOLON SEMICOLON RPAREN statement
//  ;
iteration_statement:
  WHILE {ast.iteration_begin();} LPAREN expression RPAREN {ast.iteration_statements(@3,true,false);} statement {ast.iteration_end(true);}
  | DO {ast.iteration_begin();} statement WHILE LPAREN expression RPAREN {ast.iteration_statements(@5,true,false);} SEMICOLON {ast.iteration_end(false);}
  | for_loop LPAREN basic_statement SEMICOLON RPAREN {ast.iteration_statements(@1,false,false);} statement {ast.iteration_end(true);}
  | for_loop LPAREN basic_statement SEMICOLON expression RPAREN {ast.iteration_statements(@1,false,true);} statement {ast.iteration_end(true);}
  | for_loop LPAREN basic_statement expression SEMICOLON RPAREN {ast.iteration_statements(@4,true,false);} statement {ast.iteration_end(true);}
  | for_loop LPAREN basic_statement expression SEMICOLON expression RPAREN {ast.iteration_statements(@4,true,true);} statement {ast.iteration_end(true);}
  ;

for_loop:
  FOR {ast.iteration_begin();}
  ;

//<jump-statement> ::= goto <identifier> ;
//                   | continue ;
//                   | break ;
//                   | return {<expression>}? ;
jump_statement:
  CONTINUE SEMICOLON {ast.continue_statement(@1);}
  | BREAK SEMICOLON {ast.break_statement(@1);}
  | RETURN expression SEMICOLON {ast.return_statement(@1,@2);}
  ;

%%
