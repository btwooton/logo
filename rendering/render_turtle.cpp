#include <allegro5/allegro_primitives.h>
#include <cmath>
#include "render_turtle.hpp"
#include "../turtle/turtle.hpp"

void render_turtle(Turtle& t) {

    int heading = t.get_heading();
    int x = t.get_x();
    int y = t.get_y();

    int tipx = x + cos(heading*PI/180) * 10;
    int tipy = y + sin(heading*PI/180) * 10;

    int blhd = (heading + 120) % 360;
    int blx = x + cos(blhd*PI/180) * 5;
    int bly = y + sin(blhd*PI/180) * 5;

    int brhd = (heading - 120) % 360;
    int brx = x + cos(brhd*PI/180) * 5;
    int bry = y + sin(brhd*PI/180) * 5;

    ALLEGRO_COLOR color = al_map_rgb(0, 0, 0);
    
    al_draw_filled_triangle(blx, bly, tipx, tipy, brx, bry, color);

}

void rendered_forward(Turtle& t, double amt) {
    if (!t.isdown()) {
        return;
    }
    
    int oldx = t.get_x();
    int oldy = t.get_y();

    t.forward(amt);

    ALLEGRO_COLOR color = al_map_rgb(0, 0, 0);
    al_draw_line(oldx, oldy, t.get_x(), t.get_y(), color, 1); 
}

void rendered_backward(Turtle& t, double amt) {
    if (!t.isdown()) { 
        return;
    }

    int oldx = t.get_x();
    int oldy = t.get_y();

    t.backward(amt);

    ALLEGRO_COLOR color = al_map_rgb(0, 0, 0);
    al_draw_line(oldx, oldy, t.get_x(), t.get_y(), color, 1);
}

void rendered_clean() {
   al_clear_to_color(al_map_rgb(255, 255, 255)); 
}
