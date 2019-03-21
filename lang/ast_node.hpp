#ifndef AST_NODE_H_
#define AST_NODE_H_
#include <vector>
#include <string>
#include <iostream>

enum class NodeType {
    AST_UNIT,
    AST_NUMBER,
    AST_BOOLEAN,
    AST_STRING,
    AST_IDENTIFIER,
    AST_PARAMETER,
    AST_REPEAT,
    AST_FUNCALL,
    AST_FUNC,
    AST_IF,
    AST_IFELSE,
    AST_OUTPUT,
    AST_STOP,
    AST_REPCOUNT,
    AST_BRACKETED

};

class AstNode {
    public:

        AstNode();
        AstNode(double other);
        AstNode(bool other);
        AstNode(const char *contents);
        AstNode(const char *contents, NodeType type);
        AstNode(NodeType type);
        AstNode(const AstNode& other);
        AstNode(AstNode&& other);
        ~AstNode();

        template <typename T> T get_value() const;
        template <typename T> void set_value(T new_value);
        NodeType get_type() const;
        void add_child(AstNode child);
        AstNode set_child(AstNode child, unsigned int index);
        AstNode get_child(unsigned int index) const;
        unsigned int get_num_children() const;
        void set_children(std::vector<AstNode> new_children);
        std::vector<AstNode>& get_children();

        AstNode& operator=(const AstNode& other);
        AstNode& operator=(AstNode&& other);
        bool operator==(const AstNode& other) const;
        bool operator!=(const AstNode& other) const;
        friend std::ostream& operator<<(std::ostream& out, const AstNode& node);

    private:
        NodeType type;
        std::vector<AstNode> children;
        union {
            double number;
            bool boolean;
            std::string string;
        };       
};

#endif
