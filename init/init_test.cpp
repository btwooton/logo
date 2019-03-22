#include "init_allegro.hpp"

int main(int argc, char *argv[]) {
    int result = init_allegro(640, 480, 60);
    al_rest(10);

    return result;

}
