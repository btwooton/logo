#include <vector>
#include "../lang/procedure.hpp"
#include "../init/init_dispatch.hpp"
#include "evaluator.hpp"

static AstNode substitute_repcount(AstNode root, int repcount) {
    if (root.get_type() == NodeType::AST_REPCOUNT) {
        root.set_value<double>((double)repcount);
    }

    for (int i = 0; i < root.get_num_children(); i++) {
        root.get_children()[i] = 
            substitute_repcount(root.get_child(i), repcount);
    }
    return root;
}

AstNode evaluate(const AstNode& root) {
   NodeType type = root.get_type();
   if (type == NodeType::AST_NUMBER || type == NodeType::AST_BOOLEAN) {
       return evaluate_literal(root);
   } else if (type == NodeType::AST_FUNCALL) {
       return evaluate_funcall(root);
   } else if (type == NodeType::AST_FUNC) {
       return evaluate_fundef(root);
   } else if (type == NodeType::AST_REPEAT) {
       return evaluate_repeat(root);
   } else if (type == NodeType::AST_IF) {
       return evaluate_if(root);
   } else if (type == NodeType::AST_BRACKETED) {
       return evaluate_bracketed(root);
   } else if (type == NodeType::AST_IFELSE) {
       return evaluate_ifelse(root);
   } else if (type == NodeType::AST_OUTPUT) {
       return evaluate_output(root);
   } else if (type == NodeType::AST_STOP) {
       return evaluate_stop(root);
   } else if (type == NodeType::AST_REPCOUNT) {
       return evaluate_repcount(root);
   }
   return root;
}

AstNode evaluate_literal(const AstNode& lit) {
    return lit;
}

AstNode evaluate_funcall(const AstNode& funcall) {
   const char *name = funcall.get_value<const char *>();
   Procedure p = __dispatch_table__.get_bound_procedure(name);
   unsigned int arity = p.get_arity();
   Args a = Args();

   for (int i = 0; i < arity; i++) {
       AstNode curr_arg = evaluate(funcall.get_child(i));
       a.add_arg(AstNode(curr_arg));
   }

   Args results = p.call(a);

   Arg result_arg = results.get_arg(0);

   if (result_arg.get_type() == ArgType::ARG_NUMBER) {
       AstNode result_node = AstNode(result_arg.get_value<double>());
       return result_node;
   } else if (result_arg.get_type() == ArgType::ARG_BOOLEAN) {
       AstNode result_node = AstNode(result_arg.get_value<bool>());
       return result_node;
   } else if (result_arg.get_type() == ArgType::ARG_UNIT) {
       AstNode result_node = AstNode("()");
       return result_node;
   }
   return funcall;
}

AstNode evaluate_fundef(const AstNode& fundef) {
    const char *name = fundef.get_value<const char *>();
    std::vector<AstNode> params;
    std::vector<AstNode> body;

    for (int i = 0; i < fundef.get_num_children(); i++) {
        AstNode child = fundef.get_child(i);
       if (child.get_type() == NodeType::AST_PARAMETER) {
           params.push_back(child);
       } else {
           body.push_back(child);
       }
    }

    Procedure new_procedure = Procedure(name, params.size(), params, body);
    __dispatch_table__.add_binding(name, new_procedure);
    AstNode result = AstNode("()", NodeType::AST_UNIT);
    return result;
}

AstNode evaluate_repeat(const AstNode& repeat) {
    AstNode count_node = repeat.get_child(0);
    AstNode evaluated_count = evaluate(count_node);
    int times = (int)count_node.get_value<double>();
    AstNode result;
    for (int i = 1; i <= times; i++) {
        AstNode body_node = repeat.get_child(1);
        body_node = substitute_repcount(body_node, i);
        if (i == times) {
            result = evaluate(body_node);
        } else {
            evaluate(body_node);
        }
    }
    return result;
}

AstNode evaluate_bracketed(const AstNode& bracketed) {
    AstNode result;
    unsigned int num_children = bracketed.get_num_children();
    for (int i = 0; i < num_children; i++) {
        if (i == num_children - 1) {
            result = evaluate(bracketed.get_child(i));
        } else {
            evaluate(bracketed.get_child(i));
        }
    }
    return result;
}

AstNode evaluate_if(const AstNode& if_node) {
    AstNode conditional = if_node.get_child(0);
    AstNode bracketed = if_node.get_child(1);

    AstNode boolean = evaluate(conditional);

    bool boolean_val = boolean.get_value<bool>();

    if (boolean_val) {
        return evaluate(bracketed);
    }

    return AstNode("()");
}

AstNode evaluate_ifelse(const AstNode& ifelse_node) {
    AstNode conditional = ifelse_node.get_child(0);
    AstNode bracketed1 = ifelse_node.get_child(1);
    AstNode bracketed2 = ifelse_node.get_child(2);

    AstNode boolean = evaluate(conditional);
    bool boolean_val = boolean.get_value<bool>();

    if (boolean_val) {
        return evaluate(bracketed1);
    } else {
        return evaluate(bracketed2);
    }
}

AstNode evaluate_output(const AstNode& output) {
    return evaluate(output.get_child(0));
}

AstNode evaluate_stop(const AstNode& stop) {
    return AstNode("()");
}

AstNode evaluate_repcount(const AstNode& repcount) {
    return AstNode(repcount.get_value<double>());
}


