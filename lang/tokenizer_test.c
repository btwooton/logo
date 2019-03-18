#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "tokenizer.h"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in test %s\n", __LINE__, __func__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);

void test_tokenizer() {
    // Given: You have created a Tokenizer
    Tokenizer tok = create_tokenizer();

    // When: You tokenize the following string
    char *string = malloc(sizeof(char) * (strlen("Hello World!") + 1));
    strcpy(string, "Hello World!");
    tokenize(tok, string);

    // Then: You should be able to get the appropriate tokens back
    Token t1 = get_next(tok);
    Token t2 = get_next(tok);

    ASSERT(get_type(t1) == OTHER);
    ASSERT(get_type(t2) == OTHER);
    ASSERT(strcmp(get_contents(t1), "Hello") == 0);
    ASSERT(strcmp(get_contents(t2), "World!") == 0);
    destroy_tokenizer(tok);
    free(string);
    SUCCESS();
}

void test_tokenizer_complex() {
    // Given: You have the following expression string
    const char *expression = "repeat 4 [ forward 5 * repcount right 90 ]";
    
    // When: You tokenize the string
    Tokenizer tok = create_tokenizer();
    tokenize(tok, expression);

    // Then: You should have the correct tokens
    Token t1 = get_next(tok);
    Token t2 = get_next(tok);
    Token t3 = get_next(tok);
    Token t4 = get_next(tok);
    Token t5 = get_next(tok);
    Token t6 = get_next(tok);
    Token t7 = get_next(tok);
    Token t8 = get_next(tok);
    Token t9 = get_next(tok);
    Token t10 = get_next(tok);

    ASSERT(get_type(t1) == REPEAT);
    ASSERT(get_type(t2) == NUMBER);
    ASSERT(get_type(t3) == OPEN_SQUARE);
    ASSERT(get_type(t4) == OTHER);
    ASSERT(get_type(t5) == OTHER);
    ASSERT(get_type(t6) == NUMBER);
    ASSERT(get_type(t7) == REPCOUNT);
    ASSERT(get_type(t8) == OTHER);
    ASSERT(get_type(t9) == NUMBER);
    ASSERT(get_type(t10) == CLOSED_SQUARE);

    ASSERT(strcmp(get_contents(t1), "repeat") == 0);
    ASSERT(strcmp(get_contents(t2), "4") == 0);
    ASSERT(strcmp(get_contents(t3), "[") == 0);
    ASSERT(strcmp(get_contents(t4), "forward") == 0);
    ASSERT(strcmp(get_contents(t5), "*") == 0);
    ASSERT(strcmp(get_contents(t6), "5") == 0);
    ASSERT(strcmp(get_contents(t7), "repcount") == 0);
    ASSERT(strcmp(get_contents(t8), "right") == 0);
    ASSERT(strcmp(get_contents(t9), "90") == 0);
    ASSERT(strcmp(get_contents(t10), "]") == 0);
    destroy_tokenizer(tok);
    SUCCESS();
}

void test_tokenizer_unget() {
    // Given: You have the following expression string
    const char *expression = "repeat 5 [ forward 100 right 90 ]";

    // When: You tokenize, get, unget, and get again
    Tokenizer tok = create_tokenizer();
    tokenize(tok, expression);

    Token t = get_next(tok);
    unget(tok);
    Token t2 = get_next(tok);

    // Then: You should get the same token twice
    ASSERT(t == t2);
    ASSERT(strcmp(get_contents(t), "repeat") == 0);
    ASSERT(strcmp(get_contents(t2), "repeat") == 0);
    SUCCESS();
}

void test_tokenizer_binary() {
    // Given: You have the following arithmetic expression string
    const char *expression = "1 + 2 * 5";

    // When: You tokenize the expression
    Tokenizer tok = create_tokenizer();
    tokenize(tok, expression);

    // Then: You should get the tokens back in the appropriate order
    Token t = get_next(tok);
    ASSERT(get_type(t) == OTHER);
    ASSERT(strcmp(get_contents(t), "+") == 0);
    SUCCESS();

}

int main(int argc, char *argv[]) {
    test_tokenizer();
    test_tokenizer_complex();
    test_tokenizer_unget();
    test_tokenizer_binary();
    return 0;
}
