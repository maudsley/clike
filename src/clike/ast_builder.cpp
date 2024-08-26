#include "ast_builder.h"
#include "lexer.h"
#include "parser.h"

namespace clike {

void parser::error( const location_type &l, const std::string &err_message ) {
  std::string prefix = "syntax error, ";
  ast.report_parser_error(l, err_message.substr(prefix.length()));
}

bool syntax_tree_builder::parse(const std::string& source_string) {
  std::stringstream source_stream;
  source_stream << source_string << std::endl;
  lexer_ = std::make_shared<lexer>(&source_stream);
  parser_ = std::make_shared<parser>(*lexer_, *this);
  parser_->set_debug_level(1);

  try {
    if (parser_->parse() != 0) {
      ast_.reset();
    }
  } catch (const parser_exception&) {
    /* fatal parse error handler */
    ast_.reset();
  }

  return !!ast_;
}

} /* namespace */
