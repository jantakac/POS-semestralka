#ifndef STARTMENU_H
#define STARTMENU_H

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <menu.h>
#include <string.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

typedef struct StartMenu StartMenu;
void startmenu_init(StartMenu *self);
StartMenu *startmenu_create();
void startmenu_destroy(StartMenu *self);

char startmenu_getrequest(StartMenu *self);
char menu_getgamemode(StartMenu *self);

void set_startmenu_request(StartMenu *self, const char* name);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

#endif