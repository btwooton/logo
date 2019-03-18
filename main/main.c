#include <math.h>
#include <stdio.h>
#include "../turtle/turtle.h"
#include "../init/init_allegro.h"
#include "../init/init_turtle.h"
#include "../init/init_dispatch.h"
#include "../runtime/wrappers.h"
#include "../rendering/render_turtle.h"
#include "../lang/args.h"
#include "../lang/dispatch_table.h"
#include "../lang/procedure.h"



int main(int argc, char *argv[]) {

    init_allegro(800, 800, 60);

    init_turtle(400, 400, 0, true);
    init_dispatch_table();
    
    al_clear_to_color(al_map_rgb(255, 255, 255));

    render_turtle(__turtle__);
    Args rargs = create_args(1);
    add_arg(rargs, create_number_argument(90));

    for (int j = 1; j <= 10; j++) {
        Args fargs = create_args(1);
        add_arg(fargs, create_number_argument(j * 10));

        for (int i = 0; i < 4; i++) {
            Args res1 = call(
                    get_bound_procedure(__dispatch_table__, "forward"), 
                    fargs
                    );
            Args res2 = call(
                    get_bound_procedure(__dispatch_table__, "right"),
                    rargs
                    );
            destroy_args(res1);
            destroy_args(res2);
        }
        destroy_args(fargs);

    }

    destroy_args(rargs);
    
    al_flip_display();

    al_rest(5);

    al_destroy_event_queue(event_queue);
    al_destroy_timer(timer);
    al_destroy_display(display);

    return 0;

}
