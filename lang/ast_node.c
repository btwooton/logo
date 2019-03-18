#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "ast_node.h"

struct AstNode {
   NodeType type;

   union Data {
       double number;
       bool boolean;
       const char *string;
   } data;

   AstNode *children;
   int degree;
   int num_children;
};

AstNode copy_ast_node(AstNode original) {
    NodeType type = get_ast_type(original);
    AstNode result = malloc(sizeof(struct AstNode));
    result->type = type;
    result->children = malloc(sizeof(AstNode) * original->degree);
    result->degree = original->degree;
    result->num_children = original->num_children;
    
    for (int i = 0; i < original->num_children; i++) {
        result->children[i] = copy_ast_node(original->children[i]);
    }

    if (type == AST_NUMBER) {
        result->data.number = original->data.number;
    } else if (type == AST_BOOLEAN) {
        result->data.boolean = original->data.boolean;
    } else {
        result->data.string = original->data.string;
    }
    return result;
}

AstNode create_number_node(double value) {
    AstNode result = malloc(sizeof(struct AstNode));
    result->type = AST_NUMBER;
    result->data.number = value;
    result->children = NULL;
    result->degree = 0;
    result->num_children = 0;
    return result;
}

AstNode create_funcall_node(const char *name, int arity) {
    AstNode result = malloc(sizeof(struct AstNode));
    result->type = AST_FUNCALL;
    result->data.string = name;
    result->children = malloc(sizeof(AstNode) * arity);
    result->degree = arity;
    result->num_children = 0;
    return result;
}

AstNode create_func_node(const char *name, int nparams, int nbody) {
    AstNode result = malloc(sizeof(struct AstNode));
    result->type = AST_FUNC;
    result->data.string = name;
    result->children = malloc(sizeof(AstNode) * (nparams + nbody));
    result->degree = nparams + nbody;
    result->num_children = 0;
    return result;
}

AstNode create_boolean_node(bool b) {
    AstNode result = malloc(sizeof(struct AstNode));
    result->type = AST_BOOLEAN;
    result->data.boolean = b;
    result->children = NULL;
    result->degree = 0;
    result->num_children = 0;
    return result;
}

AstNode create_strval_node(const char *contents) {
    AstNode result = malloc(sizeof(struct AstNode));
    result->data.string = contents;
    result->degree = 0;

    if (contents[0] == ':') {
        result->type = AST_PARAMETER;
        result->children = NULL;
        result->degree = 0;
        result->num_children = 0;
    } else if (strcmp(contents, "repeat") == 0) {
        result->type = AST_REPEAT;
        result->children = malloc(sizeof(AstNode) * 2);
        result->degree = 2;
        result->num_children = 0;
    } else if (strcmp(contents, "if") == 0) {
        result->type = AST_IF;
        result->children = malloc(sizeof(AstNode) * 2);
        result->degree = 2;
        result->num_children = 0;
    } else if (strcmp(contents, "output") == 0) {
        result->type = AST_OUTPUT;
        result->children = malloc(sizeof(AstNode));
        result->degree = 1;
        result->num_children = 0;
    } else if (strcmp(contents, "stop") == 0) {
        result->type = AST_STOP;
        result->children = NULL;
        result->degree = 0;
        result->num_children = 0;
    } else if (strcmp(contents, "repcount") == 0) {
        result->type = AST_REPCOUNT;
        result->children = NULL;
        result->degree = 0;
        result->num_children = 0;
    } else if (strcmp(contents, "()") == 0) {
        result->type = AST_UNIT;
        result->children = NULL;
        result->degree = 0;
        result->num_children = 0;
    } else {
        result->type = AST_IDENTIFIER;
        result->children = NULL;
        result->degree = 0;
        result->num_children = 0;
    }

    for (int i = 0; i < result->degree; i++) {
        result->children[i] = NULL;
    }
    return result;

}

AstNode create_bracketed_node(int num_children) {
    AstNode result = malloc(sizeof(struct AstNode));
    result->data.string = "bracketed";
    result->type = AST_BRACKETED;
    result->children = malloc(sizeof(AstNode) * num_children);
    result->degree = num_children;
    result->num_children = 0;
    return result;
}

void destroy_astnode(AstNode node) {
    if (node == NULL) {
        return;
    }
    if (node->children != NULL) {
        for (int i = 0; i < node->degree; i++) {
            if (node->children[i] != NULL) {
                destroy_astnode(node->children[i]);
            }
        }
        free(node->children);
    }
    free(node);
}

NodeType get_ast_type(AstNode node) {
   return node->type; 
}

double get_ast_number_value(AstNode node) {
    assert(node->type == AST_NUMBER);
    return node->data.number;
}

bool get_ast_bool_value(AstNode node) {
    assert(node->type == AST_BOOLEAN);
    return node->data.boolean;
}

const char *get_ast_str_value(AstNode node) {
    assert(node->type != AST_NUMBER && node->type != AST_BOOLEAN);
    return node->data.string;
}

void add_child(AstNode parent, AstNode child) {
    assert(parent->num_children < parent->degree);
    parent->children[parent->num_children++] = child;
}

AstNode get_child(AstNode parent, int index) {
    assert(index < parent->num_children);
    return parent->children[index];
}

AstNode set_child(AstNode parent, AstNode child, int index) {
    assert(index < parent->num_children && index >= 0);
    AstNode result = parent->children[index];
    parent->children[index] = child;
    return result;
}

int get_num_children(AstNode parent) {
    return parent->num_children;
}
