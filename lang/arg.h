#ifndef ARG_H_
#define ARG_H_
#include "ast_node.h"
#include <stdbool.h>

typedef enum ArgType {
    ARG_NUMBER,
    ARG_STRING,
    ARG_BOOLEAN,
    ARG_UNIT,
} ArgType;

typedef struct Arg *Arg;

extern Arg create_dummy_argument(ArgType type);
extern Arg create_number_argument(double number);
extern Arg create_string_argument(const char *string);
extern Arg create_bool_argument(bool boolean);
extern Arg create_from_ast_node(AstNode node);

extern void destroy_argument(Arg argument);

extern double get_number_value(Arg argument);
extern const char *get_string_value(Arg argument);
extern bool get_boolean_value(Arg argument);
extern ArgType get_arg_type(Arg argument);

#endif
