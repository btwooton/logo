#include <assert.h>
#include <stdio.h>
#include "init_turtle.h"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in file %s\n", __LINE__, __FILE__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);

void test_init_turtle() {
    // Given: You have declared the following inital values
    float x = 500;
    float y = 500;
    float a = 180;
    bool pd = true;

    // When: You call init_turtle, passing in these values
    init_turtle(x, y, a, pd);

    // Then: The __turtle__ reference should hold the appropriate values
    ASSERT(getx(__turtle__) == 500);
    ASSERT(gety(__turtle__) == 500);
    ASSERT(get_heading(__turtle__) == 180);
    ASSERT(isdown(__turtle__));

    SUCCESS();
}

int main(int argc, char *argv[]) {
    test_init_turtle();
    return 0;
}
