#include <cassert>
#include <cstdlib>
#include <cstring>
#include <string>
#include "arg.hpp"


Arg::Arg(ArgType type) {
    this->type = type;
    switch (type) {
        case ArgType::ARG_BOOLEAN:
            new (&boolean) bool(false);
            break;
        case ArgType::ARG_NUMBER:
            new (&number) double(0.0);
            break;
        case ArgType::ARG_STRING:
            new (&string) std::string("");
            break;
        case ArgType::ARG_UNIT:
            new (&string) std::string("()");
            break;
    }
}

Arg::Arg(double number) {
    this->type = ArgType::ARG_NUMBER;
    new (&this->number) double(number);
}

Arg::Arg(const char *string) {
    this->type = ArgType::ARG_STRING;
    new (&this->string) std::string(string);
}

Arg::Arg(bool boolean) {
    this->type = ArgType::ARG_BOOLEAN;
    new (&this->boolean) bool(boolean);
}

Arg::Arg(const AstNode& node) {
    switch (node.get_type()) {
        case NodeType::AST_BOOLEAN:
            this->type = ArgType::ARG_BOOLEAN;
            new (&this->boolean) bool(node.get_value<bool>());
            break;
        case NodeType::AST_NUMBER:
            this->type = ArgType::ARG_NUMBER;
            new (&this->number) double(node.get_value<double>());
            break;
        case NodeType::AST_STRING:
            this->type = ArgType::ARG_STRING;
            new (&this->string) std::string(node.get_value<const char *>());
        default:
            this->type = ArgType::ARG_UNIT;
            new (&this->string) std::string("");
            break;
    }
}

Arg::Arg(const Arg& other) {
    this->type = other.type;

    switch (this->type) {
        case ArgType::ARG_NUMBER:
            new (&number) double(other.number);
            break;
        case ArgType::ARG_BOOLEAN:
            new (&boolean) bool(other.boolean);
            break;
        case ArgType::ARG_STRING:
            new (&string) std::string(other.string);
            break;
        default:
            new (&string) std::string(other.string);
            break;
    }
}

Arg::~Arg() {
    switch (this->type) {
        case ArgType::ARG_NUMBER:
            break;
        case ArgType::ARG_BOOLEAN:
            break;
        case ArgType::ARG_STRING:
            string.~basic_string<char>();
            break;
        default:
            string.~basic_string<char>();
            break;   
    }
}

template <> double Arg::get_value() const {
    assert(this->type == ArgType::ARG_NUMBER);
    return number;
}

template <> bool Arg::get_value() const {
    assert(this->type == ArgType::ARG_BOOLEAN);
    return boolean;
}

template <> const char *Arg::get_value() const {
    assert(type == ArgType::ARG_STRING || type == ArgType::ARG_UNIT);
    return string.c_str();
}

ArgType Arg::get_type() const {
    return type;
}
