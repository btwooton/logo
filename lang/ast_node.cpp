#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include "ast_node.hpp"


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
        default:
            this->string.~basic_string<char>();
            break;
    }
}

NodeType AstNode::get_type() const {
   return type; 
}

template <> double AstNode::get_value() const {
    assert(
        type == NodeType::AST_NUMBER ||
        type == NodeType::AST_REPCOUNT
    );
    return number;
}

template <> bool AstNode::get_value() const {
    assert(type == NodeType::AST_BOOLEAN);
    return boolean;
}

template <> const char *AstNode::get_value() const {
    assert(
        type != NodeType::AST_NUMBER &&
        type != NodeType::AST_BOOLEAN &&
        type != NodeType::AST_REPCOUNT
    );
    return string.c_str();
}

template <> void AstNode::set_value(double new_value) {
    assert(type == NodeType::AST_NUMBER || type == NodeType::AST_REPCOUNT);
    number = new_value;
}

template <> void AstNode::set_value(bool new_value) {
    assert(type == NodeType::AST_BOOLEAN);
    boolean = new_value;
}

template <> void AstNode::set_value(const char *new_value) {
    assert(
        type != NodeType::AST_BOOLEAN && 
        type != NodeType::AST_NUMBER &&
        type != NodeType::AST_REPCOUNT
    );
    string = std::string(new_value);
}

void AstNode::add_child(AstNode child) {
    children.push_back(child);
}

AstNode AstNode::get_child(unsigned int index) const {
    assert(index < children.size());
    return children[index];
}

AstNode AstNode::set_child(AstNode child, unsigned int index) {
    assert(index < children.size());
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

std::ostream& operator<<(std::ostream& out, const AstNode& node) {
    switch (node.type) {
        case NodeType::AST_NUMBER:
            out << node.get_value<double>() << "\n\t";
            break;
        case NodeType::AST_BOOLEAN:
            out << node.get_value<bool>() << "\n\t";
            break;
        default:
            out << node.get_value<const char *>() << "\n\t";
    }
    for (int i = 0; i < node.children.size(); i++) {
        operator<<(out, node.children[i]);
    }
    return out;
}

void AstNode::set_children(std::vector<AstNode> new_children) {
    this->children = new_children;
}

std::vector<AstNode>& AstNode::get_children() {
    return children;
}
