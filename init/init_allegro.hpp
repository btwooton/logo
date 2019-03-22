#ifndef INIT_ALLEGRO_H_
#define INIT_ALLEGRO_H_

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_BITMAP *draw_surface;

extern int init_allegro(int width, int height, int fps);


#endif
