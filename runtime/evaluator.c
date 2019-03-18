#include <stdlib.h>
#include "../lang/procedure.h"
#include "../init/init_dispatch.h"
#include "evaluator.h"


static unsigned int __repcount__ = 0;

AstNode evaluate(AstNode root) {
   NodeType type = get_ast_type(root);
   if (type == AST_NUMBER || type == AST_BOOLEAN) {
       return evaluate_literal(root);
   } else if (type == AST_FUNCALL) {
       return evaluate_funcall(root);
   }
   return NULL;
}

AstNode evaluate_literal(AstNode lit) {
    return lit;
}

AstNode evaluate_funcall(AstNode funcall) {
   const char *name = get_ast_str_value(funcall);
   Procedure p = get_bound_procedure(__dispatch_table__, name);
   int arity = get_arity(p);
   Args a = create_args(arity);

   for (int i = 0; i < arity; i++) {
       AstNode curr_arg = evaluate(get_child(funcall, i));
       add_arg(a, create_from_ast_node(curr_arg));
       destroy_astnode(curr_arg);
   }
   Args results = call(p, a);
   destroy_args(a);

   Arg result_arg = get_arg(results, 0);

   if (get_arg_type(result_arg) == ARG_NUMBER) {
       AstNode result_node = create_number_node(get_number_value(result_arg));
       destroy_args(results);
       return result_node;
   } else if (get_arg_type(result_arg) == ARG_BOOLEAN) {
       AstNode result_node = create_boolean_node(get_boolean_value(result_arg));
       destroy_args(results);
       return result_node;
   } else if (get_arg_type(result_arg) == ARG_UNIT) {
       AstNode result_node = create_strval_node("()");
       destroy_args(results);
       return result_node;
   }
   return NULL;
}


AstNode evaluate_fundef(AstNode fundef) {
    const char *name = get_ast_str_value(fundef);
    int num_params = 0;
    int num_body = 0;

    for (int i = 0; i < get_num_children(fundef); i++) {
       if (get_ast_type(get_child(fundef, i)) == AST_PARAMETER) {
           num_params++;
       } else {
           num_body++;
       }
    }

    AstNode *params = malloc(sizeof(AstNode) * num_params);
    AstNode *body = malloc(sizeof(AstNode) * num_body);

    for (int i = 0; i < get_num_children(fundef); i++) {
        if (i < num_params) {
            params[i] = get_child(fundef, i);
        } else {
            body[i] = get_child(fundef, i);
        }
    }

    Procedure new_procedure = 
        create_procedure(name, num_params, num_body, params, body);
    add_binding(__dispatch_table__, name, new_procedure);
    AstNode result = create_strval_node("()");
    return result;
}
