#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <functional>
#include <stdexcept>
#include <iostream>
#include "ast_node.hpp" 

std::string node_type_to_string(NodeType type) {
    switch (type) {
        case NodeType::AST_UNIT:
            return "AST_UNIT";
        case NodeType::AST_NUMBER:
            return "AST_NUMBER";
        case NodeType::AST_BOOLEAN:
            return "AST_BOOLEAN";
        case NodeType::AST_STRING:
            return "AST_STRING";
        case NodeType::AST_IDENTIFIER:
            return "AST_IDENTIFIER";
        case NodeType::AST_PARAMETER:
            return "AST_PARAMETER";
        case NodeType::AST_REPEAT:
            return "AST_REPEAT";
        case NodeType::AST_FUNCALL:
            return "AST_FUNCALL";
        case NodeType::AST_FUNC:
            return "AST_FUNC";
        case NodeType::AST_IF:
            return "AST_IF";
        case NodeType::AST_IFELSE:
            return "AST_IFELSE";
        case NodeType::AST_OUTPUT:
            return "AST_OUTPUT";
        case NodeType::AST_STOP:
            return "AST_STOP";
        case NodeType::AST_REPCOUNT:
            return "AST_REPCOUNT";
        case NodeType::AST_BRACKETED:
            return "AST_BRACKETED";
    }
    return "";
}

AstNode::AstNode() {
    this->type = NodeType::AST_UNIT;
    new (&string) std::string("()");
}

AstNode::AstNode(double other) {
    this->type = NodeType::AST_NUMBER;
    new (&number) double(other);
}

AstNode::AstNode(bool other) {
    this->type = NodeType::AST_BOOLEAN;
    new (&boolean) bool(other);
}

AstNode::AstNode(const char *contents) {
    new (&string) std::string(contents);

    if (contents[0] == ':') {
        this->type = NodeType::AST_PARAMETER;
    } else if (contents[0] == '"' || contents[0] == '\'') {
        this->type = NodeType::AST_STRING;
    } else if (strcmp(contents, "repeat") == 0) {
        this->type = NodeType::AST_REPEAT;
    } else if (strcmp(contents, "if") == 0) {
        this->type = NodeType::AST_IF;
    } else if (strcmp(contents, "ifelse") == 0) {
        this->type = NodeType::AST_IFELSE;
    } else if (strcmp(contents, "output") == 0) {
        this->type = NodeType::AST_OUTPUT;
    } else if (strcmp(contents, "stop") == 0) {
        this->type = NodeType::AST_STOP;
    } else if (strcmp(contents, "()") == 0) {
        this->type = NodeType::AST_UNIT;
    } else {
        this->type = NodeType::AST_IDENTIFIER;
    }

}

AstNode::AstNode(const char *contents, NodeType type) {
    this->type = type;
    new (&string) std::string(contents);
}

AstNode::AstNode(NodeType type) {
    this->type = type;

    switch (type) {
        case NodeType::AST_REPCOUNT:
            new (&number) double(0);
            break;
        case NodeType::AST_BOOLEAN:
            new (&boolean) bool(false);
            break;
        case NodeType::AST_NUMBER:
            new (&number) double(0);
            break;
        case NodeType::AST_BRACKETED:
            new (&string) std::string("bracketed");
            break;
        default:
            new (&string) std::string("INVALID");
            break;
    }
}

AstNode::AstNode(const AstNode& other) : type(other.type) {

    children = other.children;

    switch (type) {
        case NodeType::AST_NUMBER:
            new (&number) double(other.number);
            break;
        case NodeType::AST_BOOLEAN:
            new (&boolean) bool(other.boolean);
            break;
        case NodeType::AST_REPCOUNT:
            new (&number) double(other.number);
            break;
        default:
            new (&string) std::string(other.string);
            break;
    }
}

AstNode::AstNode(AstNode&& other) {
    this->type = other.type;
    this->children = std::move(other.children);

    switch (type) {
        case NodeType::AST_NUMBER:
            new (&number) double(std::move(other.number));
            break;
        case NodeType::AST_BOOLEAN:
            new (&boolean) bool(std::move(other.boolean));
            break;
        case NodeType::AST_REPCOUNT:
            new (&number) double(std::move(other.number));
            break;
        default:
            new (&string) std::string(std::move(other.string));
            break;
    }
}

AstNode::~AstNode() {
    switch (type) {
        case NodeType::AST_NUMBER:
            break;
        case NodeType::AST_BOOLEAN:
            break;
        case NodeType::AST_REPCOUNT:
            break;
        default:
            this->string.~basic_string<char>();
            break;
    }
}

