#ifndef TOKENIZER_H_
#define TOKENIZER_H_

typedef struct Tokenizer *Tokenizer;

extern Tokenizer create_tokenizer();
extern void destroy_tokenizer(Tokenizer t);

extern void tokenize(Tokenizer t, const char *string);
extern void unget(Tokenizer t);
extern Token get_next(Tokenizer t);
extern Token peek_next(Tokenizer t);
extern bool has_next(Tokenizer t);

#endif
