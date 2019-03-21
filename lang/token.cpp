#include <cstdlib>
#include <cctype>
#include <cstring>
#include <string>
#include "token.hpp"

static bool is_numeric(const char *string) {
    int point_count = 0;
    for (int i = 0; i < strlen(string); i++) {
        if (!isdigit(string[i])) {
            if (string[i] != '.') {
                return false;
            } else {
                point_count++;
            }
            if (point_count > 1) {
                return false;
            }
        }
    }
    return true;
}

Token::Token() : contents(""), type(TokenType::OTHER) {}

Token::Token(std::string contents) : contents(contents) {

    const char *ccontents = contents.c_str();
    if (is_numeric(ccontents)) {
        type = TokenType::NUMBER;
    } else if (strcmp(ccontents, "to") == 0) {
        type = TokenType::TO;
    } else if (strcmp(ccontents, "end") == 0) {
        type = TokenType::END;
    } else if (strcmp(ccontents, "repeat") == 0) {
        type = TokenType::REPEAT;
    } else if (strcmp(ccontents, "stop") == 0) {
        type = TokenType::STOP;
    } else if (strcmp(ccontents, "repcount") == 0) {
        type = TokenType::REPCOUNT;
    } else if (strcmp(ccontents, "output") == 0) {
        type = TokenType::OUTPUT;
    } else if (strcmp(ccontents, "false") == 0 
            || strcmp(ccontents, "true") == 0) {
        type = TokenType::BOOLEAN;
    } else if (strcmp(ccontents, "[") == 0) {
        type = TokenType::OPEN_SQUARE;
    } else if (strcmp(ccontents, "]") == 0) {
        type = TokenType::CLOSED_SQUARE;
    } else if (strcmp(ccontents, "if") == 0) {
        type = TokenType::IF;
    } else if (strcmp(ccontents, "ifelse") == 0) {
        type = TokenType::IFELSE;
    } else if (ccontents[0] == ':') {
        type = TokenType::PARAMETER;
    } else {
        type = TokenType::OTHER;
    }
    
}


TokenType Token::get_type() const {
    return type;
}

const char* Token::get_contents() const {
    return contents.c_str();
}

bool Token::operator==(const Token& other) const {
    return this->contents == other.contents;
}

bool Token::operator!=(const Token& other) const {
    return this->contents != other.contents;
}