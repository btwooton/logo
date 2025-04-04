#ifndef TOKENIZER_H_
#define TOKENIZER_H_
#include <vector>
#include <string>

class Token;
class Tokenizer {

    public:
        Tokenizer();
        void tokenize(std::string input);
        void unget();
        Token get_next();
        Token peek_next();
        bool has_next() const;
        unsigned int get_num_tokens() const { return num_tokens; }
        friend std::ostream& operator<<(std::ostream& out, const Tokenizer& tok);

    private:
        std::vector<Token> tokens;
        unsigned int current_token;
        unsigned int num_tokens;

};

#endif
