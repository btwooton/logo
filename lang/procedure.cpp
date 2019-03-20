#include <cassert>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include "args.hpp"
#include "procedure.hpp"
#include "../runtime/evaluator.hpp"


Procedure::Procedure() {
    this->name = "";
    this->arity = 0;
    this->callable = nullptr;
}

Procedure::Procedure(const char *name, unsigned int arity, Args (*fun)(Args)) {
    this->name = std::string(name);
    this->arity = arity;
    this->callable = fun;
}

Procedure::Procedure(const char *name, unsigned int arity,
        std::vector<AstNode> params, std::vector<AstNode> body) {
    this->name = std::string(name);
    this->arity = arity;
    this->callable = nullptr;
    this->params = params;
    this->body = body;
}

void Procedure::bind(Args a) {
   for (int i = 0; i < a.get_arg_count(); i++) {
       Arg argument = a.get_arg(i);
       if (argument.get_type() == ArgType::ARG_NUMBER) {
           AstNode value_node = AstNode(
                   argument.get_value<double>()
            );
           AstNode param_node = this->params[i];
           this->bound_arguments[param_node] = value_node;
       } else if (argument.get_type() == ArgType::ARG_BOOLEAN) {
           AstNode value_node = AstNode(
               argument.get_value<bool>()
           );
           AstNode param_node = this->params[i];
           this->bound_arguments[param_node] = value_node;
       } else if (argument.get_type() == ArgType::ARG_STRING) {
           AstNode value_node = AstNode(
               argument.get_value<const char *>()
           );
           AstNode param_node = this->params[i];
           this->bound_arguments[param_node] = value_node;
       }
   }

   this->substitute_bound_arguments(this->body);
}

void Procedure::substitute_bound_arguments(std::vector<AstNode> nodes_lst) {
    for (int i = 0; i < nodes_lst.size(); i++) {
        AstNode next_node = nodes_lst[i];
        if (this->bound_arguments.find(next_node) != bound_arguments.end()) {
            AstNode sub_node = bound_arguments[next_node];
            sub_node.set_children(next_node.get_children());
            this->substitute_bound_arguments(sub_node.get_children());
            nodes_lst[i] = sub_node;
        }
    }
}

Args Procedure::call(Args a) {
    assert(a.get_arg_count() == this->arity);
    if (this->is_native()) {
        return callable(a);
    } else {
        this->bind(a);
        Args result = Args();
        for (int i = 0; i < this->body.size(); i++) {
            AstNode body_i = evaluate(this->body[i]);
            result.add_arg(Arg(body_i)); 
        }
        return result;
    }
}

const char *Procedure::get_name() const {
    return name.c_str();
}

unsigned int Procedure::get_arity() const {
    return arity;
}

bool Procedure::is_native() const {
    return callable != nullptr;
}

bool Procedure::operator==(const Procedure& other) const {
    return this->name == other.name &&
           this->callable == other.callable &&
           this->arity == other.arity;
}

bool Procedure::operator!=(const Procedure& other) const {
    return !this->operator==(other);
}
