#include <cassert>
#include <cstdio>
#include <cmath>
#include "turtle.hpp"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in file %s\n", __LINE__, __FILE__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);

void test_turtle_create() {

    // Given: You have created a turtle with the following attributes
    Turtle t = Turtle(50.0, 50.0, 180, true);

    // Then: The created turtle object should have the specified attributes

    ASSERT(t.get_x() == 50.0);
    ASSERT(t.get_y() == 50.0);
    ASSERT(t.get_heading() == 180);
    ASSERT(t.isdown());

    SUCCESS();

}

void test_turtle_right() {
    
    // Given: You have created a turtle with the following attributes
    Turtle t = Turtle(50.0, 50.0, 22, true);

    // When: You move the turtle right by 45 degrees
    t.right(45);
    
    // Then: The turtle's heading should be 337 degrees
    ASSERT(t.get_heading() == 337);

    SUCCESS();  

}

void test_turtle_left() {
    
    // Given: You have created a turtle with the following attributes
    Turtle t = Turtle(50, 50, 22, true);

    // When: You move the turtle left by 45 degrees
    t.left(45);

    // Then: The turtle's heading should be 67 degrees
    ASSERT(t.get_heading() == 67);

    SUCCESS();

}
void test_turtle_forward() {
    
    // Given: You have created a turtle with the following attributes
    Turtle t = Turtle(50, 50, 180, true);

    // When: You move the turtle forward by 50
    t.forward(50);


    // Then: The turtle's x position should be 0
    ASSERT(floor(t.get_x()) == 0);
    
    // Then: The turtle's y position should be 50
    ASSERT(floor(t.get_y()) == 50.0);

    SUCCESS();

}

void test_turtle_backward() {

    // Given: You have created a turtle with the following attributes
    Turtle t = Turtle(50, 50, 90, true);

    // When: You move the turtle backward by 25
    t.backward(25);

    // Then: The turtle's x position should be 50
    ASSERT(ceil(t.get_x()) == 50.0);

    // Then: The turtle's y position should be 75
    ASSERT(floor(t.get_y()) == 25.0);

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
