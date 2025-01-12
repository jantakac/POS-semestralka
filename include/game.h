#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include <time.h>
#include "constants.h"
#include "sockstruct.h"


typedef struct Game Game;
void game_init(Game *self, int max_seconds, int gamewidth, int gameheight);
Game *game_create(int max_seconds, int gamewidth, int gameheight);
void game_reset(Game *self);
void game_destroy(Game *self);
void game_move(Game *self);
void game_logic(Game *self);
int game_getgameover(Game *self);
SnakeData *game_getsnakedataptr(Game *self);
void game_setkey(Game *self, char keytoset);
void game_setelapsedtime(Game *self, int seconds);
char *game_generatemap(Game *self);
#endif