#ifndef RENDER_TURTLE_H_
#define RENDER_TURTLE_H_

typedef struct Turtle *Turtle;

extern void render_turtle(Turtle t);
extern void rendered_forward(Turtle t, float amt);
extern void rendered_backward(Turtle t, float amt);

#endif
