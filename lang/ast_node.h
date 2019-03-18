#ifndef AST_NODE_H_
#define AST_NODE_H_
#include <stdbool.h>

typedef struct AstNode *AstNode;

typedef enum NodeType {
    AST_UNIT,
    AST_NUMBER,
    AST_BOOLEAN,
    AST_IDENTIFIER,
    AST_PARAMETER,
    AST_REPEAT,
    AST_FUNCALL,
    AST_FUNC,
    AST_IF,
    AST_OUTPUT,
    AST_STOP,
    AST_REPCOUNT,
    AST_BRACKETED

} NodeType;

extern AstNode create_number_node(double value);
extern AstNode create_funcall_node(const char *name, int arity);
extern AstNode create_func_node(const char *name, int nparams, int nbody);
extern AstNode create_boolean_node(bool b);
extern AstNode create_strval_node(const char *contents);
extern AstNode create_bracketed_node(int num_children);
extern AstNode copy_ast_node(AstNode original);
extern void destroy_astnode(AstNode node);
extern NodeType get_ast_type(AstNode node);
extern double get_ast_number_value(AstNode node);
extern bool get_ast_bool_value(AstNode node);
extern const char *get_ast_str_value(AstNode node);
extern void add_child(AstNode parent, AstNode child);
extern AstNode get_child(AstNode parent, int index);
extern AstNode set_child(AstNode parent, AstNode child, int index);
extern int get_num_children(AstNode parent);

#endif
