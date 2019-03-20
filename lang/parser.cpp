#include <cassert>
#include <cstring>
#include <cstdio>
#include "procedure.hpp"
#include "dispatch_table.hpp"
#include "../init/init_dispatch.hpp"
#include "parser.hpp"

AstNode parse_expression(Tokenizer& tok) {
    Token t = tok.peek_next();

    if (t.get_type() == TokenType::NUMBER) {
       return parse_number(tok);
    } else if (t.get_type() == TokenType::BOOLEAN) {
        return parse_boolean(tok);
    } else if (t.get_type() == TokenType::REPEAT) {
        return parse_repeat(tok); 
    } else if (t.get_type() == TokenType::OPEN_SQUARE) {
        return parse_bracketed(tok);
    } else if (t.get_type() == TokenType::PARAMETER) {
        return parse_parameter(tok);
    } else if (t.get_type() == TokenType::OTHER) {
        return parse_funcall(tok);
    } else if (t.get_type() == TokenType::TO) {
        return parse_fundef(tok);
    } else if (t.get_type() == TokenType::IF) {
        return parse_if(tok);
    } else if (t.get_type() == TokenType::OUTPUT) {
        return parse_output(tok);
    } else if (t.get_type() == TokenType::STOP) {
        return parse_stop(tok);
    } else if (t.get_type() == TokenType::REPCOUNT) {
        return parse_stop(tok);
    } else {
        return parse_identifier(tok);
    }

}

AstNode parse_number(Tokenizer& tok) {
    Token number_token = tok.get_next();
    AstNode result = AstNode(atof(number_token.get_contents()));
    return result;
}

AstNode parse_boolean(Tokenizer& tok) {
    Token bool_token = tok.get_next();
    const char *contents = bool_token.get_contents();
    if (strcmp(contents, "false") == 0) {
        return AstNode(false);
    } else {
        return AstNode(true);
    }
}

AstNode parse_repeat(Tokenizer& tok) {
    Token repeat_token = tok.get_next();
    const char *contents = repeat_token.get_contents();
    AstNode repeat_node = AstNode(contents);
    AstNode count_node = parse_expression(tok);
    AstNode bracketed_node = parse_bracketed(tok);
    repeat_node.add_child(count_node);
    repeat_node.add_child(bracketed_node);
    return repeat_node;
}

AstNode parse_bracketed(Tokenizer& tok) {
    Token open_square = tok.get_next();
    assert(open_square.get_type() == TokenType::OPEN_SQUARE);
    int num_tokens = 0;
    int num_open = 1;
    while (num_open > 0) {
        Token next = tok.get_next();
        if (next.get_type() == TokenType::CLOSED_SQUARE) {
            num_open--;
            num_tokens++;
        } else if (next.get_type() == TokenType::OPEN_SQUARE) {
            num_open++;
            num_tokens++;
        } else {
            num_tokens++;
        }
    }
    tok.unget();
    Token closed_square = tok.get_next();
    assert(closed_square.get_type() == TokenType::CLOSED_SQUARE);

    for (int i = 0; i < num_tokens; i++) {
        tok.unget();
    }

    int num_children = 0;
    while (tok.peek_next() != closed_square) {
        parse_expression(tok);
        num_children++;
    }

    for (int i = 0; i < num_tokens; i++) {
        tok.unget();
    }

    AstNode bracketed = AstNode("bracketed", NodeType::AST_BRACKETED);
    
    if (tok.peek_next().get_type() == TokenType::OPEN_SQUARE) {
        tok.get_next();
    }
    for (int i = 0; i < num_children; i++) {
        bracketed.add_child(parse_expression(tok));
    }
    tok.get_next();
    return bracketed;
}

AstNode parse_identifier(Tokenizer& tok) {
    Token identifier = tok.get_next();
    AstNode result = AstNode(identifier.get_contents());
    return result;
}

AstNode parse_funcall(Tokenizer& tok) {
    Token fname = tok.get_next();
    assert(__dispatch_table__.has_binding(fname.get_contents()));

    Procedure p = __dispatch_table__.get_bound_procedure(fname.get_contents());
    unsigned int arity = p.get_arity();

    AstNode func_node = AstNode(fname.get_contents(), NodeType::AST_FUNCALL);

    for (int i = 0; i < arity; i++) {
        func_node.add_child(parse_expression(tok));
    }
    return func_node;
}

AstNode parse_fundef(Tokenizer& tok) {
    Token to = tok.get_next();
    assert(to.get_type() == TokenType::TO);

    Token fname = tok.get_next();

    AstNode func_node = AstNode(fname.get_contents(), NodeType::AST_FUNC);

    while (tok.peek_next().get_type() != TokenType::END) {
        func_node.add_child(parse_expression(tok)); 
    }

    if (tok.has_next()) {
        tok.get_next();
    }
    return func_node;
}

AstNode parse_parameter(Tokenizer& tok) {
    Token param_token = tok.get_next();
    assert(param_token.get_type() == TokenType::PARAMETER);
    return AstNode(param_token.get_contents());
}

AstNode parse_if(Tokenizer& tok) {
    Token if_token = tok.get_next();
    AstNode if_node = AstNode(if_token.get_contents());

    AstNode conditional = parse_expression(tok);
    AstNode bracketed = parse_expression(tok);
    
    if_node.add_child(conditional);
    if_node.add_child(bracketed);
    
    return if_node;
}

AstNode parse_output(Tokenizer& tok) {
    Token output_token = tok.get_next();
    assert(output_token.get_type() == TokenType::OUTPUT);
    
    AstNode output_node = AstNode(output_token.get_contents());
    AstNode out_val = parse_expression(tok);

    output_node.add_child(out_val);
    
    return output_node;
}

AstNode parse_stop(Tokenizer& tok) {
    Token stop_token = tok.get_next();
    assert(stop_token.get_type() == TokenType::STOP);

    AstNode stop_node = AstNode(stop_token.get_contents());
    return stop_node;
}

AstNode parse_repcount(Tokenizer& tok) {
    Token repcount_token = tok.get_next();
    assert(repcount_token.get_type() == TokenType::REPCOUNT);

    AstNode repcount_node = AstNode(repcount_token.get_contents());
    return repcount_node;
}
