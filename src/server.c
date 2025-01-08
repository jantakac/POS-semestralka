#include "server.h"

struct Server {
    Game *game;
    int listen_socket, connect_socket;
};



void server_test() {
    
    /*
    int recvKey;
    for (int i = 0; i < 15; ++i) {
        read(self->connect_socket, &recvInt, sizeof(int)); // subtract 1 for the null
        printf("%d\n", recvInt);
    }
    write(self->connect_socket, &inter, sizeof(int));
    printf("Hello message sent\n");
    printf("%d\n", recvInt);
    */
    
}

void server_init(Server *self) {
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    if ((self->listen_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(self->listen_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(self->listen_socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(self->listen_socket, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((self->connect_socket = accept(self->listen_socket, (struct sockaddr*)&address, &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
}

Server *server_create() {
    Server *self = malloc(sizeof(Server));
    server_init(self);
    return self;
}

void server_destroy(Server *self) {
    if (self) {
        close(self->connect_socket);
        close(self->listen_socket);
        free(self);
    }
}



void server_newgame(Server *self) {
    puts("server new game");
    self->game = game_create();
    char *map = game_generatemap(self->game);
    puts("prvych 5 odoslanej mapy");
    printf("%s\n", map);
    if (write(self->connect_socket, map, WIDTH * HEIGHT + 1) < 0) {
        perror("map send error");
    }
    char keytosend;
    while (!game_isgameover(self->game)) {
        read(self->connect_socket, &keytosend, sizeof(char));
        game_setkey(self->game, keytosend);
        game_logic(self->game);
    }
    game_destroy(self->game);
}

