CC=g++
CFLAGS=-std=c++17
LFLAGS=-lm
TDEPS=token.cpp
TOBJ=token_test.out
TSRC=token_test.cpp
ADEPS=arg.c 
AOBJ=arg_test.out
ASRC=arg_test.c
ASDEPS=arg.c args.c ast_node.c
ASOBJ=args_test.out
ASSRC=args_test.c
DTDEPS=procedure.c dispatch_table.c args.c arg.c
DTOBJ=dispatch_table_test.out
DTSRC=dispatch_table_test.c
PDEPS=parser.c ast_node.c token.c tokenizer.c \
	  '../init/init_dispatch.c' '../runtime/wrappers.c' \
	  '../init/init_turtle.c' '../turtle/turtle.c' \
	  arg.c args.c dispatch_table.c procedure.c
PSRC=parser_test.c
POBJ=parser_test.out
TZDEPS=tokenizer.cpp token.cpp
TZSRC=tokenizer_test.cpp
TZOBJ=tokenizer_test.out

arg_test:
	$(CC) $(CFLAGS) $(ASRC) $(ADEPS) -o $(AOBJ)

token_test:
	$(CC) $(CFLAGS) $(TSRC) $(TDEPS) -o $(TOBJ)

args_test:
	$(CC) $(CFLAGS) $(ASSRC) $(ASDEPS) -o $(ASOBJ)

dispatch_table_test:
	$(CC) $(CFLAGS) $(DTSRC) $(DTDEPS) -o $(DTOBJ)

tokenizer_test:
	$(CC) $(CFLAGS) $(TZSRC) $(TZDEPS) -o $(TZOBJ)

parser_test:
	$(CC) $(CFLAGS) $(PSRC) $(PDEPS) $(LFLAGS) -o $(POBJ)

clean:
	rm -f *.out
