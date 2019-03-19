#ifndef ARGS_H_
#define ARGS_H_
#include "arg.hpp"
#include <vector>

class Args {

    public:

        void add_arg(Arg arg);
        unsigned int get_arg_count() const;
        Arg get_arg(unsigned int index) const;

    private:
        std::vector<Arg> args;
};


#endif
