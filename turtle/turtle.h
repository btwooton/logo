#ifndef TURTLE_H_
#define TURTLE_H_

#include <stdbool.h>

#ifndef PI
#define PI 3.14159265
#endif

typedef struct Turtle *Turtle;

extern Turtle create_turtle(float x, float y, float a, bool pd);
extern void destroy_turtle(Turtle t);
extern float getx(Turtle t);
extern float gety(Turtle t);
extern float get_heading(Turtle t);
extern void setx(Turtle t, float x);
extern void sety(Turtle t, float y);
extern void set_heading(Turtle t, float a);
extern void forward(Turtle t, float amt);
extern void backward(Turtle t, float amt);
extern void right(Turtle t, float amt);
extern void left(Turtle t, float amt);
extern void penup(Turtle t);
extern void pendown(Turtle t);
extern bool isdown(Turtle t);

#endif
