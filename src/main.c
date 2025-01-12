#include "startmenu.h"
#include "client.h"
#include "server.h"


void main() {
    StartMenu *startmenu = startmenu_create();
    Client *client = client_create();
    if (startmenu_getgamemode(startmenu) == 'C') {
        client_newgame(client, 0, startmenu_getdimension(startmenu) / 100, startmenu_getdimension(startmenu) % 100);
    } else if (startmenu_getgamemode(startmenu) == 'T') {
        client_newgame(client, startmenu_gettime(startmenu), startmenu_getdimension(startmenu) / 100, startmenu_getdimension(startmenu) % 100);
    } else if (startmenu_getrequest(startmenu) == 'C') {
        puts("ConnectTE Not Implemented Yet!");
    }
    startmenu_destroy(startmenu);
    client_destroy(client);
}