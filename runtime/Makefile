CC=g++
CFLAGS=-std=c++11
EDEPS='../lang/parser.cpp' '../lang/tokenizer.cpp' '../lang/token.cpp' \
	  '../lang/ast_node.cpp' 'evaluator.cpp' '../lang/dispatch_table.cpp' \
	  '../lang/procedure.cpp' '../runtime/wrappers.cpp' '../init/init_dispatch.cpp' \
	  '../lang/arg.cpp' '../lang/args.cpp' '../turtle/turtle.cpp' '../init/init_turtle.cpp' '../rendering/render_turtle.cpp'
LFLAGS=-lm -lallegro -lallegro_primitives
ESRC='evaluator_test.cpp'
EOBJ='evaluator_test.out'

evaluator_test:
	$(CC) $(CFLAGS) $(ESRC) $(EDEPS) $(LFLAGS) -o $(EOBJ)

clean:
	rm -f *.out
