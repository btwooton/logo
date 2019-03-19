#include <vector>
#include <cassert>
#include "args.hpp"


void Args::add_arg(Arg arg) {
    args.push_back(arg);
}

unsigned int Args::get_arg_count() const {
    return args.size();
}

Arg Args::get_arg(unsigned int index) const {
    assert(index < args.size());
    return args[index];
}
