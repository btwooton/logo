#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "token.h"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in test %s\n", __LINE__, __func__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);

void test_create_token_valid() {
    // Given: You have created a Token with a validly formatted number
    Token number_token = create_token("125.6");

    // When: You check its type
    TokenType type = get_type(number_token);
    // Then: The type of the token should be NUMBER
    ASSERT(type == NUMBER);
    SUCCESS();
}

void test_create_token_invalid() {
    // Given: You have created a Token with an invalidly formatted number
    Token invalid_token = create_token("125.6.7");

    // When: You check its type
    TokenType type = get_type(invalid_token);

    // Then: The type of the token should be OTHER
    ASSERT(type == OTHER);
    SUCCESS();
}

void test_create_token_invalid_alpha() {
    // Given: You have created a Token that has alphabetical characters
    Token invalid_token = create_token("152.3f");

    // When: You check its type
    TokenType type = get_type(invalid_token);

    // Then: The type of the token should be OTHER
    ASSERT(type == OTHER);
    SUCCESS();
}

void test_create_token_to() {
    // Given: You have created a Token that has the contents "to"
    Token to_token = create_token("to");

    // When: You check its type
    TokenType type = get_type(to_token);

    // Then: The type of the token should be TO
    ASSERT(type == TO);
    SUCCESS();
}

void test_create_token_end() {
    // Given: You have created a Token that has the contents "end"
    Token end_token = create_token("end");

    // When: You check its type
    TokenType type = get_type(end_token);

    // Then: The type of the token should be END
    ASSERT(type == END);
    SUCCESS();
}

void test_create_token_sb() {
    // Given: You have created Tokens that have square brackets
    Token open_token = create_token("[");
    Token closed_token = create_token("]");

    // When: You check their types
    TokenType open_type = get_type(open_token);
    TokenType closed_type = get_type(closed_token);

    // Then: Their types should have the correct values
    ASSERT(open_type == OPEN_SQUARE);
    ASSERT(closed_type == CLOSED_SQUARE);
    SUCCESS();
}

void test_create_token_param() {
    // Given: You have created a Token that holds a paremeter
    Token param_token = create_token(":length");

    // When: You check its type
    TokenType type = get_type(param_token);

    // Then: Its type should be PARAMETER
    ASSERT(type == PARAMETER);
    SUCCESS();
}

void test_create_token_repeat() {
    // Given: You have created Tokens that contain "repeat" and "repcount"
    Token repeat_token = create_token("repeat");
    Token repcnt_token = create_token("repcount");

    // When: You check their types
    TokenType repeat_type = get_type(repeat_token);
    TokenType repcnt_type = get_type(repcnt_token);

    // Then: They should have the correct types
    ASSERT(repeat_type == REPEAT);
    ASSERT(repcnt_type == REPCOUNT);
    SUCCESS();
}

void test_create_token_stop_output() {
    // Given: You have created Tokens that contain "stop" and "output"
    Token stop_token = create_token("stop");
    Token output_token = create_token("output");

    // When: You check their types
    TokenType stop_type = get_type(stop_token);
    TokenType output_type = get_type(output_token);

    // Then: They should have the correct types
    ASSERT(stop_type == STOP);
    ASSERT(output_type == OUTPUT);
    SUCCESS();
}

int main(int argc, char *argv[]) {

    test_create_token_valid();
    test_create_token_invalid();
    test_create_token_invalid_alpha();
    test_create_token_to();
    test_create_token_end();
    test_create_token_sb();
    test_create_token_param();
    test_create_token_repeat();
    test_create_token_stop_output();
    return 0;
}
