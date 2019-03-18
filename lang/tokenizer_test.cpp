#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.hpp"
#include "tokenizer.hpp"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in test %s\n", __LINE__, __func__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);

void test_tokenizer() {
    // Given: You have created a Tokenizer
    Tokenizer tok = Tokenizer();

    // When: You tokenize the following string
    char *string = (char *)malloc(sizeof(char) * (strlen("Hello World!") + 1));
    strcpy(string, "Hello World!");
    tok.tokenize(string);

    // Then: You should be able to get the appropriate tokens back
    Token t1 = tok.get_next();
    Token t2 = tok.get_next();

    ASSERT(t1.get_type() == TokenType::OTHER);
    ASSERT(t2.get_type() == TokenType::OTHER);
    ASSERT(strcmp(t1.get_contents(), "Hello") == 0);
    ASSERT(strcmp(t2.get_contents(), "World!") == 0);
    free(string);
    SUCCESS();
}

void test_tokenizer_complex() {
    // Given: You have the following expression string
    const char *expression = "repeat 4 [ forward 5 * repcount right 90 ]";
    
    // When: You tokenize the string
    Tokenizer tok = Tokenizer();
    tok.tokenize(expression);

    // Then: You should have the correct tokens
    Token t1 = tok.get_next();
    Token t2 = tok.get_next();
    Token t3 = tok.get_next();
    Token t4 = tok.get_next();
    Token t5 = tok.get_next();
    Token t6 = tok.get_next();
    Token t7 = tok.get_next();
    Token t8 = tok.get_next();
    Token t9 = tok.get_next();
    Token t10 = tok.get_next();

    ASSERT(t1.get_type() == TokenType::REPEAT);
    ASSERT(t2.get_type() == TokenType::NUMBER);
    ASSERT(t3.get_type() == TokenType::OPEN_SQUARE);
    ASSERT(t4.get_type() == TokenType::OTHER);
    ASSERT(t5.get_type() == TokenType::OTHER);
    ASSERT(t6.get_type() == TokenType::NUMBER);
    ASSERT(t7.get_type() == TokenType::REPCOUNT);
    ASSERT(t8.get_type() == TokenType::OTHER);
    ASSERT(t9.get_type() == TokenType::NUMBER);
    ASSERT(t10.get_type() ==TokenType::CLOSED_SQUARE);

    ASSERT(strcmp(t1.get_contents(), "repeat") == 0);
    ASSERT(strcmp(t2.get_contents(), "4") == 0);
    ASSERT(strcmp(t3.get_contents(), "[") == 0);
    ASSERT(strcmp(t4.get_contents(), "forward") == 0);
    ASSERT(strcmp(t5.get_contents(), "*") == 0);
    ASSERT(strcmp(t6.get_contents(), "5") == 0);
    ASSERT(strcmp(t7.get_contents(), "repcount") == 0);
    ASSERT(strcmp(t8.get_contents(), "right") == 0);
    ASSERT(strcmp(t9.get_contents(), "90") == 0);
    ASSERT(strcmp(t10.get_contents(), "]") == 0);
    SUCCESS();
}

void test_tokenizer_unget() {
    // Given: You have the following expression string
    const char *expression = "repeat 5 [ forward 100 right 90 ]";

    // When: You tokenize, get, unget, and get again
    Tokenizer tok = Tokenizer();
    tok.tokenize(expression);

    Token t = tok.get_next();
    tok.unget();
    Token t2 = tok.get_next();

    // Then: You should get the same token twice
    ASSERT(t == t2);
    ASSERT(strcmp(t.get_contents(), "repeat") == 0);
    ASSERT(strcmp(t2.get_contents(), "repeat") == 0);
    SUCCESS();
}

void test_tokenizer_binary() {
    // Given: You have the following arithmetic expression string
    const char *expression = "1 + 2 * 5";

    // When: You tokenize the expression
    Tokenizer tok = Tokenizer();
    tok.tokenize(expression);

    // Then: You should get the tokens back in the appropriate order
    Token t = tok.get_next();
    ASSERT(t.get_type() == TokenType::OTHER);
    ASSERT(strcmp(t.get_contents(), "+") == 0);
    SUCCESS();

}

int main(int argc, char *argv[]) {
    test_tokenizer();
    test_tokenizer_complex();
    test_tokenizer_unget();
    test_tokenizer_binary();
    return 0;
}
