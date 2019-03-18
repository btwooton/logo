#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "args.h"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in file %s\n", __LINE__, __FILE__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);

void test_create_args() {
    // Given: You have created an Args of count 5
    Args args = create_args(5);

    // When: You get the argument count
    int argc = get_arg_count(args);

    // Then: It should be equal to 5
    ASSERT(argc == 5);

    destroy_args(args);
    SUCCESS();
}

void test_create_and_add() {
    // Given: You have created an Args of count 2
    Args args = create_args(2);
    Arg arg1 = create_number_argument(5.5);
    Arg arg2 = create_number_argument(5.9);

    // When: You add the arguments to the args
    add_arg(args, arg1);
    add_arg(args, arg2);

    // Then: The arguments should have their appropriate values and types
    ASSERT(5.5 == get_number_value(get_arg(args, 0)));
    ASSERT(5.9 == get_number_value(get_arg(args, 1)));
    ASSERT(ARG_NUMBER == get_arg_type(get_arg(args, 0)));
    ASSERT(ARG_NUMBER == get_arg_type(get_arg(args, 1)));
    destroy_args(args);
    SUCCESS();
}

int main(int argc, char *argv[]) {
    
    test_create_args();
    test_create_and_add();
    return 0;
}
