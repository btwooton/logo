#include <cassert>
#include <cstdio>
#include <cstring>
#include "args.hpp"
#include "procedure.hpp"
#include "dispatch_table.hpp"

#define ASSERT(condition) if(!(condition)) { \
    printf("Assertion failed at line %d in file %s\n", __LINE__, __FILE__); \
    assert(false); }

#define SUCCESS() printf("Test %s has passed\n", __func__);


void test_add_to_table() {
    // Given: You have created the following Procedures and DispatchTable 
    Procedure p1 = Procedure("Add", 2, nullptr);
    Procedure p2 = Procedure("Subtract", 2, nullptr);
    DispatchTable dt = DispatchTable();

    // When: You add the bindings for the procedures to the dispatch table
    dt.add_binding(p1.get_name(), p1);
    dt.add_binding(p2.get_name(), p2);

    // Then: You should be able to get the bound procedures back
    Procedure o1 = dt.get_bound_procedure(p1.get_name());
    Procedure o2 = dt.get_bound_procedure(p2.get_name());

    ASSERT(strcmp(o1.get_name(), p1.get_name()) == 0);
    ASSERT(strcmp(o2.get_name(), p2.get_name()) == 0);
    ASSERT(o1 == p1);
    ASSERT(o2 == p2);

    SUCCESS();
}

void test_add_with_resize() {
    // Given: You have created the following Procedures and DispatchTable
    Procedure p1 = Procedure("Add", 2, nullptr);
    Procedure p2 = Procedure("Subtract", 2, nullptr);
    Procedure p3 = Procedure("Multiply", 2, nullptr);
    Procedure p4 = Procedure("Divide", 2, nullptr);
    Procedure p5 = Procedure("And", 2, nullptr);

    DispatchTable dt = DispatchTable();

    // When: You add the bindings for the procedures to the dispatch table
    dt.add_binding(p1.get_name(), p1);
    dt.add_binding(p2.get_name(), p2);
    dt.add_binding(p3.get_name(), p3);
    dt.add_binding(p4.get_name(), p4);
    dt.add_binding(p5.get_name(), p5);

    // Then: The DispatchTable should have the appropriate size
    ASSERT(5 == dt.get_size());

    // Then: You should be able to get the procedures back from the table
    Procedure o1 = dt.get_bound_procedure(p1.get_name());
    Procedure o2 = dt.get_bound_procedure(p2.get_name());
    Procedure o3 = dt.get_bound_procedure(p3.get_name());
    Procedure o4 = dt.get_bound_procedure(p4.get_name());
    Procedure o5 = dt.get_bound_procedure(p5.get_name());

    ASSERT(o1 == p1);
    ASSERT(o2 == p2);
    ASSERT(o3 == p3);
    ASSERT(o4 == p4);
    ASSERT(o5 == p5);

    SUCCESS();
}

void test_has_binding() {
    // Given: You have created the following procedures
    Procedure p1 = Procedure("Add", 2, nullptr);
    Procedure p2 = Procedure("Subtract", 2, nullptr);
    Procedure p3 = Procedure("Multiply", 2, nullptr);
    Procedure p4 = Procedure("Divide", 2, nullptr);

    // When: You add the procedures to a dispatch table
    DispatchTable dt = DispatchTable();
    dt.add_binding(p1.get_name(), p1);
    dt.add_binding(p2.get_name(), p2);
    dt.add_binding(p3.get_name(), p3);
    dt.add_binding(p4.get_name(), p4);

    // Then: The dispatch table should have the appropriate bindings
    ASSERT(dt.has_binding("Add"));
    ASSERT(dt.has_binding("Subtract"));
    ASSERT(dt.has_binding("Multiply"));
    ASSERT(dt.has_binding("Divide"));
    
    SUCCESS();

}

int main(int argc, char *argv[]) {

    test_add_to_table();
    test_add_with_resize();
    test_has_binding();
    return 0;
}
