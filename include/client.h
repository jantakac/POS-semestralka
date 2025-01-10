#ifndef CLIENT_H
#define CLIENT_H

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <ncurses.h>
#include <pthread.h>
#include "constants.h"
#include "server.h"

typedef struct Client Client;
int client_connect(Client *self);
Client *client_create();
void client_destroy(Client *self);
void client_newgame(Client *self);
#endif