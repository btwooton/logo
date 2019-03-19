#ifndef ARG_H_
#define ARG_H_
#include "ast_node.hpp"
#include <string>

enum class ArgType {
    ARG_NUMBER,
    ARG_STRING,
    ARG_BOOLEAN,
    ARG_UNIT,
};

class Arg {

    public:

        Arg(ArgType type);
        Arg(double number);
        Arg(const char *string);
        Arg(bool boolean);
        Arg(const AstNode& node);
        Arg(const Arg& other);
        ~Arg();

        template <typename T> T get_value() const;
        ArgType get_type() const;

    private:
        ArgType type;
        union {
            double number;
            std::string string;
            bool boolean;
        };
};

#endif
