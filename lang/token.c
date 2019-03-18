#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "token.h"

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

struct Token {
    char *contents;
    TokenType type;
};

Token create_token(const char *contents) {
    Token result = malloc(sizeof(struct Token));
    result->contents = malloc(sizeof(char) * (strlen(contents) + 1));
    strcpy(result->contents, contents);

    if (is_numeric(contents)) {
        result->type = NUMBER;
    } else if (strcmp(contents, "to") == 0) {
        result->type = TO;
    } else if (strcmp(contents, "end") == 0) {
        result->type = END;
    } else if (strcmp(contents, "repeat") == 0) {
        result->type = REPEAT;
    } else if (strcmp(contents, "stop") == 0) {
        result->type = STOP;
    } else if (strcmp(contents, "repcount") == 0) {
        result->type = REPCOUNT;
    } else if (strcmp(contents, "output") == 0) {
        result->type = OUTPUT;
    } else if (strcmp(contents, "false") == 0 
            || strcmp(contents, "true") == 0) {
        result->type = BOOLEAN;
    } else if (strcmp(contents, "[") == 0) {
        result->type = OPEN_SQUARE;
    } else if (strcmp(contents, "]") == 0) {
        result->type = CLOSED_SQUARE;
    } else if (strcmp(contents, "if") == 0) {
        result->type = IF;
    } else if (contents[0] == ':') {
        result->type = PARAMETER;
    } else {
        result->type = OTHER;
    }
    
    return result;
}

void destroy_token(Token t) {
    free(t->contents);
    free(t);
}

TokenType get_type(Token t) {
    return t->type;
}

const char *get_contents(Token t) {
    return t->contents;
}
