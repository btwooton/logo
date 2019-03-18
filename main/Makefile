CC=gcc
SRC=main.c
DEPS='../turtle/turtle.c' '../rendering/render_turtle.c' '../init/init_allegro.c' \
	 '../init/init_turtle.c' '../lang/args.c' '../lang/arg.c' '../runtime/wrappers.c' \
	 '../lang/procedure.c' '../lang/dispatch_table.c' '../init/init_dispatch.c'
OBJS=main.out
LFLAGS=-lm -lallegro -lallegro_primitives
CFLAGS=-std=c11

main:
		$(CC) $(CFLAGS) $(SRC) $(DEPS) $(LFLAGS) -o $(OBJS)

clean:
		rm *.out
