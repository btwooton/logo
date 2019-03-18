#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "arg.h"

struct Arg {

    ArgType type;

    union Data {
        double number;
        char *string;
        bool boolean;
    } data;

};

Arg create_dummy_argument(ArgType type) {
    Arg result = malloc(sizeof(struct Arg));
    result->type = type;

    switch(type) {
        case ARG_NUMBER:
            result->data.number = 0.0;
            break;
        case ARG_STRING:
            result->data.string = malloc(sizeof(char) * 2);
            strcpy(result->data.string, "");
            break;
        case ARG_BOOLEAN:
            result->data.boolean = false;
            break;
        case ARG_UNIT:
            result->data.string = malloc(sizeof(char) * 3);
            strcpy(result->data.string, "()");
            break;
    }

    return result;
}

Arg create_number_argument(double number) {
    Arg result = malloc(sizeof(struct Arg));
    result->type = ARG_NUMBER;
    result->data.number = number;
    return result;
}

Arg create_string_argument(const char *string) {
    Arg result = malloc(sizeof(struct Arg));
    result->type = ARG_STRING;
    result->data.string = malloc(sizeof(char) * (strlen(string) + 1));
    strcpy(result->data.string, string);
    return result;
}

Arg create_bool_argument(bool boolean) {
    Arg result = malloc(sizeof(struct Arg));
    result->type = ARG_BOOLEAN;
    result->data.boolean = boolean;
    return result;
}

Arg create_from_ast_node(AstNode node) {
    NodeType type = get_ast_type(node);
    assert(type == AST_NUMBER || type == AST_BOOLEAN);
    Arg result = malloc(sizeof(struct Arg));

    if (type == AST_NUMBER) {
        result->type = ARG_NUMBER;
        result->data.number = get_ast_number_value(node);
    } else if {
        result->type = ARG_BOOLEAN;
        result->data.boolean = get_ast_bool_value(node);
    } else {
        result->type = ARG_UNIT;
        result->data.string = malloc(sizeof(char) * 3);
        strcpy(result->data.string, "()");
    }

    return result;
}
void destroy_argument(Arg argument) {
    if (argument->type == ARG_STRING) {
        free(argument->data.string);
    }
    free(argument);
}

double get_number_value(Arg argument) {
    assert(argument->type == ARG_NUMBER);
    return argument->data.number;
}

const char *get_string_value(Arg argument) {
    assert(argument->type == ARG_STRING || argument->type == ARG_UNIT);
    return argument->data.string;
}

bool get_boolean_value(Arg argument) {
    assert(argument->type == ARG_BOOLEAN);
    return argument->data.boolean;
}

ArgType get_arg_type(Arg argument) {
    return argument->type;
}
