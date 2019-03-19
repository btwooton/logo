#include <cassert>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include "ast_node.hpp"


AstNode::AstNode(double other) {
    type = NodeType::AST_NUMBER;
    new (&number) double(other);
}

AstNode::AstNode(bool other) {
    type = NodeType::AST_BOOLEAN;
    new (&boolean) bool(other);
}

AstNode::AstNode(const char *contents) {
    new (&string) std::string(contents);

    if (contents[0] == ':') {
        type = NodeType::AST_PARAMETER;
    } else if (contents[0] == '"' || contents[0] == '\'') {
        type = NodeType::AST_STRING;
    } else if (strcmp(contents, "repeat") == 0) {
        type = NodeType::AST_REPEAT;
    } else if (strcmp(contents, "if") == 0) {
        type = NodeType::AST_IF;
    } else if (strcmp(contents, "output") == 0) {
        type = NodeType::AST_OUTPUT;
    } else if (strcmp(contents, "stop") == 0) {
        type = NodeType::AST_STOP;
    } else if (strcmp(contents, "repcount") == 0) {
        type = NodeType::AST_REPCOUNT;
    } else if (strcmp(contents, "()") == 0) {
        type = NodeType::AST_UNIT;
    } else {
        type = NodeType::AST_IDENTIFIER;
    }

}

AstNode::AstNode(const char *contents, NodeType type) {
    type = type;
    new (&string) std::string(contents);
}

AstNode::AstNode(const AstNode& other) {
    type = other.type;

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
    assert(type == NodeType::AST_NUMBER);
    return number;
}

template <> bool AstNode::get_value() const {
    assert(type == NodeType::AST_BOOLEAN);
    return boolean;
}

template <> const char *AstNode::get_value() const {
    assert(type != NodeType::AST_NUMBER && type != NodeType::AST_BOOLEAN);
    return string.c_str();
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
