#ifndef PROCEDURE_H_
#define PROCEDURE_H_
#include <stdbool.h>
#include "args.h"
#include "ast_node.h"

typedef struct Procedure *Procedure;

extern Procedure create_native(const char *name, int arity, Args (*fun)(Args));
extern Procedure create_procedure(const char *name, int arity, 
        AstNode *params, AstNode *body);
extern Args call(Procedure p, Args a);
extern void destroy_procedure(Procedure p);
extern const char *get_name(Procedure p);
extern int get_arity(Procedure p);
extern bool is_native(Procedure p);

#endif
