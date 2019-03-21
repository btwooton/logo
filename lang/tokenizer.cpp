#include <cassert>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>
#include "token.hpp"
#include "tokenizer.hpp"

static const char *binops = "*/+-=><";

Tokenizer::Tokenizer() {

    num_tokens = 0;
    current_token = 0;
}
        
void Tokenizer::tokenize(const char *string) {
    tokens.clear();
    current_token = 0;
    num_tokens = 0;
    char *copy_string = (char *)malloc(sizeof(char) * (strlen(string) + 1));
    strcpy(copy_string, string);
    const char *delim = " \t\n\f\r";
    char *pch = strtok(copy_string, delim);

    while (pch != NULL) {
        Token next = Token(std::string(pch));
        if (strstr(binops, pch) != NULL) {
            Token temp = tokens[num_tokens - 1];
            tokens[num_tokens - 1] = next;
            tokens.push_back(temp);
            num_tokens++;
        } else {
            tokens.push_back(next);
            num_tokens++;
        }
        pch = strtok(NULL, delim);
    }
    free(copy_string);
}


void Tokenizer::unget() {
    current_token--;
}

Token Tokenizer::get_next() {
    if (!has_next()) {
        throw std::out_of_range("Tokenizer is out of Tokens");
    }
    return tokens[current_token++];
}

Token Tokenizer::peek_next() {
    Token result = get_next();
    current_token--;
    return result;
}

bool Tokenizer::has_next() const {
    return current_token < num_tokens;
}

std::ostream& operator<<(std::ostream& out, const Tokenizer& tok) {
    for (int i = 0; i < tok.tokens.size(); i++) {
        out << tok.tokens[i].get_contents() << " ";
    }
    out << "\n";
    return out;
}