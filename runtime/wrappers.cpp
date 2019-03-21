#include <cassert>
#include <cstdlib>
#include <cstring>
#include "wrappers.hpp"
#include "../turtle/turtle.hpp"
#include "../init/init_turtle.hpp"
#include "../lang/args.hpp"
#include "../lang/arg.hpp"
#include "../rendering/render_turtle.hpp"

Args wforward_impl(Args a) {
  Arg amount = a.get_arg(0);
  if (__turtle__.isdown()) {
      rendered_forward(__turtle__, amount.get_value<double>());
      Args result = Args();
      result.add_arg(Arg(ArgType::ARG_UNIT));
      return result;
  }
  __turtle__.forward(amount.get_value<double>()); 
  Args result = Args();
  result.add_arg(Arg(ArgType::ARG_UNIT));
  return result;
}

Args wbackward_impl(Args a) {
   Arg amount = a.get_arg(0);
   if (__turtle__.isdown()) {
      rendered_backward(__turtle__, amount.get_value<double>());
      Args result = Args();
      result.add_arg(Arg(ArgType::ARG_UNIT));
      return result;
  }
   __turtle__.backward(amount.get_value<double>());
   Args result = Args();
   result.add_arg(Arg(ArgType::ARG_UNIT));
   return result;
}

Args wright_impl(Args a) {
    Arg amount = a.get_arg(0);
    __turtle__.right(amount.get_value<double>());
    Args result = Args();
    result.add_arg(Arg(ArgType::ARG_UNIT));
    return result;
}

Args wleft_impl(Args a) {
    Arg amount = a.get_arg(0);
    __turtle__.left(amount.get_value<double>());
    Args result = Args();
    result.add_arg(Arg(ArgType::ARG_UNIT));
    return result;
}

Args wgetx_impl(Args a) {
    Args result = Args();
    Arg result_arg = Arg(__turtle__.get_x());
    result.add_arg(result_arg);
    return result;
}

Args wgety_impl(Args a) {
    Args result = Args();
    Arg result_arg = Arg(__turtle__.get_y());
    result.add_arg(result_arg);
    return result;
}

Args wget_heading_impl(Args a) {
    Args result = Args();
    Arg result_arg = Arg(__turtle__.get_heading());
    result.add_arg(result_arg);
    return result;
}

Args wsetx_impl(Args a) {
    Arg amount = a.get_arg(0);
    __turtle__.set_x(amount.get_value<double>());
    Args result = Args();
    result.add_arg(Arg(ArgType::ARG_UNIT));
    return result;
}

Args wsety_impl(Args a) {
    Arg amount = a.get_arg(0);
    __turtle__.set_y(amount.get_value<double>());
    Args result = Args();
    result.add_arg(Arg(ArgType::ARG_UNIT));
    return result;
}

Args wset_heading_impl(Args a) {
    Arg amount = a.get_arg(0);
    __turtle__.set_heading(amount.get_value<double>());
    Args result = Args();
    result.add_arg(Arg(ArgType::ARG_UNIT));
    return result;
}

Args wpenup_impl(Args a) {
    __turtle__.penup();
    Args result = Args();
    result.add_arg(Arg(ArgType::ARG_UNIT));
    return result;
}

Args wpendown_impl(Args a) {
    __turtle__.pendown();
    Args result = Args();
    result.add_arg(Arg(ArgType::ARG_UNIT));
    return result;
}

Args wisdown_impl(Args a) {
    Args result = Args();
    result.add_arg(Arg(__turtle__.isdown()));
    return result;
}

Args wadd_impl(Args a) {
    Args result = Args();
    Arg n1 = a.get_arg(0);
    Arg n2 = a.get_arg(1);

    double d1 = n1.get_value<double>();
    double d2 = n2.get_value<double>();

    Arg result_arg = Arg(d1 + d2);
    result.add_arg(result_arg);
    return result;
}

Args wsubtract_impl(Args a) {
    Args result = Args();
    Arg n1 = a.get_arg(0);
    Arg n2 = a.get_arg(1);

    double d1 = n1.get_value<double>();
    double d2 = n2.get_value<double>();
    
    Arg result_arg = Arg(d1 - d2);
    result.add_arg(result_arg);
    return result;
}

Args wmultiply_impl(Args a) {
    Args result = Args();
    Arg n1 = a.get_arg(0);
    Arg n2 = a.get_arg(1);

    double d1 = n1.get_value<double>();
    double d2 = n2.get_value<double>();

    Arg result_arg = Arg(d1 * d2);
    result.add_arg(result_arg);
    return result;
}

Args wdivide_impl(Args a) {
    Args result = Args();
    Arg n1 = a.get_arg(0);
    Arg n2 = a.get_arg(1);

    double d1 = n1.get_value<double>();
    double d2 = n2.get_value<double>();

    Arg result_arg = Arg(d1 / d2);
    result.add_arg(result_arg);
    return result;
}

Args wequal_impl(Args a) {
    Args result = Args();
    Arg a1 = a.get_arg(0);
    Arg a2 = a.get_arg(1);

    ArgType t1 = a1.get_type();
    ArgType t2 = a2.get_type();

    if (t1 != t2) {
        result.add_arg(Arg(false));
    } else if (t1 == ArgType::ARG_NUMBER) {
        double d1 = a1.get_value<double>();
        double d2 = a2.get_value<double>();
        result.add_arg(Arg(d1 == d2));
    } else if (t1 == ArgType::ARG_BOOLEAN) {
        bool b1 = a1.get_value<bool>();
        bool b2 = a2.get_value<bool>();
        result.add_arg(Arg(b1 == b2));
    } else if (t1 == ArgType::ARG_STRING) {
        const char *s1 = a1.get_value<const char *>();
        const char *s2 = a2.get_value<const char *>();
        result.add_arg(Arg(strcmp(s1, s2) == 0));
    } else {
        result.add_arg(Arg(true));
    }
    return result;
}

Args wlessthan_impl(Args a) {
    Args result = Args();
    Arg a1 = a.get_arg(0);
    Arg a2 = a.get_arg(1);
    ArgType t1 = a1.get_type();
    ArgType t2 = a2.get_type();

    assert(t1 == ArgType::ARG_NUMBER);

    double d1 = a1.get_value<double>();
    double d2 = a2.get_value<double>();

    result.add_arg(Arg(d1 < d2));
    return result;
}

Args wgreaterthan_impl(Args a) {
    Args result = Args();
    Arg a1 = a.get_arg(0);
    Arg a2 = a.get_arg(1);

    assert(a1.get_type() == ArgType::ARG_NUMBER);

    double d1 = a1.get_value<double>();
    double d2 = a2.get_value<double>();

    result.add_arg(Arg(d1 > d2));
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
