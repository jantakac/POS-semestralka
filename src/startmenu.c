#include "startmenu.h"



struct StartMenu {
	ITEM *startmenu_items[4];
	ITEM *gamemenu_items[3];
	MENU **activemenu;
	MENU *startmenu;
	MENU *gamemenu;
    WINDOW *startmenu_win;
	WINDOW *gamemenu_win;
	
    int n_startmenu_items, n_gamemenu_items, i, c;
	// startmenu_request '0' = NULL, 'N' = NEW GAME, 'C' = CONNECT TO EXISTING, 'Q' = EXIT
	char startmenu_request;
	// gamemode_option 'C' = CLASSIC, 'T' = TIMED
	char gamemode_option;
};

void set_startmenu_request(StartMenu *self, const char *name) {
	if (strcmp(name, "New Game") == 0) {
		self->startmenu_request = 'N';
	} else if (strcmp(name, "Connect to existing") == 0) {
		self->startmenu_request = 'C';
	} else {
		self->startmenu_request = 'Q';
	}
}

void set_gamemode_option(StartMenu *self, const char *name) {
	if (strcmp(name, "Classic") == 0) {
		self->gamemode_option = 'C';
	} else {
		self->gamemode_option = 'T';
	}
}

void startmenu_init(StartMenu *self) {
	self->startmenu_items[0] = new_item("New Game", "");
	self->startmenu_items[1] = new_item("Connect to existing", "");
	self->startmenu_items[2] = new_item("Exit", "");
	self->startmenu_items[3] = NULL;
	self->n_startmenu_items = 4;

	self->gamemenu_items[0] = new_item("Classic", "");
	self->gamemenu_items[1] = new_item("Timed", "");
	self->gamemenu_items[2] = NULL;
	self->n_gamemenu_items = 3;

	self->startmenu_request = '0';
	self->gamemode_option = '0';

	initscr();
	start_color();
    cbreak();
    noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_GREEN, COLOR_BLUE);

	self->startmenu = new_menu((ITEM **)self->startmenu_items);
	self->gamemenu = new_menu((ITEM **)self->gamemenu_items);

    self->startmenu_win = newwin(10, 40, 1, 1);
	self->gamemenu_win = newwin(10, 40, 1, 1);
    keypad(self->startmenu_win, TRUE);
	box(self->startmenu_win, 0, 0);
	box(self->gamemenu_win, 0, 0);

    set_menu_win(self->startmenu, self->startmenu_win);
    set_menu_sub(self->startmenu, derwin(self->startmenu_win, 5, 38, 3, 2));
	set_menu_sub(self->gamemenu, derwin(self->gamemenu_win, 5, 38, 3, 2));

    
	print_in_middle(self->startmenu_win, 1, 0, 40, "SNAKE", COLOR_PAIR(1));
	mvprintw(LINES - 2, 0, "F1 to exit");
	refresh();

	post_menu(self->startmenu);
	wrefresh(self->startmenu_win);
	self->activemenu = &self->startmenu;
	

	while((self->c = wgetch(stdscr)) != KEY_F(1))
	{       
        switch(self->c) {	
            case KEY_DOWN:
				menu_driver(*self->activemenu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(*self->activemenu, REQ_UP_ITEM);
				break;
            case 10:
                ITEM *current = current_item(*self->activemenu);
				if (*self->activemenu != self->gamemenu) {
					set_startmenu_request(self, item_name(current));
				} else {
					set_gamemode_option(self, item_name(current));
					goto menuloop_out;
				}
				if (*self->activemenu != self->gamemenu && self->startmenu_request == 'N') {
					post_menu(self->gamemenu);
					wrefresh(self->gamemenu_win);
					self->activemenu = &self->gamemenu;
				}
				// todo: implementovat connect to existing
				if (self->startmenu_request == 'Q' || self->startmenu_request == 'C') {
					goto menuloop_out;
				}
                break;
		}
        wrefresh(*self->activemenu == self->startmenu ? self->startmenu_win : self->gamemenu_win);
	}	
menuloop_out:
	startmenu_destroy(self);
}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color) {
	int length, x, y;
	float temp;

	if(win == NULL) {
		win = stdscr;
	}
	getyx(win, y, x);
	if(startx != 0) {
		x = startx;
	}
	if(starty != 0) {
		y = starty;
	}
	if(width == 0) {
		width = 80;
	}

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}


StartMenu *startmenu_create()
{
	StartMenu *self = malloc(sizeof(StartMenu));
	startmenu_init(self);
	return self;
}

void startmenu_destroy(StartMenu *self)
{
	if (self) {
		unpost_menu(self->gamemenu);
		unpost_menu(self->startmenu);
		free_menu(self->gamemenu);
		free_menu(self->startmenu);
		for(self->i = 0; self->i < self->n_gamemenu_items; ++(self->i)) {
			free_item(self->gamemenu_items[self->i]);
		}
		for(self->i = 0; self->i < self->n_startmenu_items; ++(self->i)) {
			free_item(self->startmenu_items[self->i]);
		}
		endwin();
		free(self);
	}
}

char startmenu_getrequest(StartMenu *self) {
	return self->startmenu_request;
}

char startmenu_getgamemode(StartMenu *self) {
	return self->gamemode_option;
}