NodeType AstNode::get_type() const {
   return type; 
}

template <> double AstNode::get_value() const {
    if (type != NodeType::AST_NUMBER && type != NodeType::AST_REPCOUNT) {
        throw std::runtime_error("Invalid type for double get_value(), actual type: " + node_type_to_string(type));
    }
    return number;
}

template <> bool AstNode::get_value() const {
    if (type != NodeType::AST_BOOLEAN) {
        throw std::runtime_error("Invalid type for bool get_value(), actual type: " + node_type_to_string(type));
    }
    return boolean;
}

template <> const char *AstNode::get_value() const {
    if (type == NodeType::AST_BOOLEAN || type == NodeType::AST_NUMBER || type == NodeType::AST_REPCOUNT) {
        throw std::runtime_error("Invalid type for string get_value(), actual type: " + node_type_to_string(type));
    }
    return string.c_str();
}

template <> void AstNode::set_value(double new_value) {
    if (type != NodeType::AST_NUMBER && type != NodeType::AST_REPCOUNT) {
        throw std::runtime_error("Invalid type for set_value(double), actual type: " + node_type_to_string(type));
    }
    number = new_value;
}

template <> void AstNode::set_value(bool new_value) {
    if (type != NodeType::AST_BOOLEAN) {
        throw std::runtime_error("Invalid type for set_value(bool)");
    }
    boolean = new_value;
}

template <> void AstNode::set_value(const char *new_value) {
    if (type == NodeType::AST_BOOLEAN || 
        type == NodeType::AST_NUMBER || 
        type == NodeType::AST_REPCOUNT) {
        throw std::runtime_error("Invalid type for set_value(const char *)");
    }
    string = std::string(new_value);
}

void AstNode::add_child(AstNode child) {
    children.push_back(child);
}

AstNode AstNode::get_child(unsigned int index) const {
    if (index >= children.size()) {
        throw std::out_of_range("Index out of range");
    }
    return children[index];
}

AstNode AstNode::set_child(AstNode child, unsigned int index) {
    if (index >= children.size()) {
        throw std::out_of_range("Index out of range");
    }
    AstNode result = children[index];
    children[index] = child;
    return result;
}

unsigned int AstNode::get_num_children() const {
    return children.size();
}

AstNode& AstNode::operator=(const AstNode& other) {

    if (&other == this) {
        return *this;
    }

    this->type = other.type;

    this->children = other.children;

    switch (this->type) {
        case NodeType::AST_NUMBER:
            this->number = other.number;
            break;
        case NodeType::AST_BOOLEAN:
            this->boolean = other.boolean;
            break;
        case NodeType::AST_REPCOUNT:
            this->number = other.number;
            break;
        default:
            this->string = other.string;
            break;
    }
    return *this;
}

AstNode& AstNode::operator=(AstNode&& other) {
    this->type = other.type;

    this->children = std::move(other.children);

    switch (this->type) {
        case NodeType::AST_NUMBER:
            this->number = std::move(other.number);
            break;
        case NodeType::AST_BOOLEAN:
            this->boolean = std::move(other.boolean);
            break;
        case NodeType::AST_REPCOUNT:
            this->number = std::move(other.number);
            break;
        default:
            this->string = std::move(other.string);
            break;
    }

    return *this;
}

bool AstNode::operator==(const AstNode& other) const {
    if (other.type != this->type) {
        return false;
    }

    switch (this->type) {
        case NodeType::AST_BOOLEAN:
            return this->boolean == other.boolean;
            break;
        case NodeType::AST_NUMBER:
            return this->number == other.number;
            break;
        default:
            return this->string == other.string;
            break;
    }

    return false;
}

bool AstNode::operator!=(const AstNode& other) const {
    return !this->operator==(other);
}

std::ostream& output_recursive(std::ostream& out, const AstNode& node, std::string tab_string) {
  switch (node.type) {
        case NodeType::AST_NUMBER:
            out << tab_string << node.get_value<double>() << "\n";
            break;
        case NodeType::AST_BOOLEAN:
            out << tab_string << node.get_value<bool>() << "\n";
            break;
        default:
            out << tab_string << node.get_value<const char *>() << "\n";
    }
    std::string next_tab = tab_string + "\t";
    for (int i = 0; i < node.children.size(); i++) {
        output_recursive(out, node.children[i], next_tab);
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const AstNode& node) {
  return output_recursive(out, node, "");
}

void AstNode::set_children(std::vector<AstNode> new_children) {
    this->children = new_children;
}

std::vector<AstNode>& AstNode::get_children() {
    return children;
}
