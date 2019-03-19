#include <cassert>
#include <cstdio>
#include <cstring>
#include "arg.hpp"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in file %s\n", __LINE__, __FILE__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);


void test_create_empty_args() {
    // Given: You have created dummy arguments
    Arg num_arg = Arg(ArgType::ARG_NUMBER);
    Arg str_arg = Arg(ArgType::ARG_STRING);
    Arg bool_arg = Arg(ArgType::ARG_BOOLEAN);

    // Then: They should have the appropriate default values
    ASSERT(num_arg.get_value<double>() == 0.0);
    ASSERT(strcmp(str_arg.get_value<const char *>(), "") == 0);
    ASSERT(bool_arg.get_value<bool>() == false);

    SUCCESS();

}

void test_create_number_args() {
    // Given: You have created numeric arguments
    Arg n1 = Arg(5.6);
    Arg n2 = Arg(22.0);
    Arg n3 = Arg(37.7);

    // Then: They should contain the appropriate values
    ASSERT(n1.get_value<double>() == 5.6);
    ASSERT(n2.get_value<double>() == 22);
    ASSERT(n3.get_value<double>() == 37.7);

    SUCCESS();

}

void test_create_string_args() {
    // Given: You have instantiated the following strings
    const char *s1 = "Hello World!";
    const char *s2 = "Banana";
    const char *s3 = "Zebra";

    // When: You construct three string arguments from these values
    Arg a1 = Arg(s1);
    Arg a2 = Arg(s2);
    Arg a3 = Arg(s3);

    // Then: The arguments should have the same values as the strings
    ASSERT(strcmp(a1.get_value<const char *>(), s1) == 0);
    ASSERT(strcmp(a2.get_value<const char *>(), s2) == 0);
    ASSERT(strcmp(a3.get_value<const char *>(), s3) == 0);

    SUCCESS();
}

void test_create_unit_args() {
   // Given: You have created a dummy argument of type UNIT
   Arg a1 = Arg(ArgType::ARG_UNIT);

   // When: You get the string value of the argument and the type
   ArgType type = a1.get_type();
   const char *contents = a1.get_value<const char *>();

   // Then: The type should be UNIT, and the contents should be "()"
   ASSERT(strcmp("()", contents) == 0);
   ASSERT(type == ArgType::ARG_UNIT);
   SUCCESS();
}

int main(int argc, char *argv[]) {
    
    test_create_empty_args();
    test_create_number_args();
    test_create_string_args();
    test_create_unit_args();
    return 0;
}
