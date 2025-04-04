#include <unordered_map>
#include <string>
#include <cstring>
#include "args.hpp"
#include "procedure.hpp"
#include "dispatch_table.hpp"
#include <stdio.h>

unsigned int DispatchTable::get_size() const {
    return dt.size();
}

void DispatchTable::add_binding(const char *name, Procedure p) {
    dt[std::string(name)] = p;
}

Procedure DispatchTable::get_bound_procedure(const char *name) {
    return dt[std::string(name)];
}

bool DispatchTable::has_binding(const char *name) const {
    return dt.find(std::string(name)) != dt.end();
}
