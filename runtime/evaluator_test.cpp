#include <cassert>
#include <cstdio>
#include <cstdbool>
#include "../lang/procedure.hpp"
#include "../turtle/turtle.hpp"
#include "../init/init_dispatch.hpp"
#include "../init/init_turtle.hpp"
#include "../lang/parser.hpp"
#include "evaluator.hpp"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in test %s\n", __LINE__, __func__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);

void test_evaluate_literal() {
    // Given: You have parsed the given expressions into an AST
    const char *bool_expr = "true";
    const char *num_expr = "5.7";

    Tokenizer tok = Tokenizer();
    tok.tokenize(bool_expr);
    AstNode n1 = parse_expression(tok);

    tok.tokenize(num_expr);
    AstNode n2 = parse_expression(tok);

    // When: You evaluate the respective ASTs
    AstNode e1 = evaluate(n1);
    AstNode e2 = evaluate(n2);

    // Then: You should get the literal values back as results
    ASSERT(e1.get_value<bool>() == n1.get_value<bool>());
    ASSERT(e2.get_value<double>() == n2.get_value<double>());

    SUCCESS();
}

void test_evaluate_funcall() {
    // Given: You have parsed the following function call expression into an AST
    init_turtle(500, 500, 90, true);
    init_dispatch_table();

    const char *arith_expr = "1 + 2 * 3";
    
    Tokenizer tok = Tokenizer();
    tok.tokenize(arith_expr);

    AstNode root = parse_expression(tok);

    // When: You evaluate the respective AST
    AstNode result = evaluate(root);

    // Then: You get an AstNode back containing the result of the function call
    ASSERT(result.get_type() == NodeType::AST_NUMBER);
    ASSERT(result.get_value<double>() == 7);

    SUCCESS();
}

void test_evaluate_repeat() {
    // Given: You have parsed the following repeat expression into an AST
    init_turtle(500, 500, 90, true);
    init_dispatch_table();

    const char *repeat_expr = "repeat 4 [ repcount + 5 ]";

    Tokenizer tok = Tokenizer();
    tok.tokenize(repeat_expr);

    AstNode root = parse_expression(tok);

    // When: You evaluate the respective AST
    AstNode result = evaluate(root);

    // Then: The type of the AstNode that you get back is a AST_NUMBER
    ASSERT(result.get_type() == NodeType::AST_NUMBER);

    // Then: The value of the AstNode that you get back is 9
    ASSERT(result.get_value<double>() == 9.0);

    SUCCESS();
}

void test_evaluate_ifelse() {
    // Given: You have parse the following ifelse expression
    init_turtle(500, 500, 90, true);
    init_dispatch_table();

    const char *ifelse_expr = "ifelse 5 < 10 [ 5 * 20 ] [ 20 - 5 ]";

    Tokenizer tok = Tokenizer();
    tok.tokenize(ifelse_expr);

    AstNode root = parse_expression(tok);

    // When: You evaluate the resulting AST
    AstNode result = evaluate(root);

    // Then: The type of the AstNode that you get back is an AST_NUMBER
    ASSERT(result.get_type() == NodeType::AST_NUMBER);

    // Then: The value of the AstNode that you get back is 100
    ASSERT(result.get_value<double>() == 100.0);
    SUCCESS();
}

void test_evaluate_ifelse_falsecond() {
    // Given: You have parse the following ifelse expression
    init_turtle(500, 500, 90, true);
    init_dispatch_table();

    const char *ifelse_expr = "ifelse 5 > 10 [ 5 * 20 ] [ 20 - 5 ]";

    Tokenizer tok = Tokenizer();
    tok.tokenize(ifelse_expr);

    AstNode root = parse_expression(tok);

    // When: You evaluate the resulting AST
    AstNode result = evaluate(root);

    // Then: The type of the AstNode that you get back is an AST_NUMBER
    ASSERT(result.get_type() == NodeType::AST_NUMBER);

    // Then: The value of the AstNode that you get back is 15
    ASSERT(result.get_value<double>() == 15.0);
    SUCCESS();
}

int main(int argc, char *argv[]) {

    test_evaluate_literal();
    test_evaluate_funcall();
    test_evaluate_repeat();
    test_evaluate_ifelse();
    test_evaluate_ifelse_falsecond();
    return 0;
}
