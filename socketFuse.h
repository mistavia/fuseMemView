#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>	//printf
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <glib.h>
#include <gio/gio.h>

GSocketConnection * connection;
GSocketClient * client;
    
int socket_send_packet(int address, int byte);

#endif /* SOCKET_H */

