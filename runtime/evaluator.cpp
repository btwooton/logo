#include <vector>
#include "../lang/procedure.hpp"
#include "../init/init_dispatch.hpp"
#include "evaluator.hpp"


static unsigned int __repcount__ = 0;

AstNode evaluate(const AstNode& root) {
   NodeType type = root.get_type();
   if (type == NodeType::AST_NUMBER || type == NodeType::AST_BOOLEAN) {
       return evaluate_literal(root);
   } else if (type == NodeType::AST_FUNCALL) {
       return evaluate_funcall(root);
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
