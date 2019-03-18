#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "procedure.h"
#include "dispatch_table.h"
#include "../init/init_dispatch.h"
#include "parser.h"

AstNode parse_expression(Tokenizer tok) {
    Token t = peek_next(tok);

    if (get_type(t) == NUMBER) {
       return parse_number(tok);
    } else if (get_type(t) == BOOLEAN) {
        return parse_boolean(tok);
    } else if (get_type(t) == REPEAT) {
        return parse_repeat(tok); 
    } else if (get_type(t) == OPEN_SQUARE) {
        return parse_bracketed(tok);
    } else if (get_type(t) == PARAMETER) {
        return parse_parameter(tok);
    } else if (get_type(t) == OTHER) {
        return parse_funcall(tok);
    } else if (get_type(t) == TO) {
        return parse_fundef(tok);
    } else if (get_type(t) == IF) {
        return parse_if(tok);
    } else if (get_type(t) == OUTPUT) {
        return parse_output(tok);
    } else if (get_type(t) == STOP) {
        return parse_stop(tok);
    } else if (get_type(t) == REPCOUNT) {
        return parse_stop(tok);
    } else {
        return parse_identifier(tok);
    }

}

AstNode parse_number(Tokenizer tok) {
    Token number_token = get_next(tok);
    AstNode result = create_number_node(atof(get_contents(number_token)));
    return result;
}

AstNode parse_boolean(Tokenizer tok) {
    Token bool_token = get_next(tok);
    const char *contents = get_contents(bool_token);
    if (strcmp(contents, "false") == 0) {
        return create_boolean_node(false);
    } else {
        return create_boolean_node(true);
    }
}

AstNode parse_repeat(Tokenizer tok) {
    Token repeat_token = get_next(tok);
    const char *contents = get_contents(repeat_token);
    AstNode repeat_node = create_strval_node(contents);
    AstNode count_node = parse_expression(tok);
    AstNode bracketed_node = parse_bracketed(tok);
    add_child(repeat_node, count_node);
    add_child(repeat_node, bracketed_node);
    return repeat_node;
}

AstNode parse_bracketed(Tokenizer tok) {
    Token open_square = get_next(tok);
    assert(get_type(open_square) == OPEN_SQUARE);
    int num_tokens = 0;
    int num_open = 1;
    while (num_open > 0) {
        Token next = get_next(tok);
        if (get_type(next) == CLOSED_SQUARE) {
            num_open--;
            num_tokens++;
        } else if (get_type(next) == OPEN_SQUARE) {
            num_open++;
            num_tokens++;
        } else {
            num_tokens++;
        }
    }
    unget(tok);
    Token closed_square = get_next(tok);

    for (int i = 0; i < num_tokens; i++) {
        unget(tok);
    }

    int num_children = 0;
    while (peek_next(tok) != closed_square) {
        destroy_astnode(parse_expression(tok));
        num_children++;
    }

    for (int i = 0; i < num_tokens; i++) {
        unget(tok);
    }

    AstNode bracketed = create_bracketed_node(num_children);
    if (get_type(peek_next(tok)) == OPEN_SQUARE) {
        get_next(tok);
    }
    for (int i = 0; i < num_children; i++) {
        add_child(bracketed, parse_expression(tok));
    }
    get_next(tok);
    return bracketed;
}

AstNode parse_identifier(Tokenizer tok) {
    Token identifier = get_next(tok);
    AstNode result = create_strval_node(get_contents(identifier));
    return result;
}

AstNode parse_funcall(Tokenizer tok) {
    Token fname = get_next(tok);
    assert(__dispatch_table__ != NULL);
    assert(has_binding(__dispatch_table__, get_contents(fname)));

    Procedure p = get_bound_procedure(__dispatch_table__, get_contents(fname));
    int arity = get_arity(p);

    AstNode func_node = create_funcall_node(get_contents(fname), arity);

    for (int i = 0; i < arity; i++) {
        add_child(func_node, parse_expression(tok));
    }
    return func_node;
}

AstNode parse_fundef(Tokenizer tok) {
    Token to = get_next(tok);
    assert(get_type(to) == TO);

    Token fname = get_next(tok);

    int nparams = 0;
    int nbody = 0;

    while (get_type(peek_next(tok)) == PARAMETER) {
        nparams++;
        get_next(tok);
    }

    while (get_type(peek_next(tok)) != END) {
        destroy_astnode(parse_expression(tok));
        nbody++;
    
    }

    while (get_type(peek_next(tok)) != TO) {
        unget(tok);
    }
    get_next(tok);
    get_next(tok);

    AstNode func_node = create_func_node(get_contents(fname), nparams, nbody);

    for (int i = 0; i < nparams; i++) {
        Token ptoken = get_next(tok);
        AstNode param_node = create_strval_node(get_contents(ptoken));
        add_child(func_node, param_node);
    }
    while (get_type(peek_next(tok)) != END) {
        add_child(func_node, parse_expression(tok)); 
    }
    get_next(tok);
    return func_node;
}

AstNode parse_parameter(Tokenizer tok) {
    Token param_token = get_next(tok);
    assert(get_type(param_token) == PARAMETER);
    return create_strval_node(get_contents(param_token));
}

AstNode parse_if(Tokenizer tok) {
    Token if_token = get_next(tok);
    AstNode if_node = create_strval_node(get_contents(if_token));

    AstNode conditional = parse_expression(tok);
    AstNode bracketed = parse_expression(tok);
    
    add_child(if_node, conditional);
    add_child(if_node, bracketed);
    
    return if_node;
}

AstNode parse_output(Tokenizer tok) {
    Token output_token = get_next(tok);
    assert(get_type(output_token) == OUTPUT);
    
    AstNode output_node = create_strval_node(get_contents(output_token));
    AstNode out_val = parse_expression(tok);

    add_child(output_node, out_val);
    
    return output_node;
}

AstNode parse_stop(Tokenizer tok) {
    Token stop_token = get_next(tok);
    assert(get_type(stop_token) == STOP);

    AstNode stop_node = create_strval_node(get_contents(stop_token));
    return stop_node;
}

AstNode parse_repcount(Tokenizer tok) {
    Token repcount_token = get_next(tok);
    assert(get_type(repcount_token) == REPCOUNT);

    AstNode repcount_node = create_strval_node(get_contents(repcount_token));
    return repcount_node;
}
