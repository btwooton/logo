#ifndef WRAPPERS_H_
#define WRAPPERS_H_
#include "../lang/args.hpp"

extern Args (*wforward)(Args a);
extern Args (*wbackward)(Args a);
extern Args (*wgetx)(Args a);
extern Args (*wgety)(Args a);
extern Args (*wget_heading)(Args a);
extern Args (*wsetx)(Args a);
extern Args (*wsety)(Args a);
extern Args (*wset_heading)(Args a);
extern Args (*wright)(Args a);
extern Args (*wleft)(Args a);
extern Args (*wpenup)(Args a);
extern Args (*wpendown)(Args a);
extern Args (*wisdown)(Args a);
extern Args (*wadd)(Args a);
extern Args (*wsubtract)(Args a);
extern Args (*wmultiply)(Args a);
extern Args (*wdivide)(Args a);
extern Args (*wequal)(Args a);
extern Args (*wlessthan)(Args a);
extern Args (*wgreaterthan)(Args a);
extern Args (*wclean)(Args a);

#endif
