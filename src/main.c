#include "startmenu.h"
#include "client.h"
#include "server.h"


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