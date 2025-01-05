#include "menu.h"

typedef enum {
	NEW_GAME = 0,
	TO_EXISTING = 1,
	QUIT = 2
} MenuRequest;

typedef enum {
	GAME_MODE_STANDARD = 0,
	GAME_MODE_TIMED = 1
} GameMode;

struct Menu {
	MenuRequest menu_request;
	GameMode gamemode_option;
};

void menu_init(Menu *self) {
	initscr();
	printw("Cawes");
	refresh();
	getch();
	endwin();
}


Menu *menu_create()
{
	Menu *self = malloc(sizeof(Menu));
	menu_init(self);
	
	return self;
}

void menu_destroy(Menu *self)
{
	if (self) {
		free(self);
	}
}

MenuRequest menu_getrequest(Menu *self) {
	return self->menu_request;
}

GameMode menu_getgamemode(Menu *self) {
	return self->gamemode_option;
}

