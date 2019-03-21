#ifndef EVALUATOR_H_
#define EVALUATOR_H_
#include "../lang/ast_node.hpp"

extern AstNode evaluate(const AstNode& root);
extern AstNode evaluate_literal(const AstNode& lit);
extern AstNode evaluate_funcall(const AstNode& funcall);
extern AstNode evaluate_fundef(const AstNode& fundef);
extern AstNode evaluate_repeat(const AstNode& repeat);
extern AstNode evaluate_bracketed(const AstNode& bracketed);
extern AstNode evaluate_if(const AstNode& if_node);
extern AstNode evaluate_ifelse(const AstNode& ifelse_node);
extern AstNode evaluate_output(const AstNode& output);
extern AstNode evaluate_stop(const AstNode& stop);
extern AstNode evaluate_repcount(const AstNode& repcount);

#endif
