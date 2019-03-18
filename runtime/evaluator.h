#ifndef EVALUATOR_H_
#define EVALUATOR_H_
#include "../lang/ast_node.h"

extern AstNode evaluate(AstNode root);
extern AstNode evaluate_literal(AstNode lit);
extern AstNode evaluate_funcall(AstNode funcall);
extern AstNode evaluate_fundef(AstNode fundef);
//extern AstNode evaluate_repeat(AstNode repeat);

#endif
