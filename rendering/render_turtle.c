#include <allegro5/allegro_primitives.h>
#include <math.h>
#include "render_turtle.h"
#include "../turtle/turtle.h"

void render_turtle(Turtle t) {

    int heading = get_heading(t);
    int x = getx(t);
    int y = gety(t);

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

void rendered_forward(Turtle t, float amt) {
    if (!isdown(t)) {
        return;
    }
    
    int oldx = getx(t);
    int oldy = gety(t);

    forward(t, amt);

    ALLEGRO_COLOR color = al_map_rgb(0, 0, 0);
    al_draw_line(oldx, oldy, getx(t), gety(t), color, 1); 
}

void rendered_backward(Turtle t, float amt) {
    if (!isdown(t)) { 
        return;
    }

    int oldx = getx(t);
    int oldy = gety(t);

    backward(t, amt);

    ALLEGRO_COLOR color = al_map_rgb(0, 0, 0);
    al_draw_line(oldx, oldy, getx(t), gety(t), color, 1);
}

