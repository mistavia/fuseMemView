#ifndef NETWORK_H
#define NETWORK_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int network_get_ip4_addr (char *host);

#endif /* NETWORK_H */

