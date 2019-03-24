#ifndef RENDER_TURTLE_H_
#define RENDER_TURTLE_H_
#include "../turtle/turtle.hpp"

extern void render_turtle(Turtle& t);
extern void rendered_forward(Turtle& t, double amt);
extern void rendered_backward(Turtle& t, double amt);
extern void rendered_clean();

#endif
