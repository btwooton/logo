#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "wrappers.h"
#include "../turtle/turtle.h"
//#include "../rendering/render_turtle.h"
#include "../init/init_turtle.h"
#include "../lang/args.h"
#include "../lang/arg.h"

Args wforward_impl(Args a) {
  Arg amount = get_arg(a, 0);
  forward(__turtle__, get_number_value(amount)); Args result = create_args(1);
  add_arg(result, create_dummy_argument(ARG_UNIT));
  return result;
}

Args wbackward_impl(Args a) {
   Arg amount = get_arg(a, 0);
   backward(__turtle__, get_number_value(amount));
   Args result = create_args(1);
   add_arg(result, create_dummy_argument(ARG_UNIT));
   return result;
}

Args wright_impl(Args a) {
    Arg amount = get_arg(a, 0);
    right(__turtle__, get_number_value(amount));
    Args result = create_args(1);
    add_arg(result, create_dummy_argument(ARG_UNIT));
    return result;
}

Args wleft_impl(Args a) {
    Arg amount = get_arg(a, 0);
    left(__turtle__, get_number_value(amount));
    Args result = create_args(1);
    add_arg(result, create_dummy_argument(ARG_UNIT));
    return result;
}

Args wgetx_impl(Args a) {
    Args result = create_args(1);
    Arg result_arg = create_number_argument(getx(__turtle__));
    add_arg(result, result_arg);
    return result;
}

Args wgety_impl(Args a) {
    Args result = create_args(1);
    Arg result_arg = create_number_argument(gety(__turtle__));
    add_arg(result, result_arg);
    return result;
}

Args wget_heading_impl(Args a) {
    Args result = create_args(1);
    Arg result_arg = create_number_argument(get_heading(__turtle__));
    add_arg(result, result_arg);
    return result;
}

Args wsetx_impl(Args a) {
    Arg amount = get_arg(a, 0);
    setx(__turtle__, get_number_value(amount));
    Args result = create_args(1);
    add_arg(result, create_dummy_argument(ARG_UNIT));
    return result;
}

Args wsety_impl(Args a) {
    Arg amount = get_arg(a, 0);
    sety(__turtle__, get_number_value(amount));
    Args result = create_args(1);
    add_arg(result, create_dummy_argument(ARG_UNIT));
    return result;
}

Args wset_heading_impl(Args a) {
    Arg amount = get_arg(a, 0);
    set_heading(__turtle__, get_number_value(amount));
    Args result = create_args(1);
    add_arg(result, create_dummy_argument(ARG_UNIT));
    return result;
}

Args wpenup_impl(Args a) {
    penup(__turtle__);
    Args result = create_args(1);
    add_arg(result, create_dummy_argument(ARG_UNIT));
    return result;
}

Args wpendown_impl(Args a) {
    pendown(__turtle__);
    Args result = create_args(1);
    add_arg(result, create_dummy_argument(ARG_UNIT));
    return result;
}

Args wisdown_impl(Args a) {
    Args result = create_args(1);
    add_arg(result, create_bool_argument(isdown(__turtle__)));
    return result;
}

Args wadd_impl(Args a) {
    Args result = create_args(1);
    Arg n1 = get_arg(a, 0);
    Arg n2 = get_arg(a, 1);

    double d1 = get_number_value(n1);
    double d2 = get_number_value(n2);

    Arg result_arg = create_number_argument(d1 + d2);
    add_arg(result, result_arg);
    return result;
}

Args wsubtract_impl(Args a) {
    Args result = create_args(1);
    Arg n1 = get_arg(a, 0);
    Arg n2 = get_arg(a, 1);

    double d1 = get_number_value(n1);
    double d2 = get_number_value(n2);
    
    Arg result_arg = create_number_argument(d1 - d2);
    add_arg(result, result_arg);
    return result;
}

Args wmultiply_impl(Args a) {
    Args result = create_args(1);
    Arg n1 = get_arg(a, 0);
    Arg n2 = get_arg(a, 1);

    double d1 = get_number_value(n1);
    double d2 = get_number_value(n2);

    Arg result_arg = create_number_argument(d1 * d2);
    add_arg(result, result_arg);
    return result;
}

Args wdivide_impl(Args a) {
    Args result = create_args(1);
    Arg n1 = get_arg(a, 0);
    Arg n2 = get_arg(a, 1);

    double d1 = get_number_value(n1);
    double d2 = get_number_value(n2);

    Arg result_arg = create_number_argument(d1 / d2);
    add_arg(result, result_arg);
    return result;
}

Args wequal_impl(Args a) {
    Args result = create_args(1);
    Arg a1 = get_arg(a, 0);
    Arg a2 = get_arg(a, 1);

    ArgType t1 = get_arg_type(a1);
    ArgType t2 = get_arg_type(a2);

    if (t1 != t2) {
        add_arg(result, create_bool_argument(false));
    } else if (t1 == ARG_NUMBER) {
        double d1 = get_number_value(a1);
        double d2 = get_number_value(a2);
        add_arg(result, create_bool_argument(d1 == d2));
    } else if (t1 == ARG_BOOLEAN) {
        bool b1 = get_boolean_value(a1);
        bool b2 = get_boolean_value(a2);
        add_arg(result, create_bool_argument(b1 == b2));
    } else if (t1 == ARG_STRING) {
        const char *s1 = get_string_value(a1);
        const char *s2 = get_string_value(a2);
        add_arg(result, create_bool_argument(strcmp(s1, s2) == 0));
    } else {
        add_arg(result, create_bool_argument(true));
    }
    return result;
}

Args wlessthan_impl(Args a) {
    Args result = create_args(1);
    Arg a1 = get_arg(a, 0);
    Arg a2 = get_arg(a, 1);

    ArgType t1 = get_arg_type(a1);
    ArgType t2 = get_arg_type(a2);

    assert(t1 == ARG_NUMBER);

    double d1 = get_number_value(a1);
    double d2 = get_number_value(a2);

    add_arg(result, create_bool_argument(d1 < d2));
    return result;
}

Args wgreaterthan_impl(Args a) {
    Args result = create_args(1);
    Arg a1 = get_arg(a, 0);
    Arg a2 = get_arg(a, 1);

    assert(get_arg_type(a1) == ARG_NUMBER);

    double d1 = get_number_value(a1);
    double d2 = get_number_value(a2);

    add_arg(result, create_bool_argument(d1 > d2));
    return result;
}

Args (*wforward)(Args a) = &wforward_impl;
Args (*wbackward)(Args a) = &wbackward_impl;
Args (*wgetx)(Args a) = &wgetx_impl;
Args (*wgety)(Args a) = &wgety_impl;
Args (*wget_heading)(Args a) = &wget_heading_impl;
Args (*wsetx)(Args a) = &wsetx_impl;
Args (*wsety)(Args a) = &wsety_impl;
Args (*wset_heading)(Args a) = &wset_heading_impl;
Args (*wright)(Args a) = &wright_impl;
Args (*wleft)(Args a) = &wleft_impl;
Args (*wpenup)(Args a) = &wpenup_impl;
Args (*wpendown)(Args a) = &wpendown_impl;
Args (*wisdown)(Args a) = &wisdown_impl;
Args (*wadd)(Args a) = &wadd_impl;
Args (*wsubtract)(Args a) = &wsubtract_impl;
Args (*wmultiply)(Args a) = &wmultiply_impl;
Args (*wdivide)(Args a) = &wdivide_impl;
Args (*wequal)(Args a) = &wequal_impl;
Args (*wlessthan)(Args a) = &wlessthan_impl;
Args (*wgreaterthan)(Args a) = &wgreaterthan_impl;
