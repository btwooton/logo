#ifndef DISPATCH_TABLE_H_
#define DISPATCH_TABLE_H_
#include "procedure.hpp"
#include <unordered_map>
#include <string>

class DispatchTable {

    public:

        unsigned int get_size() const;
        void add_binding(const char *name, Procedure p);
        Procedure get_bound_procedure(const char *name);
        bool has_binding(const char *name) const;

    private:
        std::unordered_map<std::string, Procedure> dt;
};

#endif
