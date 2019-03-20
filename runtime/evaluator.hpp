#ifndef EVALUATOR_H_
#define EVALUATOR_H_
#include "../lang/ast_node.hpp"

extern AstNode evaluate(const AstNode& root);
extern AstNode evaluate_literal(const AstNode& lit);
extern AstNode evaluate_funcall(const AstNode& funcall);
extern AstNode evaluate_fundef(const AstNode& fundef);
//extern AstNode evaluate_repeat(AstNode repeat);

#endif
