#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "../turtle/turtle.hpp"
#include "procedure.hpp"
#include "dispatch_table.hpp"
#include "../init/init_turtle.hpp"
#include "../init/init_dispatch.hpp" 
#include "parser.hpp"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in test %s\n", __LINE__, __func__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);

void test_parse_repeat() {
    init_turtle(500, 500, 90, true);
    init_dispatch_table();
    // Given: you tokenize the following expression
    Tokenizer tok = Tokenizer();
    const char *expression = "repeat 4 [ forward 100 right 90 ]";
    tok.tokenize(expression);

    // When: you parse the tokens held by the tokenizer
    AstNode repeat_node = parse_expression(tok);

    // Then: the type of the repeat_node should be repeat
    ASSERT(repeat_node.get_type() == NodeType::AST_REPEAT);
    ASSERT(repeat_node.get_num_children() == 2);
    
    AstNode count_node = repeat_node.get_child(0);
    ASSERT(count_node.get_type() == NodeType::AST_NUMBER);
    
    AstNode bracketed_node = repeat_node.get_child(1);
    ASSERT(bracketed_node.get_type() == NodeType::AST_BRACKETED);
    ASSERT(bracketed_node.get_num_children() == 2);
    AstNode forward = bracketed_node.get_child(0);
    ASSERT(forward.get_type() == NodeType::AST_FUNCALL);
    
    AstNode n1 = forward.get_child(0);
    ASSERT(n1.get_type() == NodeType::AST_NUMBER);
    ASSERT(n1.get_value<double>() == 100.0);
    
    AstNode right = bracketed_node.get_child(1);
    ASSERT(right.get_type() == NodeType::AST_FUNCALL);
    
    AstNode n2 = right.get_child(0);
    ASSERT(n2.get_type() == NodeType::AST_NUMBER);
    ASSERT(n2.get_value<double>() == 90.0);

    SUCCESS();
}

void test_parse_nested_repeat() {
    init_turtle(500, 500, 90, true);
    init_dispatch_table();
    // Given: you tokenize the following expression
    Tokenizer tok = Tokenizer();
    const char *expression = "repeat 4 [ repeat 4 \
                              [ forward 100 right 90 ] right 90 ]";
    tok.tokenize(expression);

    // When: you parse the tokens held by the tokenizer
    AstNode repeat_node = parse_expression(tok);

    // Then: the type of the repeat_node should be repeat
    ASSERT(repeat_node.get_type() == NodeType::AST_REPEAT);
    ASSERT(repeat_node.get_num_children() == 2);
    
    AstNode count_node = repeat_node.get_child(0);
    ASSERT(count_node.get_type() == NodeType::AST_NUMBER);
    
    AstNode bracketed_node = repeat_node.get_child(1);
    ASSERT(bracketed_node.get_type() == NodeType::AST_BRACKETED);
    ASSERT(bracketed_node.get_num_children() == 2);

    AstNode repeat2 = bracketed_node.get_child(0);
    ASSERT(repeat2.get_type() == NodeType::AST_REPEAT);
    AstNode right2 = bracketed_node.get_child(1);
    ASSERT(right2.get_type() == NodeType::AST_FUNCALL);
    AstNode number3 = right2.get_child(0);
    ASSERT(number3.get_type() == NodeType::AST_NUMBER);
    ASSERT(number3.get_value<double>() == 90.0);

    ASSERT(repeat2.get_num_children() == 2);
    AstNode count2 = repeat2.get_child(0);
    ASSERT(count2.get_type() == NodeType::AST_NUMBER);
    AstNode bracketed2 = repeat2.get_child(1);
    ASSERT(bracketed2.get_type() == NodeType::AST_BRACKETED);

    ASSERT(bracketed2.get_num_children() == 2);

    SUCCESS();
}

void test_parse_fundef() {
    init_turtle(500, 500, 90, true);
    init_dispatch_table();
    // Given: You have the following function definition expression
    const char *expression = "to square :length repeat 4 [ forward :length right 90 ] end";

    // When: You parse the expression
    Tokenizer tok = Tokenizer();
    tok.tokenize(expression);

    // Then: You should get back the root of the appropriate AST
    AstNode func_node = parse_expression(tok);
    ASSERT(func_node.get_type() == NodeType::AST_FUNC);
    ASSERT(func_node.get_num_children() == 2);

    AstNode param_node = func_node.get_child(0);
    ASSERT(param_node.get_type() == NodeType::AST_PARAMETER);

    AstNode body_node = func_node.get_child(1);
    ASSERT(body_node.get_type() == NodeType::AST_REPEAT);
    ASSERT(body_node.get_num_children() == 2);

    AstNode count_node = body_node.get_child(0);
    ASSERT(count_node.get_type() == NodeType::AST_NUMBER);
    ASSERT(count_node.get_value<double>() == 4.0);

    AstNode bracketed = body_node.get_child(1);
    ASSERT(bracketed.get_type() == NodeType::AST_BRACKETED);
    ASSERT(bracketed.get_num_children() == 2);

    AstNode forward = bracketed.get_child(0);
    ASSERT(forward.get_type() == NodeType::AST_FUNCALL);
    ASSERT(strcmp(forward.get_value<const char *>(), "forward") == 0);
    ASSERT(forward.get_num_children() == 1);

    AstNode right = bracketed.get_child(1);
    ASSERT(right.get_type() == NodeType::AST_FUNCALL);
    ASSERT(strcmp(right.get_value<const char *>(), "right") == 0);
    ASSERT(right.get_num_children() == 1);

    SUCCESS();
}

void test_parse_if() {
    init_turtle(500, 500, 90, true);
    init_dispatch_table();
    // Given: You have tokenized the following if expression
    const char *expression = "if :n < 1 [ output 1 ]";

    Tokenizer tok = Tokenizer();
    tok.tokenize(expression);

    Token if_tok = tok.get_next();
    ASSERT(if_tok.get_type() == TokenType::IF);
    ASSERT(tok.peek_next().get_type() == TokenType::OTHER);
    tok.get_next();
    ASSERT(tok.peek_next().get_type() == TokenType::PARAMETER);
    tok.unget();
    tok.unget();

    // When: You parse the tokens
    AstNode if_node = parse_expression(tok);

    // Then: You should get back the appropriate AST
    ASSERT(if_node.get_type() == NodeType::AST_IF);
    ASSERT(if_node.get_num_children() == 2);

    AstNode conditional = if_node.get_child(0);
    ASSERT(conditional.get_type() == NodeType::AST_FUNCALL);
    ASSERT(conditional.get_num_children() == 2);

    AstNode param = conditional.get_child(0);
    ASSERT(param.get_type() == NodeType::AST_PARAMETER);
    AstNode number = conditional.get_child(1);
    ASSERT(number.get_type() == NodeType::AST_NUMBER);

    AstNode bracketed = if_node.get_child(1);
    ASSERT(bracketed.get_type() == NodeType::AST_BRACKETED);
    ASSERT(bracketed.get_num_children() == 1);

    AstNode output = bracketed.get_child(0);
    ASSERT(output.get_type() == NodeType::AST_OUTPUT);

    SUCCESS();
}




int main(int argc, char *argv[]) {
    test_parse_repeat();
    test_parse_nested_repeat();
    test_parse_fundef();
    test_parse_if();
    return 0;
}
