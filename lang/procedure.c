#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"
#include "procedure.h"
#include "../runtime/evaluator.h"

struct Procedure {
    char *name;
    int arity;
    int nbody;
    Args (*fun)(Args);
    AstNode *parameters;
    AstNode *body_exprs;
};

Procedure create_native(const char *name, int arity, Args (*fun)(Args)) {
    Procedure result = malloc(sizeof(struct Procedure));
    char *copy_name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(copy_name, name);
    result->name = copy_name;
    result->arity = arity;
    result->nbody = 0;
    result->fun = fun;
    result->parameters = NULL;
    result->body_exprs = NULL;
    return result;
}

Procedure create_procedure(const char *name, int arity, int nbody, 
        AstNode *params, AstNode *body) {
    Procedure result = malloc(sizeof(struct Procedure));
    char *copy_name = malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(copy_name, name);
    result->name = copy_name;
    result->arity = arity;
    result->nbody = nbody;
    result->fun = NULL;
    result->parameters = params;
    result->body_exprs = body;
    return result;
}

static void bind(Procedure p, Args a) {
   for (int i = 0; i < get_arg_count(a); i++) {
       Arg argument = get_arg(a, i);
       if (get_arg_type(argument) == ARG_NUMBER) {
           AstNode value_node = create_number_node(
                   get_number_value(argument)
                   );
           AstNode param_node = p->parameters[i];
           substitute(
       }
   }

}

Args call(Procedure p, Args a) {
    assert(get_arg_count(a) == p->arity);
    if (is_native(p)) {
        return (*p->fun)(a);
    } else {
        bind(p, a);
        Args result = create_args(p->nbody);
        for (int i = 0; i < p->nbody; i++) {
            AstNode body_i = evaluate(p->body_exprs[i]);
            add_arg(result, create_from_ast_node(body_i)); 
        }
        return result;
    }
}

void destroy_procedure(Procedure p) {
    free(p->name);
    free(p);
}

const char *get_name(Procedure p) {
    return p->name;
}

int get_arity(Procedure p) {
    return p->arity;
}

bool is_native(Procedure p) {
    return p->fun != NULL;
}
