#include <cstdio>
#include "init_allegro.hpp"

ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_BITMAP *draw_surface = NULL;

int init_allegro(int width, int height, int fps) {

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    display = al_create_display(width, height);

    if (!display) {
        fprintf(stderr, "failed to initialize display!\n");
        return -1;
    }

    timer = al_create_timer(1.0/fps);

    if (!timer) {
        fprintf(stderr, "failed to initialize timer!\n");
        al_destroy_display(display);
        return -1;
    }

    event_queue = al_create_event_queue();

    if (!event_queue) {
        fprintf(stderr, "failed to initialize event_queue!\n");
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    draw_surface = al_create_bitmap(width, height);

    if (!draw_surface) {
        fprintf(stderr, "failed to create draw_surface\n");
        al_destroy_event_queue(event_queue);
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    al_init_primitives_addon();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    return 0;

}
