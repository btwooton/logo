#ifndef TOKEN_H_
#define TOKEN_H_

typedef struct Token *Token;

typedef enum TokenType {
    TO,
    END,
    OPEN_SQUARE,
    CLOSED_SQUARE,
    FUNCTION_NAME,
    PARAMETER,
    NUMBER,
    BOOLEAN,
    STOP,
    REPEAT,
    REPCOUNT,
    IF,
    OUTPUT,
    OTHER

} TokenType;

extern Token create_token(const char *contents);
extern void destroy_token(Token t);
extern TokenType get_type(Token t);
extern const char *get_contents(Token t);

#endif
