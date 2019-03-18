#include <stdlib.h>
#include "init_turtle.h"

Turtle __turtle__ = NULL;

void init_turtle(float x, float y, float a, bool pd) {
    __turtle__ = create_turtle(x, y, a, pd);
}
