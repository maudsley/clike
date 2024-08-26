%{
//#undef yyFlexLexer
#include "ast_builder.h"
#include "lexer.h"
#include "parser.h"
#undef YY_DECL
#define YY_DECL int clike::lexer::yylex(clike::parser::semantic_type* lval, clike::parser::location_type* loc)

#include <cstdio>
#include <iostream>

/* #define YY_USER_ACTION loc->step(); loc->columns(yyleng); */
#define YY_USER_ACTION loc->columns(yyleng);

using token = clike::parser::token;

%}

%option yylineno
%option debug
%option nodefault
%option yyclass="clike::lexer"
%option prefix="clike"
%option noyywrap
%option c++

%x IN_COMMENT

%%

%{
  /** Code executed at the beginning of yylex **/
  yylval = lval;
  loc->step();
%}

[ \t]+ {loc->step();}
[\n]+ {loc->lines(yyleng); loc->step();}

";" {return token::SEMICOLON;}
":" {return token::COLON;}
"," {return token::COMMA;}
"." {return token::DOT;}
"?" {return token::QMARK;}
"!" {return token::BANG;}
"~" {return token::TILDE;}

"{" {return token::LBRACE;}
"}" {return token::RBRACE;}
"(" {return token::LPAREN;}
")" {return token::RPAREN;}
"[" {return token::LBRACKET;}
"]" {return token::RBRACKET;}

"=" {return token::EQUALS;}
"!=" {return token::NOTEQ;}
"==" {return token::EQEQ;}
"<" {return token::LTHAN;}
"<=" {return token::LTHANEQ;}
">" {return token::GTHAN;}
">=" {return token::GTHANEQ;}

"&&" {return token::ANDAND;}
"&" {return token::AND;}
"&=" {return token::ANDEQ;}
"<<" {return token::LSHIFT;}
"<<=" {return token::LSHIFTEQ;}
">>" {return token::RSHIFT;}
">>=" {return token::RSHIFTEQ;}
"||" {return token::OROR;}
"|" {return token::OR;}
"|=" {return token::OREQ;}
"^" {return token::XOR;}
"^=" {return token::XOREQ;}
"++" {return token::PLUSPLUS;}
"+" {return token::PLUS;}
"+=" {return token::PLUSEQ;}
"--" {return token::MINUSMINUS;}
"-" {return token::MINUS;}
"-=" {return token::MINUSEQ;}
"*" {return token::MUL;}
"*=" {return token::MULEQ;}
"/" {return token::DIV;}
"/=" {return token::DIVEQ;}
"%" {return token::MOD;}
"%=" {return token::MODEQ;}

"for" {return token::FOR;}
"do" {return token::DO;}
"while" {return token::WHILE;}
"continue" {return token::CONTINUE;}
"break" {return token::BREAK;}
"switch" {return token::SWITCH;}
"case" {return token::CASE;}
"if" {return token::IF;}
"else" {return token::ELSE;}
"goto" {return token::GOTO;}
"return" {return token::RETURN;}

"auto" {return token::AUTO;}
"const" {return token::CONST;}
"default" {return token::DEFAULT;}
"extern" {return token::EXTERN;}
"register" {return token::REGISTER;}
"static" {return token::STATIC;}
"typedef" {return token::TYPEDEF;}
"sizeof" {return token::SIZEOF;}

"volatile" {return token::VOLATILE;}
"signed" {return token::SIGNED;}
"unsigned" {return token::UNSIGNED;}
"long" {return token::LONG;}
"short" {return token::SHORT;}
"void" {return token::VOID;}
"bool" {return token::BOOL;}
"char" {return token::CHAR;}
"int" {return token::INT;}
"float" {return token::FLOAT;}
"double" {return token::DOUBLE;}

"struct" {return token::STRUCT;}

[\_a-zA-Z][\_a-zA-Z0-9]* {
  yylval->build<std::string>(yytext);
  return token::IDENTIFIER;
}

[0-9]+[LlUu]? {
  yylval->build<std::string>(yytext);
  return token::INTCONST;
}

0x[0-9A-Fa-f]+[LlUu]? {
  yylval->build<std::string>(yytext);
  return token::HEXCONST;
}

"//".* /* single line comments */
<INITIAL>"/*"         BEGIN(IN_COMMENT); /* multi-line comments */
<IN_COMMENT>"*/"      BEGIN(INITIAL);
<IN_COMMENT>[^*\n]+   // eat comment in chunks
<IN_COMMENT>"*"       // eat the lone star
<IN_COMMENT>\n        yylineno++;

<<EOF>> {return 0;}

. {return token::SYMBOL;} /* default rule */

%%
