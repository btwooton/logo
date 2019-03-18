#include <stdlib.h>
#include <math.h>
#include "turtle.h"

struct Turtle {

    float x, y, a;
    bool pd;

};

Turtle create_turtle(float x, float y, float a, bool pd) {
    Turtle result = malloc(sizeof(struct Turtle));
    result->x = x;
    result->y = y;
    result->a = a;
    result->pd = pd;
    return result;
}

void destroy_turtle(Turtle t) {
    free(t);
}

float getx(Turtle t) {
    return t->x;
}

float gety(Turtle t) {
    return t->y;
}

float get_heading(Turtle t) {
    return t->a;
}

void setx(Turtle t, float x) {
    t->x = x;
}

void sety(Turtle t, float y) {
    t->y = y;
}

void set_heading(Turtle t, float a) {
    t->a = a;
}

void forward(Turtle t, float amt) {
    float new_x = t->x + cos(t->a*PI/180) * amt;
    float new_y = t->y + sin(t->a*PI/180) * amt;
    t->x = new_x;
    t->y = new_y;
}

void backward(Turtle t, float amt) {
    float new_x = t->x - cos(t->a*PI/180) * amt;
    float new_y = t->y - sin(t->a*PI/180) * amt;
    t->x = new_x;
    t->y = new_y;
}

void right(Turtle t, float amt) {
    t->a = (int)(t->a - amt + 360) % 360;
}

void left(Turtle t, float amt) {
    t->a = (int)(t->a + amt) % 360;
}

void penup(Turtle t) {
    t->pd = false;
}

void pendown(Turtle t) {
    t->pd = true;
}

bool isdown(Turtle t) {
    return t->pd;
}
