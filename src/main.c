#include "startmenu.h"
#include "client.h"
#include "server.h"

void main() {
    StartMenu *startmenu = startmenu_create();
    Client *client = client_create();
    if (startmenu_getgamemode(startmenu) == 'C') {
        startmenu_destroy(startmenu);
        client_newgame(client, 0, startmenu_getdimension(startmenu) / 100, startmenu_getdimension(startmenu) % 100);
    } else if (startmenu_getgamemode(startmenu) == 'T') {
        startmenu_destroy(startmenu);
        client_newgame(client, startmenu_gettime(startmenu), startmenu_getdimension(startmenu) / 100, startmenu_getdimension(startmenu) % 100);
    } else if (startmenu_getrequest(startmenu) == 'C') {
        startmenu_destroy(startmenu);
        puts("ConnectTE Not Implemented Yet!");
    } else {
        startmenu_destroy(startmenu);
    }
    client_destroy(client);
}