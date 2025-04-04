#include <cassert>
#include <cctype> 
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>
#include "token.hpp"
#include "tokenizer.hpp"

static const std::string binops = "*/+-=><";

Tokenizer::Tokenizer() {

    num_tokens = 0;
    current_token = 0;
}
        
void Tokenizer::tokenize(std::string input) {
    tokens.clear();
    current_token = 0;
    num_tokens = 0;
    const std::string delim = " \t\n\f\r[]";
    const std::string ws = " \t\n\f\r";
    std::size_t current = 0;

    while (current < input.length()) {
        if (input[current] == '[') {
            Token lbracket("[");
            tokens.push_back(lbracket);
            num_tokens++;
            current++;
            continue;
        } else if (input[current] == ']') {
            Token rbracket("]");
            tokens.push_back(rbracket);
            num_tokens++;
            current++;
            continue;
        } else if (binops.find(input[current]) != std::string::npos) {
            std::string token(1, input[current]);
            Token next_token(token);
            Token previous = tokens.back();
            tokens.pop_back();
            tokens.push_back(next_token);
            tokens.push_back(previous);
            num_tokens++;
            current++;
            continue;
        } else if (ws.find(input[current]) != std::string::npos) {
            current++;
            continue;
        } else {
            std::size_t next = input.find_first_of(delim, current);
            // if there is no delimiter, just consume until the end of the string
            if (next == std::string::npos) {
                next = input.length();
            }
            std::string token = input.substr(current, next - current);
            Token next_token(token);
            tokens.push_back(next_token);
            current = next;
            num_tokens++;
        }
    }
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
    for (int i = tok.current_token; i < tok.tokens.size(); i++) {
        out << tok.tokens[i].get_contents() << " ";
    }
    out << "\n";
    return out;
}
