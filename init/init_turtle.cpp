#include "init_turtle.hpp"

Turtle __turtle__;

void init_turtle(double x, double y, int a, bool pd) {
    __turtle__ = Turtle(x, y, a, pd);
}
