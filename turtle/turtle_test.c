#include <assert.h>
#include <stdio.h>
#include "turtle.h"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in file %s\n", __LINE__, __FILE__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);

void test_turtle_create() {

    // Given: You have created a turtle with the following attributes
    Turtle t = create_turtle(50, 50, 180, true);

    // Then: The created turtle object should have the specified attributes

    ASSERT(t);
    ASSERT(getx(t) == 50);
    ASSERT(gety(t) == 50);
    ASSERT(get_heading(t) == 180);
    ASSERT(isdown(t));

    SUCCESS();

}

void test_turtle_right() {
    
    // Given: You have created a turtle with the following attributes
    Turtle t = create_turtle(50, 50, 22, true);

    // When: You move the turtle right by 45 degrees
    right(t, 45);
    
    // Then: The turtle's heading should be 337 degrees
    ASSERT(get_heading(t) == 337);

    SUCCESS();  

}

void test_turtle_left() {
    
    // Given: You have created a turtle with the following attributes
    Turtle t = create_turtle(50, 50, 22, true);

    // When: You move the turtle left by 45 degrees
    left(t, 45);

    // Then: The turtle's heading should be 67 degrees
    ASSERT(get_heading(t) == 67);

    SUCCESS();

}
void test_turtle_forward() {
    
    // Given: You have created a turtle with the following attributes
    Turtle t = create_turtle(50, 50, 180, true);

    // When: You move the turtle forward by 50
    forward(t, 50);

    // Then: The turtle's x position should be 0
    ASSERT(getx(t) == 0);
    
    // Then: The turtle's y position should be 50
    ASSERT(gety(t) == 50);

    SUCCESS();

}

void test_turtle_backward() {

    // Given: You have created a turtle with the following attributes
    Turtle t = create_turtle(50, 50, 90, true);

    // When: You move the turtle backward by 25
    backward(t, 25);
    
    // Then: The turtle's x position should be 50
    ASSERT(getx(t) == 50);

    // Then: The turtle's y position should be 75
    ASSERT(gety(t) == 25);

    SUCCESS();

}

int main(int argc, char *argv[]) {
    test_turtle_right();
    test_turtle_left();
    test_turtle_create();
    test_turtle_forward();
    test_turtle_backward();


    return 0;
}
