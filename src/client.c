#include "client.h"

struct Client {
    char map[MAXWIDTH * MAXHEIGHT + 1];
    SnakeData snakedata;
    WINDOW *snake_win;
    WINDOW *score_win;
    int client_socket;
    int gameheight;
    int gamewidth;
};

int client_connect(Client *self) {

    struct sockaddr_in serv_addr;

    if ((self->client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("\nInvalid address / Address not supported \n");
        return -1;
    }
    if ((connect(self->client_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        perror("\nConnection Failed \n");
        return -1;
    }
    return 0;
}


Client *client_create() {
    Client *self = malloc(sizeof(Client));
    return self;
}


void client_destroy(Client *self) {
    if (self) {
        close(self->client_socket);
        free(self);
    }
}

void *snakekey_send(void *arg) {
    Client *self = (Client *)arg;
    puts("posielame");
    int ch;
    char sendkey = 'u';    
    while (1) {
        ch = getch();
        switch(ch) {
            case KEY_LEFT:
                if (sendkey != 'r') {
                    sendkey = 'l';
                }
                break;
            case KEY_RIGHT:
                if (sendkey != 'l') {
                    sendkey = 'r';
                }
                break;
            case KEY_UP:
                if (sendkey != 'd') {
                    sendkey = 'u';
                }
                break;
            case KEY_DOWN:
                if (sendkey != 'u') {
                    sendkey = 'd';
                }
                break;
            case 'p':
                sendkey = 'p';
                break;
            default:
                break;
        }
        write(self->client_socket, &sendkey, sizeof(char));
        usleep(200000);
        if (self->snakedata.gameover > 0) {
            break;
        }
    }
    return NULL;
}

void *snake_draw(void *arg) {
    Client *self = (Client *)arg;
    puts("kreslime");
    initscr();
    cbreak();
    noecho();
    clear();
    curs_set(0);
    refresh();
    self->snake_win = newwin(self->gameheight, self->gamewidth, 1, 1);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    wclear(self->snake_win);

    // border okolo
    WINDOW *border_win = newwin(self->gameheight + 2, self->gamewidth + 2, 0, 0);
    wclear(border_win);
    box(border_win, 0, 0);
    wrefresh(border_win);
    // endborder

    self->score_win = newwin(3, self->gamewidth + 2, self->gameheight + 2, 0);
    wclear(self->score_win);
    wrefresh(self->score_win);
    
    for (int i = 0; i < self->gamewidth; ++i) {
        for (int j = 0; j < self->gameheight; ++j) {
            if (self->map[self->gamewidth * j + i] == 'X') {
                mvwprintw(self->snake_win, j, i, "X");
            }
        }
    }
    
    self->snakedata.gameover = -1;
    do {
        read(self->client_socket, &self->snakedata, sizeof(SnakeData));
        
        mvwprintw(self->snake_win, self->snakedata.y, self->snakedata.x, "O");
        for (int i = 0; i < self->snakedata.snaketail_len; ++i) {
            mvwprintw(self->snake_win, self->snakedata.snaketail_y[i], self->snakedata.snaketail_x[i], "o");
        }
        mvwprintw(self->snake_win, self->snakedata.fruity, self->snakedata.fruitx, "*");


        if (self->snakedata.gameover > 0) {
            wclear(self->snake_win);
            mvwprintw(self->snake_win, self->gameheight / 2, self->gamewidth / 2 - 5, "Game Over!");
            mvwprintw(self->snake_win, self->gameheight / 2 + 1, self->gamewidth / 2 - 8, "Final score: %d", self->snakedata.score);
            wrefresh(self->snake_win);
            sleep(5);
            break;
        }

        mvwprintw(self->score_win, 0, 1, "Score: %d", self->snakedata.score);
        mvwprintw(self->score_win, 1, 1, "Time elapsed: %d", self->snakedata.elapsed_time);
        wrefresh(self->score_win);
        wrefresh(self->snake_win);
        usleep(200000);



        mvwprintw(self->snake_win, self->snakedata.y, self->snakedata.x, " ");
        for (int i = 0; i < self->snakedata.snaketail_len; ++i) {
            mvwprintw(self->snake_win, self->snakedata.snaketail_y[i], self->snakedata.snaketail_x[i], " ");
        }

    } while(self->snakedata.gameover == 0);
    mvwprintw(self->score_win, 1, 0, "                              ");
    wclear(self->snake_win);
    delwin(border_win);
    delwin(self->score_win);
    delwin(self->snake_win);
    endwin();
    return NULL;
}


void client_newgame(Client *self, int gameduration_secs, int gamewidth, int gameheight) {
    pid_t p = fork();
    if (p < 0) {
        perror("error fork");
        exit(EXIT_FAILURE);
    } else if (p == 0) {
        Server *server = server_create();
        server_newgame(server, gameduration_secs, gamewidth, gameheight);
        server_destroy(server);
    } else {
        puts("waiting for server");
        sleep(2);
        if (client_connect(self) < 0) {
            perror("connection failed");
            refresh();
        }
        self->gamewidth = gamewidth;
        self->gameheight = gameheight;
        read(self->client_socket, self->map, gamewidth * gameheight + 1);
        puts("prvych 5 prijatej mapy");
        printf("%s\n", self->map);
        pthread_t thread_draw;
        pthread_t thread_send;
        pthread_create(&thread_draw, NULL, snake_draw, self);
        pthread_create(&thread_send, NULL, snakekey_send, self);
        pthread_join(thread_draw, NULL);
        pthread_join(thread_send, NULL);
    }
}