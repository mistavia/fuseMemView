#ifndef SOCKET_H
#define SOCKET_H

#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <gio/gio.h>
#include "memory.h"


int socket_setup_bindings();
gboolean socket_received_packet (GIOChannel *source, GIOCondition condition, gpointer data);
gboolean socket_is_packet_valid (gchar *packetData);
gint socket_get_mem_addr (gchar *packetData);
gint socket_get_mem_byte (gchar *packetData);

#endif /* SOCKET_H */

