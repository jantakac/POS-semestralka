#include "startmenu.h"



struct StartMenu {
	ITEM *startmenu_items[4];
	ITEM *gamemenu_items[3];
	ITEM *dimensionmenu_items[6];
	ITEM *timemenu_items[7];
	MENU **activemenu;
	MENU *startmenu;
	MENU *gamemenu;
	MENU *dimensionmenu;
	MENU *timemenu;
    WINDOW *startmenu_win;
	WINDOW *gamemenu_win;
	WINDOW *dimensionmenu_win;
	WINDOW *timemenu_win;
	
    int n_startmenu_items, n_gamemenu_items, n_dimensionmenu_items, n_timemenu_items, i, c;
	// dimension_option 2010, 3015, 4020, 6030, 8040
	int dimension_option;
	// time_option 20, 40, 60, 80, 100, 120
	int time_option;
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

void set_dimension_option(StartMenu *self, const char *name) {
	if (strcmp(name, "20:10") == 0) {
		self->dimension_option = 2010;
	} else if (strcmp(name, "30:15") == 0) {
		self->dimension_option = 3015;
	} else if (strcmp(name, "40:20") == 0) {
		self->dimension_option = 4020;
	} else if (strcmp(name, "60:30") == 0) {
		self->dimension_option = 6030;
	} else {
		self->dimension_option = 8040;
	}
}

void set_time_option(StartMenu *self, const char *name) {
	if (strcmp(name, "20") == 0) {
		self->time_option = 20;
	} else if (strcmp(name, "40") == 0) {
		self->time_option = 40;
	} else if (strcmp(name, "60") == 0) {
		self->time_option = 60;
	} else if (strcmp(name, "80") == 0) {
		self->time_option = 80;
	} else if (strcmp(name, "100") == 0) {
		self->time_option = 100;
	} else {
		self->time_option = 120;
	}
}

void startmenu_init(StartMenu *self) {

	self->startmenu_items[0] = new_item("New Game", "");
	self->startmenu_items[1] = new_item("Connect to existing", "Not Implemented");
	self->startmenu_items[2] = new_item("Exit", "");
	self->startmenu_items[3] = NULL;
	self->n_startmenu_items = 4;

	self->gamemenu_items[0] = new_item("Classic", "");
	self->gamemenu_items[1] = new_item("Timed", "");
	self->gamemenu_items[2] = NULL;
	self->n_gamemenu_items = 3;

	self->dimensionmenu_items[0] = new_item("20:10", "");
	self->dimensionmenu_items[1] = new_item("30:15", "");
	self->dimensionmenu_items[2] = new_item("40:20", "");
	self->dimensionmenu_items[3] = new_item("60:30", "");
	self->dimensionmenu_items[4] = new_item("80:40", "");
	self->dimensionmenu_items[5] = NULL;
	self->n_dimensionmenu_items = 6;

	self->timemenu_items[0] = new_item("20", "");
	self->timemenu_items[1] = new_item("40", "");
	self->timemenu_items[2] = new_item("60", "");
	self->timemenu_items[3] = new_item("80", "");
	self->timemenu_items[4] = new_item("100", "");
	self->timemenu_items[5] = new_item("120", "");
	self->timemenu_items[6] = NULL;
	self->n_timemenu_items = 7;

	self->dimension_option = 0;
	self->time_option = 0;
	self->startmenu_request = '0';
	self->gamemode_option = '0';

	initscr();
	start_color();
    cbreak();
    noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	init_pair(1, COLOR_GREEN, COLOR_BLUE);

	self->startmenu = new_menu((ITEM **)self->startmenu_items);
	self->gamemenu = new_menu((ITEM **)self->gamemenu_items);
	self->dimensionmenu = new_menu((ITEM **)self->dimensionmenu_items);
	self->timemenu = new_menu((ITEM **)self->timemenu_items);

    self->startmenu_win = newwin(10, 40, 1, 1);
	self->gamemenu_win = newwin(10, 40, 1, 1);
	self->dimensionmenu_win = newwin(10, 40, 1, 1);
	self->timemenu_win = newwin(10, 40, 1, 1);
    keypad(self->startmenu_win, TRUE);
	box(self->startmenu_win, 0, 0);
	box(self->gamemenu_win, 0, 0);
	box(self->dimensionmenu_win, 0, 0);
	box(self->timemenu_win, 0, 0);

    set_menu_win(self->startmenu, self->startmenu_win);
    set_menu_sub(self->startmenu, derwin(self->startmenu_win, 5, 38, 3, 2));
	set_menu_sub(self->gamemenu, derwin(self->gamemenu_win, 5, 38, 3, 2));
	set_menu_sub(self->dimensionmenu, derwin(self->dimensionmenu_win, 5, 38, 3, 2));
	set_menu_sub(self->timemenu, derwin(self->timemenu_win, 5, 38, 3, 2));
    
	print_in_middle(self->startmenu_win, 1, 0, 40, "SNAKE", COLOR_PAIR(1));
	mvprintw(LINES - 2, 0, "F1 to end menu");
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
				if (*self->activemenu == self->startmenu) {
					set_startmenu_request(self, item_name(current));
				} else if (*self->activemenu == self->gamemenu) {
					set_gamemode_option(self, item_name(current));
				} else if (*self->activemenu == self->dimensionmenu) {
					set_dimension_option(self, item_name(current));
					if (self->gamemode_option == 'C') {
						goto menuloop_out;
					}
				} else if (*self->activemenu == self->timemenu) {
					set_time_option(self, item_name(current));
					goto menuloop_out;
				}
				if (*self->activemenu == self->startmenu && self->startmenu_request == 'N') {
					post_menu(self->gamemenu);
					wrefresh(self->gamemenu_win);
					self->activemenu = &self->gamemenu;
				} else if (*self->activemenu == self->gamemenu && self->gamemode_option != '0') {
					post_menu(self->dimensionmenu);
					wrefresh(self->dimensionmenu_win);
					self->activemenu = &self->dimensionmenu;
				} else if (*self->activemenu == self->dimensionmenu && self->gamemode_option == 'T' && self->dimension_option != 0) {
					post_menu(self->timemenu);
					wrefresh(self->timemenu_win);
					self->activemenu = &self->timemenu;
				}
				if (self->startmenu_request == 'Q' || self->startmenu_request == 'C') {
					goto menuloop_out;
				}
                break;
		}
		if (*self->activemenu == self->startmenu) {
			wrefresh(self->startmenu_win);
		} else if (*self->activemenu == self->gamemenu) {
			print_in_middle(self->gamemenu_win, 1, 0, 40, "GAME MODE", COLOR_PAIR(1));
			wrefresh(self->gamemenu_win);
		} else if (*self->activemenu == self->dimensionmenu) {
			print_in_middle(self->dimensionmenu_win, 1, 0, 40, "GAME DIMENSIONS", COLOR_PAIR(1));
        	wrefresh(self->dimensionmenu_win);
		} else if (*self->activemenu == self->timemenu) {
			print_in_middle(self->timemenu_win, 1, 0, 40, "GAME TIME", COLOR_PAIR(1));
			wrefresh(self->timemenu_win);
		} else {
			refresh();
		}
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
		unpost_menu(self->timemenu);
		unpost_menu(self->dimensionmenu);
		unpost_menu(self->gamemenu);
		unpost_menu(self->startmenu);
		free_menu(self->timemenu);
		free_menu(self->dimensionmenu);
		free_menu(self->gamemenu);
		free_menu(self->startmenu);
		for(self->i = 0; self->i < self->n_timemenu_items; ++(self->i)) {
			free_item(self->timemenu_items[self->i]);
		}
		for(self->i = 0; self->i < self->n_dimensionmenu_items; ++(self->i)) {
			free_item(self->dimensionmenu_items[self->i]);
		}
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

int startmenu_getdimension(StartMenu *self) {
	return self->dimension_option;
}

int startmenu_gettime(StartMenu *self) {
	return self->time_option;
}
