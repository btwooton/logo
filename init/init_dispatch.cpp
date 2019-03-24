#include <cstdlib>
#include "init_dispatch.hpp"
#include "../runtime/wrappers.hpp"

DispatchTable __dispatch_table__ = DispatchTable();

void init_dispatch_table() {
    __dispatch_table__.add_binding(
       "forward", 
       Procedure("forward", 1, wforward)
    );
    __dispatch_table__.add_binding(
       "backward", 
       Procedure("backward", 1, wbackward)
    );
    __dispatch_table__.add_binding(
        "getx",
        Procedure("getx", 0, wgetx)
    );
    __dispatch_table__.add_binding(
        "gety",
        Procedure("gety", 0, wgety)
    );
    __dispatch_table__.add_binding(
        "getheading",
        Procedure("getheading", 0, wget_heading)
    );
    __dispatch_table__.add_binding(
        "setx",
        Procedure("setx", 1, wsetx)
    );
    __dispatch_table__.add_binding(
        "sety",
        Procedure("sety", 1, wsety)
    );
    __dispatch_table__.add_binding(
        "setheading",
        Procedure("setheading", 1, wset_heading)
    );
    __dispatch_table__.add_binding(
        "right",
        Procedure("right", 1, wright)
    );
    __dispatch_table__.add_binding(
        "left",
        Procedure("left", 1, wleft)
    );
    __dispatch_table__.add_binding(
        "penup",
        Procedure("penup", 0, wpenup)
    );
    __dispatch_table__.add_binding(
        "pendown",
        Procedure("pendown", 0, wpendown)
    );
    __dispatch_table__.add_binding(
        "isdown",
        Procedure("isdown", 0, wisdown)
    );
    __dispatch_table__.add_binding(
        "+",
        Procedure("+", 2, wadd)
    );
    __dispatch_table__.add_binding(
        "-",
        Procedure("-", 2, wsubtract)
    );
    __dispatch_table__.add_binding(
        "*",
        Procedure("*", 2, wmultiply)
    );
    __dispatch_table__.add_binding(
        "/",
        Procedure("/", 2, wdivide)
    );
    __dispatch_table__.add_binding(
        "=",
        Procedure("=", 2, wequal)
   );
    __dispatch_table__.add_binding(
        "<",
        Procedure("<", 2, wlessthan)
    );
    __dispatch_table__.add_binding(
        ">",
        Procedure(">", 2, wgreaterthan)
    );
    __dispatch_table__.add_binding(
        "clean",
        Procedure("clean", 0, wclean)
    );
    __dispatch_table__.add_binding(
        "setpensize",
        Procedure("setpensize", 1, wsetpensize)
    );
}
