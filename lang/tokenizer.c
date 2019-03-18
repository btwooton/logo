#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "token.h"
#include "tokenizer.h"

static const char *binops = "*/+-=><";

struct Tokenizer {
    Token *tokens;
    int current_token;
    int num_tokens;
}; 

Tokenizer create_tokenizer() {
    Tokenizer result = malloc(sizeof(struct Tokenizer));
    result->tokens = NULL;
    result->current_token = 0;
    result->num_tokens = 0;
    return result;
}

void destroy_tokenizer(Tokenizer t) {
    for (int i = 0; i < t->num_tokens; i++) {
        destroy_token(t->tokens[i]);
    }
    free(t);
}

void tokenize(Tokenizer t, const char *string) {
    int num_tokens = 0;
    bool in_token = false; 
    for (int i = 0; i < strlen(string); i++) {
        if (in_token && isspace(string[i])) {
            num_tokens++;
            in_token = false;
        } else if (!in_token && !isspace(string[i])) {
            in_token = true;
        }
    }

    if (in_token) {
        in_token = false;
        num_tokens++;
    }

    if (t->tokens != NULL) {
        for (int i = 0; i < t->num_tokens; i++) {
            destroy_token(t->tokens[i]);
        }
        free(t->tokens);
    }
    t->num_tokens = 0;
    t->current_token = 0;
    t->tokens = malloc(sizeof(Token) * num_tokens);
    char *copy_string = malloc(sizeof(char) * (strlen(string) + 1));
    strcpy(copy_string, string);
    const char *delim = " \t\n\f\r";
    char *pch = strtok(copy_string, delim);
    
    while (pch != NULL) {
        Token next = create_token(pch);
        if (strstr(binops, pch) != NULL) {
            Token temp = t->tokens[t->num_tokens - 1];
            t->tokens[t->num_tokens - 1] = next;
            t->tokens[t->num_tokens++] = temp;
        } else {
            t->tokens[t->num_tokens++] = next;
        }
        pch = strtok(NULL, delim);
    }
    free(copy_string);
}

Token get_next(Tokenizer t) {
    if (!has_next(t)) {
        return NULL;
    }
    return t->tokens[t->current_token++];
}

void unget(Tokenizer t) {
    assert(t->current_token > 0);
    t->current_token--;
}

Token peek_next(Tokenizer t) {
    if (!has_next(t)) {
        return NULL;
    }
    return t->tokens[t->current_token];
}

bool has_next(Tokenizer t) {
    return t->current_token < t->num_tokens;
}
