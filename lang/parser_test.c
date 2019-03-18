#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../turtle/turtle.h"
#include "procedure.h"
#include "dispatch_table.h"
#include "../init/init_turtle.h"
#include "../init/init_dispatch.h" 
#include "parser.h"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in test %s\n", __LINE__, __func__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);

void test_parse_repeat() {
    init_turtle(500, 500, 90, true);
    init_dispatch_table();
    // Given: you tokenize the following expression
    Tokenizer tok = create_tokenizer();
    const char *expression = "repeat 4 [ forward 100 right 90 ]";
    tokenize(tok, expression);

    // When: you parse the tokens held by the tokenizer
    AstNode repeat_node = parse_expression(tok);

    // Then: the type of the repeat_node should be repeat
    ASSERT(get_ast_type(repeat_node) == AST_REPEAT);
    ASSERT(get_num_children(repeat_node) == 2);
    
    AstNode count_node = get_child(repeat_node, 0);
    ASSERT(get_ast_type(count_node) == AST_NUMBER);
    
    AstNode bracketed_node = get_child(repeat_node, 1);
    ASSERT(get_ast_type(bracketed_node) == AST_BRACKETED);
    ASSERT(get_num_children(bracketed_node) == 2);
    AstNode forward = get_child(bracketed_node, 0);
    ASSERT(get_ast_type(forward) == AST_FUNCALL);
    
    AstNode n1 = get_child(forward, 0);
    ASSERT(get_ast_type(n1) == AST_NUMBER);
    ASSERT(get_ast_number_value(n1) == 100);
    
    AstNode right = get_child(bracketed_node, 1);
    ASSERT(get_ast_type(right) == AST_FUNCALL);
    
    AstNode n2 = get_child(right, 0);
    ASSERT(get_ast_type(n2) == AST_NUMBER);
    ASSERT(get_ast_number_value(n2) == 90);
    destroy_tokenizer(tok);
    destroy_astnode(repeat_node);

    SUCCESS();
}

void test_parse_nested_repeat() {
    init_turtle(500, 500, 90, true);
    init_dispatch_table();
    // Given: you tokenize the following expression
    Tokenizer tok = create_tokenizer();
    const char *expression = "repeat 4 [ repeat 4 \
                              [ forward 100 right 90 ] right 90 ]";
    tokenize(tok, expression);

    // When: you parse the tokens held by the tokenizer
    AstNode repeat_node = parse_expression(tok);

    // Then: the type of the repeat_node should be repeat
    ASSERT(get_ast_type(repeat_node) == AST_REPEAT);
    ASSERT(get_num_children(repeat_node) == 2);
    
    AstNode count_node = get_child(repeat_node, 0);
    ASSERT(get_ast_type(count_node) == AST_NUMBER);
    
    AstNode bracketed_node = get_child(repeat_node, 1);
    ASSERT(get_ast_type(bracketed_node) == AST_BRACKETED);
    ASSERT(get_num_children(bracketed_node) == 2);

    AstNode repeat2 = get_child(bracketed_node, 0);
    ASSERT(get_ast_type(repeat2) == AST_REPEAT);
    AstNode right2 = get_child(bracketed_node, 1);
    ASSERT(get_ast_type(right2) == AST_FUNCALL);
    AstNode number3 = get_child(right2, 0);
    ASSERT(get_ast_type(number3) == AST_NUMBER);
    ASSERT(get_ast_number_value(number3) == 90);

    ASSERT(get_num_children(repeat2) == 2);
    AstNode count2 = get_child(repeat2, 0);
    ASSERT(get_ast_type(count2) == AST_NUMBER);
    AstNode bracketed2 = get_child(repeat2, 1);
    ASSERT(get_ast_type(bracketed2) == AST_BRACKETED);

    ASSERT(get_num_children(bracketed2) == 2);

    destroy_tokenizer(tok);
    destroy_astnode(repeat_node);

    SUCCESS();
}

void test_parse_fundef() {
    init_turtle(500, 500, 90, true);
    init_dispatch_table();
    // Given: You have the following function definition expression
    const char *expression = "to square :length repeat 4 [ forward :length right 90 ] end";

    // When: You parse the expression
    Tokenizer tok = create_tokenizer();
    tokenize(tok, expression);


    // Then: You should get back the root of the appropriate AST
    AstNode func_node = parse_expression(tok);
    ASSERT(get_ast_type(func_node) == AST_FUNC);
    ASSERT(get_num_children(func_node) == 2);

    AstNode param_node = get_child(func_node, 0);
    ASSERT(get_ast_type(param_node) == AST_PARAMETER);

    AstNode body_node = get_child(func_node, 1);
    ASSERT(get_ast_type(body_node) == AST_REPEAT);
    ASSERT(get_num_children(body_node) == 2);

    AstNode count_node = get_child(body_node, 0);
    ASSERT(get_ast_type(count_node) == AST_NUMBER);
    ASSERT(get_ast_number_value(count_node) == 4);

    AstNode bracketed = get_child(body_node, 1);
    ASSERT(get_ast_type(bracketed) == AST_BRACKETED);
    ASSERT(get_num_children(bracketed) == 2);

    AstNode forward = get_child(bracketed, 0);
    ASSERT(get_ast_type(forward) == AST_FUNCALL);
    ASSERT(strcmp(get_ast_str_value(forward), "forward") == 0);
    ASSERT(get_num_children(forward) == 1);

    AstNode right = get_child(bracketed, 1);
    ASSERT(get_ast_type(right) == AST_FUNCALL);
    ASSERT(strcmp(get_ast_str_value(right), "right") == 0);
    ASSERT(get_num_children(right) == 1);
    destroy_astnode(func_node);
    SUCCESS();
}

void test_parse_if() {
    init_turtle(500, 500, 90, true);
    init_dispatch_table();
    // Given: You have tokenized the following if expression
    const char *expression = "if :n < 1 [ output 1 ]";

    Tokenizer tok = create_tokenizer();
    tokenize(tok, expression);

    Token if_tok = get_next(tok);
    ASSERT(get_type(if_tok) == IF);
    ASSERT(get_type(peek_next(tok)) == OTHER);
    get_next(tok);
    ASSERT(get_type(peek_next(tok)) == PARAMETER);
    unget(tok);
    unget(tok);

    // When: You parse the tokens
    AstNode if_node = parse_expression(tok);

    // Then: You should get back the appropriate AST
    ASSERT(get_ast_type(if_node) == AST_IF);
    ASSERT(get_num_children(if_node) == 2);

    AstNode conditional = get_child(if_node, 0);
    ASSERT(get_ast_type(conditional) == AST_FUNCALL);
    ASSERT(get_num_children(conditional) == 2);

    AstNode param = get_child(conditional, 0);
    ASSERT(get_ast_type(param) == AST_PARAMETER);
    AstNode number = get_child(conditional, 1);
    ASSERT(get_ast_type(number) == AST_NUMBER);

    AstNode bracketed = get_child(if_node, 1);
    ASSERT(get_ast_type(bracketed) == AST_BRACKETED);
    ASSERT(get_num_children(bracketed) == 1);

    AstNode output = get_child(bracketed, 0);
    ASSERT(get_ast_type(output) == AST_OUTPUT);
    destroy_astnode(if_node);
    SUCCESS();
}




int main(int argc, char *argv[]) {
    test_parse_repeat();
    test_parse_nested_repeat();
    test_parse_fundef();
    test_parse_if();
    return 0;
}
