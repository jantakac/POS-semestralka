#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct Menu Menu;
void menu_init(Menu *self);
Menu *menu_create();
void menu_destroy(Menu *self);


#endif