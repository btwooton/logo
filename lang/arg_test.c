#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "arg.h"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in file %s\n", __LINE__, __FILE__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);


void test_create_empty_args() {
    // Given: You have created dummy arguments
    Arg num_arg = create_dummy_argument(ARG_NUMBER);
    Arg str_arg = create_dummy_argument(ARG_STRING);
    Arg bool_arg = create_dummy_argument(ARG_BOOLEAN);

    // Then: They should have the appropriate default values
    ASSERT(get_number_value(num_arg) == 0.0);
    ASSERT(strcmp(get_string_value(str_arg), "") == 0);
    ASSERT(get_boolean_value(bool_arg) == false);

    destroy_argument(num_arg);
    destroy_argument(str_arg);
    destroy_argument(bool_arg);

    SUCCESS();

}

void test_create_number_args() {
    // Given: You have created numeric arguments
    Arg n1 = create_number_argument(5.6);
    Arg n2 = create_number_argument(22);
    Arg n3 = create_number_argument(37.7);

    // Then: They should contain the appropriate values
    ASSERT(get_number_value(n1) == 5.6);
    ASSERT(get_number_value(n2) == 22);
    ASSERT(get_number_value(n3) == 37.7);

    destroy_argument(n1);
    destroy_argument(n2);
    destroy_argument(n3);

    SUCCESS();

}

void test_create_string_args() {
    // Given: You have instantiated the following strings
    const char *s1 = "Hello World!";
    const char *s2 = "Banana";
    const char *s3 = "Zebra";

    // When: You construct three string arguments from these values
    Arg a1 = create_string_argument(s1);
    Arg a2 = create_string_argument(s2);
    Arg a3 = create_string_argument(s3);

    // Then: The arguments should have the same values as the strings
    ASSERT(strcmp(get_string_value(a1), s1) == 0);
    ASSERT(strcmp(get_string_value(a2), s2) == 0);
    ASSERT(strcmp(get_string_value(a3), s3) == 0);

    // When: You destroy the arguments
    destroy_argument(a1);
    destroy_argument(a2);
    destroy_argument(a3);

    // Then: The original strings should stil be valid
    ASSERT(strcmp(s1, "Hello World!") == 0);
    ASSERT(strcmp(s2, "Banana") == 0);
    ASSERT(strcmp(s3, "Zebra") == 0);

    SUCCESS();
}

void test_create_unit_args() {
   // Given: You have created a dummy argument of type UNIT
   Arg a1 = create_dummy_argument(ARG_UNIT);

   // When: You get the string value of the argument and the type
   ArgType type = get_type(a1);
   const char *contents = get_string_value(a1);

   // Then: The type should be UNIT, and the contents should be "()"
   ASSERT(strcmp("()", contents) == 0);
   ASSERT(type == ARG_UNIT);
   SUCCESS();
}

int main(int argc, char *argv[]) {
    
    test_create_empty_args();
    test_create_number_args();
    test_create_string_args();
    test_create_unit_args();
    return 0;
}
