#ifndef __LEXER_H__
#define __LEXER_H__

#undef yyFlexLexer
#define yyFlexLexer clikeFlexLexer
#include "parser.h"
#include "location.hh"
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

namespace clike {

class lexer : public clikeFlexLexer {
public:
   
   lexer(std::istream *in) : clikeFlexLexer(in) {
   }

   virtual ~lexer() {
   }

   //get rid of override virtual function warning
   using clikeFlexLexer::yylex;

   virtual int yylex(clike::parser::semantic_type* lval, clike::parser::location_type* location);

private:

   clike::parser::semantic_type *yylval = nullptr;

};

} /* namespace */

#endif /* __LEXER_H__ */
