#include "menu.h"

#define TIME_BETWEEN_FRAMES_30FPS 33 // cca 30fps, lower number more fps

void main() {

    Menu *menu = menu_create();

    /*
    Game *game = game_create();

    while (!game_isgameover(game)) {
        game_gameloop(game);
        sleep(TIME_BETWEEN_FRAMES_30FPS);
    }
    game_destroy(game);
    */
    menu_destroy(menu);
}