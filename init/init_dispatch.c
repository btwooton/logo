#include <stdlib.h>
#include "init_dispatch.h"
#include "../runtime/wrappers.h"

DispatchTable __dispatch_table__ = NULL;

void init_dispatch_table() {
   __dispatch_table__ = create_dispatch_table(25);
   add_binding(
           &__dispatch_table__, "forward", 
           create_native("forward", 1, wforward)
           );
   add_binding(
           &__dispatch_table__, "backward",
           create_native("backward", 1, wbackward)
           );
   add_binding(
           &__dispatch_table__, "getx",
           create_native("getx", 0, wgetx)
           );
   add_binding(
           &__dispatch_table__, "gety",
           create_native("gety", 0, wgety)
           );
   add_binding(
           &__dispatch_table__, "getheading",
           create_native("getheading", 0, wget_heading)
           );
   add_binding(
           &__dispatch_table__, "setx",
           create_native("setx", 1, wsetx)
           );
   add_binding(
           &__dispatch_table__, "sety",
           create_native("sety", 1, wsety)
           );
   add_binding(
           &__dispatch_table__, "setheading",
           create_native("setheading", 1, wset_heading)
           );
   add_binding(
           &__dispatch_table__, "right",
           create_native("right", 1, wright)
           );
   add_binding(
           &__dispatch_table__, "left",
           create_native("left", 1, wleft)
           );
   add_binding(
           &__dispatch_table__, "penup",
           create_native("penup", 0, wpenup)
           );
   add_binding(
           &__dispatch_table__, "pendown",
           create_native("pendown", 0, wpendown)
           );
   add_binding(
           &__dispatch_table__, "isdown",
           create_native("isdown", 0, wisdown)
           );
   add_binding(
           &__dispatch_table__, "+",
           create_native("+", 2, wadd)
           );
   add_binding(
           &__dispatch_table__, "-",
           create_native("-", 2, wsubtract)
           );
   add_binding(
           &__dispatch_table__, "*",
           create_native("*", 2, wmultiply)
           );
   add_binding(
           &__dispatch_table__, "/",
           create_native("/", 2, wdivide)
           );
   add_binding(
           &__dispatch_table__, "=",
           create_native("=", 2, wequal)
           );
   add_binding(
           &__dispatch_table__, "<",
           create_native("<", 2, wlessthan)
           );
   add_binding(
           &__dispatch_table__, ">",
           create_native(">", 2, wgreaterthan)
           );
}
