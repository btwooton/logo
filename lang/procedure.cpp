#include <cassert>
#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
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
           const char *param_name = param_node.get_value<const char *>();
           std::string key = std::string(param_name);
           this->bound_arguments[key] = value_node;
       } else if (argument.get_type() == ArgType::ARG_BOOLEAN) {
           AstNode value_node = AstNode(
               argument.get_value<bool>()
           );
           AstNode param_node = this->params[i];
           const char *param_name = param_node.get_value<const char *>();
           std::string key = std::string(param_name);
           this->bound_arguments[key] = value_node;
       } else if (argument.get_type() == ArgType::ARG_STRING) {
           AstNode value_node = AstNode(
               argument.get_value<const char *>()
           );
           AstNode param_node = this->params[i];
           const char *param_name = param_node.get_value<const char *>();
           std::string key = std::string(param_name);
           this->bound_arguments[key] = value_node;
       }
   }
}

std::vector<AstNode> Procedure::substitute_bound_arguments(std::vector<AstNode> nodes_lst) {
    std::vector<AstNode> substituted_body;
    for (int i = 0; i < nodes_lst.size(); i++) {
        AstNode next_node = nodes_lst[i];
        if (next_node.get_type() == NodeType::AST_PARAMETER) {
            const char *name = next_node.get_value<const char *>();
            std::string key = std::string(name);
            if (bound_arguments.find(key) != bound_arguments.end()) {
                AstNode sub_node = bound_arguments[key];
                std::vector<AstNode> children = next_node.get_children();
                std::vector<AstNode> sub_children = 
                    substitute_bound_arguments(children);
                sub_node.set_children(sub_children);
                substituted_body.push_back(sub_node);
            }
        } else {
            std::vector<AstNode> children = next_node.get_children();
            std::vector<AstNode> sub_children = 
                substitute_bound_arguments(children);
            next_node.set_children(sub_children);
            substituted_body.push_back(next_node);
        }
    }
    return substituted_body;
}

Args Procedure::call(Args a) {
    assert(a.get_arg_count() == this->arity);
    if (this->is_native()) {
        return callable(a);
    } else {
        this->bind(a);
        std::vector<AstNode> sub = substitute_bound_arguments(body);
        Args result = Args();
        for (int i = 0; i < this->body.size(); i++) {
            AstNode body_i = evaluate(sub[i]);
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
