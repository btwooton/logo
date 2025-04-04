CC=g++
SRC=main.cpp
DEPS='../turtle/turtle.cpp' '../rendering/render_turtle.cpp' '../init/init_allegro.cpp' \
	 '../init/init_turtle.cpp' '../lang/args.cpp' '../lang/arg.cpp' '../runtime/wrappers.cpp' \
	 '../lang/procedure.cpp' '../lang/dispatch_table.cpp' '../init/init_dispatch.cpp' \
	 '../runtime/evaluator.cpp' '../lang/ast_node.cpp' '../lang/parser.cpp' \
	 '../lang/tokenizer.cpp' '../lang/token.cpp'
OBJS=main.out
LFLAGS= -L/opt/homebrew/lib -lm -lallegro -lallegro_primitives -lallegro_main
CFLAGS=-std=c++17 -I/opt/homebrew/include

main:
		$(CC) $(CFLAGS) $(SRC) $(DEPS) $(LFLAGS) -o $(OBJS)

clean:
		rm *.out
