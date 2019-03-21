#ifndef TOKENIZER_H_
#define TOKENIZER_H_
#include <vector>

class Token;
class Tokenizer {

    public:
        Tokenizer();
        void tokenize(const char *string);
        void unget();
        Token get_next();
        Token peek_next();
        bool has_next() const;
        friend std::ostream& operator<<(std::ostream& out, const Tokenizer& tok);

    private:
        std::vector<Token> tokens;
        unsigned int current_token;
        unsigned int num_tokens;

};

#endif
