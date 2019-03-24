CC=g++
SRC=main.cpp
DEPS='../turtle/turtle.cpp' '../rendering/render_turtle.cpp' '../init/init_allegro.cpp' \
	 '../init/init_turtle.cpp' '../lang/args.cpp' '../lang/arg.cpp' '../runtime/wrappers.cpp' \
	 '../lang/procedure.cpp' '../lang/dispatch_table.cpp' '../init/init_dispatch.cpp' \
	 '../runtime/evaluator.cpp' '../lang/ast_node.cpp' '../lang/parser.cpp' \
	 '../lang/tokenizer.cpp' '../lang/token.cpp'
OBJS=main.out
LFLAGS=-lm -lallegro -lallegro_primitives
CFLAGS=-std=c++17

main:
		$(CC) $(CFLAGS) $(SRC) $(DEPS) $(LFLAGS) -o $(OBJS)

clean:
		rm *.out
