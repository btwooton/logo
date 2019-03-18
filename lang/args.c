#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "args.h"

struct Args {
    Arg *argv;
    int argc;
    int curr_arg;
};

Args create_args(int argc) {
    Args result = malloc(sizeof(struct Args));
    result->argc = argc;
    result->curr_arg = 0;
    result->argv = malloc(sizeof(Arg) * argc);
    for (int i = 0; i < argc; i++) {
        result->argv[i] = NULL;
    }
    return result;
}

void add_arg(Args args, Arg arg) {
    assert(args->curr_arg < args->argc);
    args->argv[args->curr_arg++] = arg;
}

int get_arg_count(Args args) {
    return args->argc;
}

Arg get_arg(Args args, int index) {
    assert(index >= 0 && index < args->argc);
    return args->argv[index];
}

void destroy_args(Args args) {
    for (int i = 0; i < args->argc; i++) {
        if (args->argv[i]) {
            destroy_argument(args->argv[i]);
        }
    }
    free(args);
}
