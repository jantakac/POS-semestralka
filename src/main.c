#include "startmenu.h"
#include "client.h"
#include "server.h"

#define TIME_BETWEEN_FRAMES_30FPS 33 // cca 30fps, lower number more fps

void main() {
    StartMenu *startmenu = startmenu_create();
    Client *client = client_create();
    if (startmenu_getgamemode(startmenu) == 'C') {
        client_newgame(client);
    } else if (startmenu_getgamemode(startmenu) == 'T') {
        puts("Timed Not Implemented Yet!");
    } else if (startmenu_getrequest(startmenu) == 'C') {
        puts("ConnectTE Not Implemented Yet!");
    }
    client_destroy(client);
}