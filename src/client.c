#include "client.h"

struct Client {
    char map[HEIGHT * WIDTH + 1];
    WINDOW *snake_win;
    int client_socket;
};

int client_connect(Client *self) {

    struct sockaddr_in serv_addr;

    if ((self->client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    if ((connect(self->client_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
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
    int ch;
    char sendkey;
    while ((ch = getch()) != 'x') {
        switch(ch) {
            case KEY_LEFT:
                sendkey = 'l';
                write(self->client_socket, &sendkey, sizeof(char));
                break;
            case KEY_RIGHT:
                sendkey = 'r';
                write(self->client_socket, &sendkey, sizeof(char));
                break;
            case KEY_UP:
                sendkey = 'u';
                write(self->client_socket, &sendkey, sizeof(char));
                break;
            case KEY_DOWN:
                sendkey = 'd';
                write(self->client_socket, &sendkey, sizeof(char));
                break;
        }
    }
    return NULL;
}

void *snake_draw(void *arg) {
    Client *self = (Client *)arg;
    printf("kreslime");
    initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    /*for (int i = 0; i < 10; ++i) {
        clear();
        usleep(200000);
        printw("kreslim");
        refresh();
        usleep(200000);
    }
    clear();
    printw(self->map);
    refresh();*/

    
    self->snake_win = newwin(HEIGHT, WIDTH, 0, 0);
    box(self->snake_win, 0, 0);
    while(1) {
        wrefresh(self->snake_win);
        usleep(200000);
    }
    
    /*
    wrefresh(self->snake_win);
    keypad(self->snake_win, TRUE);
    nodelay(self->snake_win, TRUE);
    
    char recvChar;
    while (1) {
        read(self->client_socket, &recvChar, sizeof(char));
        box(self->snake_win, 0, 0);
        wrefresh(self->snake_win);
        usleep(200000);
    }*/
    return NULL;
}



void client_newgame(Client *self) {
    pid_t p = fork();
    if (p < 0) {
        perror("error fork");
        exit(EXIT_FAILURE);
    } else if (p == 0) {
        Server *server = server_create();
        server_newgame(server);
        server_destroy(server);
    } else {
        //TODO: zmenit sleep na signaly
        puts("slapeme");
        sleep(2);
        if (client_connect(self) < 0) {
            perror("connection failed");
            refresh();
        }
        read(self->client_socket, self->map, HEIGHT * WIDTH + 1);
        puts("prvych 5 prijatej mapy");
        printf("%s\n", self->map);
        pthread_t thread_draw;
        pthread_t thread_send;
        pthread_create(&thread_draw, NULL, snakekey_send, self);
        pthread_create(&thread_send, NULL, snake_draw, self);
        pthread_join(thread_draw, NULL);
        pthread_join(thread_send, NULL);
    }
}