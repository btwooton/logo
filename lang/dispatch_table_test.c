#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include "args.h"
#include "procedure.h"
#include "dispatch_table.h"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in file %s\n", __LINE__, __FILE__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);

void test_create_dispatch_table() {
    // Given: You have created a DispatchTable of capacity 10
    DispatchTable dt = create_dispatch_table(10);

    // When: You get the size of the DispatchTable
    unsigned int size = get_size(dt);

    // Then: The size should be 0
    ASSERT(size == 0);
    destroy_dispatch_table(dt);
    SUCCESS();
}

void test_add_to_table() {
    // Given: You have created the following Procedures and DispatchTable 
    Procedure p1 = create_native("Add", 2, NULL);
    Procedure p2 = create_native("Subtract", 2, NULL);
    DispatchTable dt = create_dispatch_table(10);

    // When: You add the bindings for the procedures to the dispatch table
    add_binding(&dt, get_name(p1), p1);
    add_binding(&dt, get_name(p2), p2);

    // Then: You should be able to get the bound procedures back
    Procedure o1 = get_bound_procedure(dt, get_name(p1));
    Procedure o2 = get_bound_procedure(dt, get_name(p2));

    ASSERT(get_name(o1) == get_name(p1));
    ASSERT(get_name(o2) == get_name(p2));
    ASSERT(o1 == p1);
    ASSERT(o2 == p2);

    destroy_dispatch_table(dt);
    destroy_procedure(p1);
    destroy_procedure(p2);
    SUCCESS();

}

void test_add_with_resize() {
    // Given: You have created the following Procedures and DispatchTable
    Procedure p1 = create_native("Add", 2, NULL);
    Procedure p2 = create_native("Subtract", 2, NULL);
    Procedure p3 = create_native("Multiply", 2, NULL);
    Procedure p4 = create_native("Divide", 2, NULL);
    Procedure p5 = create_native("And", 2, NULL);

    DispatchTable dt = create_dispatch_table(2);

    // When: You add the bindings for the procedures to the dispatch table
    add_binding(&dt, get_name(p1), p1);
    add_binding(&dt, get_name(p2), p2);
    add_binding(&dt, get_name(p3), p3);
    add_binding(&dt, get_name(p4), p4);
    add_binding(&dt, get_name(p5), p5);

    // Then: The DispatchTable should have the appropriate size
    ASSERT(5 == get_size(dt));

    // Then: You should be able to get the procedures back from the table
    Procedure o1 = get_bound_procedure(dt, get_name(p1));
    Procedure o2 = get_bound_procedure(dt, get_name(p2));
    Procedure o3 = get_bound_procedure(dt, get_name(p3));
    Procedure o4 = get_bound_procedure(dt, get_name(p4));
    Procedure o5 = get_bound_procedure(dt, get_name(p5));

    ASSERT(o1 == p1);
    ASSERT(o2 == p2);
    ASSERT(o3 == p3);
    ASSERT(o4 == p4);
    ASSERT(o5 == p5);

    destroy_procedure(p1);
    destroy_procedure(p2);
    destroy_procedure(p3);
    destroy_procedure(p4);
    destroy_procedure(p5);
    destroy_dispatch_table(dt);
    SUCCESS();
}

void test_has_binding() {
    // Given: You have created the following procedures
    Procedure p1 = create_native("Add", 2, NULL);
    Procedure p2 = create_native("Subtract", 2, NULL);
    Procedure p3 = create_native("Multiply", 2, NULL);
    Procedure p4 = create_native("Divide", 2, NULL);

    // When: You add the procedures to a dispatch table
    DispatchTable dt = create_dispatch_table(5);
    add_binding(&dt, get_name(p1), p1);
    add_binding(&dt, get_name(p2), p2);
    add_binding(&dt, get_name(p3), p3);
    add_binding(&dt, get_name(p4), p4);

    // Then: The dispatch table should have the appropriate bindings
    ASSERT(has_binding(dt, "Add"));
    ASSERT(has_binding(dt, "Subtract"));
    ASSERT(has_binding(dt, "Multiply"));
    ASSERT(has_binding(dt, "Divide"));
    
    destroy_procedure(p1);
    destroy_procedure(p2);
    destroy_procedure(p3);
    destroy_procedure(p4);
    destroy_dispatch_table(dt);
    SUCCESS();



}

int main(int argc, char *argv[]) {

    test_create_dispatch_table();
    test_add_to_table();
    test_add_with_resize();
    test_has_binding();
    return 0;
}
