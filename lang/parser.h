#ifndef PARSER_H_
#define PARSER_H_
#include "ast_node.h"
#include "token.h"
#include "tokenizer.h"

extern AstNode parse_expression(Tokenizer tok);
extern AstNode parse_number(Tokenizer tok);
extern AstNode parse_boolean(Tokenizer tok);
extern AstNode parse_repeat(Tokenizer tok);
extern AstNode parse_bracketed(Tokenizer tok);
extern AstNode parse_identifier(Tokenizer tok);
extern AstNode parse_funcall(Tokenizer tok);
extern AstNode parse_fundef(Tokenizer tok);
extern AstNode parse_parameter(Tokenizer tok);
extern AstNode parse_if(Tokenizer tok);
extern AstNode parse_output(Tokenizer tok);
extern AstNode parse_stop(Tokenizer tok);
extern AstNode parse_repcount(Tokenizer tok);

#endif
