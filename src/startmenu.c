#include "startmenu.h"



struct StartMenu {
	ITEM **startmenu_items;
	char *startmenu_choices[4];
	MENU *startmenu;
    WINDOW *startmenu_win;
	int c;
    int n_startmenu_choices, i;
	
	// startmenu_request 'N' = NEW GAME, 'C' = CONNECT TO EXISTING, 'Q' = EXIT
	char startmenu_request;
	
	// gamemode_option 'C' = CLASSIC, 'T' = TIMED
	char gamemode_option;
};

void set_startmenu_request(StartMenu *self, const char* name) {
	if (strcmp(name, "New Game") == 0) {
		self->startmenu_request = 'N';
	} else if (strcmp(name, "Connect to existing") == 0) {
		self->startmenu_request = 'C';
	} else {
		self->startmenu_request = 'Q';
	}
}

void startmenu_init(StartMenu *self) {
	self->startmenu_choices[0] = "New Game";
	self->startmenu_choices[1] = "Connect to existing";
	self->startmenu_choices[2] = "Exit";
	self->startmenu_choices[3] = NULL;

	initscr();
	start_color();
    cbreak();
    noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_GREEN, COLOR_BLUE);

	
    self->n_startmenu_choices = ARRAY_SIZE(self->startmenu_choices);
    // musi byt null terminated to pole
    self->startmenu_items = (ITEM **)calloc(self->n_startmenu_choices, sizeof(ITEM *));
    for (self->i = 0; self->i < self->n_startmenu_choices; ++(self->i)) {
        self->startmenu_items[self->i] = new_item(self->startmenu_choices[self->i], "");
	}

	self->startmenu = new_menu((ITEM **)self->startmenu_items);

    self->startmenu_win = newwin(10, 40, 4, 4);
    keypad(self->startmenu_win, TRUE);
     
    set_menu_win(self->startmenu, self->startmenu_win);
    set_menu_sub(self->startmenu, derwin(self->startmenu_win, 6, 38, 3, 1));

    box(self->startmenu_win, 0, 0);
	print_in_middle(self->startmenu_win, 1, 0, 40, "SNAKE", COLOR_PAIR(1));
	mvwaddch(self->startmenu_win, 2, 0, ACS_LTEE);
	mvwhline(self->startmenu_win, 2, 1, ACS_HLINE, 38);
	mvwaddch(self->startmenu_win, 2, 39, ACS_RTEE);
	mvprintw(LINES - 2, 0, "F1 to exit");
	refresh();

	post_menu(self->startmenu);
	wrefresh(self->startmenu_win);

	while((self->c = wgetch(self->startmenu_win)) != KEY_F(1))
	{       
        switch(self->c) {	
            case KEY_DOWN:
				menu_driver(self->startmenu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(self->startmenu, REQ_UP_ITEM);
				break;
            case 10:
                ITEM *current = current_item(self->startmenu);
				set_startmenu_request(self, item_name(current));
				goto menuloop_out;
                break;
		}
        wrefresh(self->startmenu_win);
	}	
menuloop_out:
	unpost_menu(self->startmenu);
	free_menu(self->startmenu);
	for(self->i = 0; self->i < self->n_startmenu_choices; ++(self->i)) {
		free_item(self->startmenu_items[self->i]);
	}
	endwin();
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
		free(self);
	}
}

char startmenu_getrequest(StartMenu *self) {
	return self->startmenu_request;
}

char menu_getgamemode(StartMenu *self) {
	return self->gamemode_option;
}

