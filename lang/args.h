#ifndef ARGS_H_
#define ARGS_H_
#include "arg.h"

typedef struct Args *Args;

extern Args create_args(int argc);
extern void add_arg(Args args, Arg arg);
extern int get_arg_count(Args args);
extern Arg get_arg(Args args, int index);
extern void destroy_args(Args args);

#endif
