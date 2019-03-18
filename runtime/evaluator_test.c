#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../lang/procedure.h"
#include "../turtle/turtle.h"
#include "../init/init_dispatch.h"
#include "../init/init_turtle.h"
#include "../lang/parser.h"
#include "evaluator.h"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in test %s\n", __LINE__, __func__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);

void test_evaluate_literal() {
    // Given: You have parsed the given expressions into an AST
    const char *bool_expr = "true";
    const char *num_expr = "5.7";

    Tokenizer tok = create_tokenizer();
    tokenize(tok, bool_expr);
    AstNode n1 = parse_expression(tok);

    tokenize(tok, num_expr);
    AstNode n2 = parse_expression(tok);

    // When: You evaluate the respective ASTs
    AstNode e1 = evaluate(n1);
    AstNode e2 = evaluate(n2);

    // Then: You should get the literal values back as results
    ASSERT(get_ast_bool_value(e1) == get_ast_bool_value(n1));
    ASSERT(get_ast_number_value(e2) == get_ast_number_value(n2));
    destroy_astnode(n1);
    destroy_astnode(n2);
    destroy_tokenizer(tok);
    SUCCESS();
}

void test_evaluate_funcall() {
    // Given: You have parsed the following function call expression into an AST
    init_turtle(500, 500, 90, true);
    init_dispatch_table();

    const char *arith_expr = "1 + 2 * 3";
    
    Tokenizer tok = create_tokenizer();
    tokenize(tok, arith_expr);

    AstNode root = parse_expression(tok);

    // When: You evaluate the respective AST
    AstNode result = evaluate(root);

    // Then: The type of the AstNode that you get the result of the funcall back
    ASSERT(get_ast_type(result) == AST_NUMBER);
    ASSERT(get_ast_number_value(result) == 7);
    destroy_astnode(result);
    destroy_astnode(root);
    destroy_tokenizer(tok);
    SUCCESS();
}

int main(int argc, char *argv[]) {

    test_evaluate_literal();
    test_evaluate_funcall();
    return 0;
}
