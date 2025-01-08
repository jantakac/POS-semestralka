#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include "constants.h"


typedef struct Game Game;
void game_init(Game *self);
Game *game_create();
void game_reset(Game *self);
void game_destroy(Game *self);
void game_move(Game *self);
void game_logic(Game *self);
bool game_isgameover(Game *self);
void game_gameloop(Game *self);
void game_setkey(Game *self, char keytoset);
char *game_generatemap(Game *self);
#endif