#ifndef DISPATCH_TABLE_H_
#define DISPATCH_TABLE_H_
#include <stdbool.h>
#include "procedure.h"

typedef struct DispatchTable *DispatchTable;

extern DispatchTable create_dispatch_table(unsigned int capacity);
extern void destroy_dispatch_table(DispatchTable dt);

extern unsigned int get_size(DispatchTable dt);
extern void add_binding(DispatchTable *dt, const char *name, Procedure p);
extern Procedure get_bound_procedure(DispatchTable dt, const char *name);
extern bool has_binding(DispatchTable dt, const char *name);

#endif
