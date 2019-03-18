#include <cstdio>
#include <cassert>
#include <string>
#include "token.hpp"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in test %s\n", __LINE__, __func__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);

void test_create_token_valid() {
    // Given: You have created a Token with a validly formatted number
    Token number_token = Token("125.6");

    // When: You check its type
    TokenType type = number_token.get_type();
    // Then: The type of the token should be NUMBER
    ASSERT(type == TokenType::NUMBER);
    SUCCESS();
}

void test_create_token_invalid() {
    // Given: You have created a Token with an invalidly formatted number
    Token invalid_token = Token("125.6.7");

    // When: You check its type
    TokenType type = invalid_token.get_type();

    // Then: The type of the token should be OTHER
    ASSERT(type == TokenType::OTHER);
    SUCCESS();
}

void test_create_token_invalid_alpha() {
    // Given: You have created a Token that has alphabetical characters
    Token invalid_token = Token("152.3f");

    // When: You check its type
    TokenType type = invalid_token.get_type();

    // Then: The type of the token should be OTHER
    ASSERT(type == TokenType::OTHER);
    SUCCESS();
}

void test_create_token_to() {
    // Given: You have created a Token that has the contents "to"
    Token to_token = Token("to");

    // When: You check its type
    TokenType type = to_token.get_type();

    // Then: The type of the token should be TO
    ASSERT(type == TokenType::TO);
    SUCCESS();
}

void test_create_token_end() {
    // Given: You have created a Token that has the contents "end"
    Token end_token = Token("end");

    // When: You check its type
    TokenType type = end_token.get_type();

    // Then: The type of the token should be END
    ASSERT(type == TokenType::END);
    SUCCESS();
}

void test_create_token_sb() {
    // Given: You have created Tokens that have square brackets
    Token open_token = Token("[");
    Token closed_token = Token("]");

    // When: You check their types
    TokenType open_type = open_token.get_type();
    TokenType closed_type = closed_token.get_type();

    // Then: Their types should have the correct values
    ASSERT(open_type == TokenType::OPEN_SQUARE);
    ASSERT(closed_type == TokenType::CLOSED_SQUARE);
    SUCCESS();
}

void test_create_token_param() {
    // Given: You have created a Token that holds a paremeter
    Token param_token = Token(":length");

    // When: You check its type
    TokenType type = param_token.get_type();

    // Then: Its type should be PARAMETER
    ASSERT(type == TokenType::PARAMETER);
    SUCCESS();
}

void test_create_token_repeat() {
    // Given: You have created Tokens that contain "repeat" and "repcount"
    Token repeat_token = Token("repeat");
    Token repcnt_token = Token("repcount");

    // When: You check their types
    TokenType repeat_type = repeat_token.get_type();
    TokenType repcnt_type = repcnt_token.get_type();

    // Then: They should have the correct types
    ASSERT(repeat_type == TokenType::REPEAT);
    ASSERT(repcnt_type == TokenType::REPCOUNT);
    SUCCESS();
}

void test_create_token_stop_output() {
    // Given: You have created Tokens that contain "stop" and "output"
    Token stop_token = Token("stop");
    Token output_token = Token("output");

    // When: You check their types
    TokenType stop_type = stop_token.get_type();
    TokenType output_type = output_token.get_type();

    // Then: They should have the correct types
    ASSERT(stop_type == TokenType::STOP);
    ASSERT(output_type == TokenType::OUTPUT);
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
