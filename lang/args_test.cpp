#include <cassert>
#include <cstdio>
#include "args.hpp"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in file %s\n", __LINE__, __FILE__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);

void test_create_and_add() {
    // Given: You have created an Args of count 2
    Args args = Args();
    Arg arg1 = Arg(5.5);
    Arg arg2 = Arg(5.9);

    // When: You add the arguments to the args
    args.add_arg(arg1);
    args.add_arg(arg2);

    // Then: The arguments should have their appropriate values and types
    ASSERT(5.5 == args.get_arg(0).get_value<double>());
    ASSERT(5.9 == args.get_arg(1).get_value<double>());
    ASSERT(ArgType::ARG_NUMBER == args.get_arg(0).get_type());
    ASSERT(ArgType::ARG_NUMBER == args.get_arg(1).get_type());
    SUCCESS();
}

int main(int argc, char *argv[]) {
    
    test_create_and_add();
    return 0;
}
