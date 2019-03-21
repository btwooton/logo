CC=g++
CFLAGS=-std=c++17
LFLAGS=-lm -lallegro -lallegro_primitives
TDEPS=token.cpp
TOBJ=token_test.out
TSRC=token_test.cpp
ADEPS=arg.cpp ast_node.cpp
AOBJ=arg_test.out
ASRC=arg_test.cpp
ASDEPS=arg.cpp args.cpp ast_node.cpp
ASOBJ=args_test.out
ASSRC=args_test.cpp
ASTDEPS=ast_node.cpp
ASTOBJ=ast_node_test.out
ASTSRC=ast_node_test.cpp
DTDEPS=procedure.cpp dispatch_table.cpp args.cpp arg.cpp \
       '../runtime/evaluator.cpp' ast_node.cpp '../init/init_dispatch.cpp' \
	   '../runtime/wrappers.cpp' '../turtle/turtle.cpp' \
	   '../init/init_turtle.cpp'
DTOBJ=dispatch_table_test.out
DTSRC=dispatch_table_test.cpp
PDEPS=parser.cpp ast_node.cpp token.cpp tokenizer.cpp \
	  '../init/init_dispatch.cpp' '../runtime/wrappers.cpp' \
	  '../init/init_turtle.cpp' '../turtle/turtle.cpp' \
	  arg.cpp args.cpp dispatch_table.cpp procedure.cpp ../runtime/evaluator.cpp '../rendering/render_turtle.cpp'
PSRC=parser_test.cpp
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

ast_node_test:
	$(CC) $(CFLAGS) $(ASTSRC) $(ASTDEPS) -o $(ASTOBJ)

clean:
	rm -f *.out
