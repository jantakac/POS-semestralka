#include "startmenu.h"
#include "client.h"
#include "server.h"

#define TIME_BETWEEN_FRAMES_30FPS 33 // cca 30fps, lower number more fps

void main() {
    Client *client = client_create();
    //este menu ze ak new game ale zatial je newgame vzdy
    client_newgame(client);
    // client_destroy(client);
}