#ifndef TOKEN_H_
#define TOKEN_H_
#include <string>

enum class TokenType
{
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

};

class Token
{
    public:

        Token();
        Token(std::string contents);
        TokenType get_type() const;
        const char *get_contents() const;
    
    private:

        std::string contents;
        TokenType type;
};

#endif
