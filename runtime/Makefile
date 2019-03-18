CC=gcc
CFLAGS=-std=c11
EDEPS='../lang/parser.c' '../lang/tokenizer.c' '../lang/token.c' \
	  '../lang/ast_node.c' 'evaluator.c' '../lang/dispatch_table.c' \
	  '../lang/procedure.c' '../runtime/wrappers.c' '../init/init_dispatch.c' \
	  '../lang/arg.c' '../lang/args.c' '../turtle/turtle.c' '../init/init_turtle.c'
LFLAGS=-lm
ESRC='evaluator_test.c'
EOBJ='evaluator_test.out'

evaluator_test:
	$(CC) $(CFLAGS) $(ESRC) $(EDEPS) $(LFLAGS) -o $(EOBJ)

clean:
	rm -f *.out
