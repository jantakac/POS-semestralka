#ifndef SERVER_H
#define SERVER_H

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "constants.h"
#include "game.h"


typedef struct Server Server;
void server_init(Server *self);
Server *server_create();
void server_destroy(Server *self);
void server_newgame(Server *self);
#endif