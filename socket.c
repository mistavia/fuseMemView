#include "socket.h"

gint socket_get_mem_byte (gchar *packetData) {
    
    char memByteStr[2], *memErrorCheckStr;
    
    for (int memPtr=0; memPtr<5; memPtr++) { memByteStr[memPtr] = packetData[memPtr+4]; } memByteStr[2] = '\0';
    int memByte = (int)strtol(memByteStr, NULL, 16);
    
    return memByte;
}

gint socket_get_mem_addr (gchar *packetData) {
    
    char memAddrStr[4];
    
    for (int memPtr=0; memPtr<5; memPtr++) { memAddrStr[memPtr] = packetData[memPtr]; } memAddrStr[4] = '\0';
    int memAddr = (int)strtol(memAddrStr, NULL, 16);
    
    return memAddr;
}

gboolean socket_network_read(GIOChannel *source, GIOCondition cond, gpointer data)
{
    GString *s = g_string_new(NULL);
    GError *error;

    GIOStatus ret = g_io_channel_read_line_string(source, s, NULL, NULL);

    if (ret == G_IO_STATUS_ERROR) {
      g_object_unref (data);
    }
    else
        if (strlen(s->str) == 6) {
            
            gint memAddr = socket_get_mem_addr(s->str);
            gint memByte = socket_get_mem_byte(s->str);

            if (memAddr >= 0 && memAddr <= MAX_MEM_SIZE && memByte >= 0 && memByte <=255){
                memory_write_byte(memAddr, memByte);
            }
        }

    return TRUE;
}

gboolean socket_new_connection (GSocketService *service, GSocketConnection *connection, GObject *source_object, gpointer user_data)
{
    g_object_ref (connection);
    
    GSocketAddress *sockaddr = g_socket_connection_get_remote_address(connection, NULL);
    GInetAddress *addr = g_inet_socket_address_get_address(G_INET_SOCKET_ADDRESS(sockaddr));
    guint16 port = g_inet_socket_address_get_port(G_INET_SOCKET_ADDRESS(sockaddr));

//    char *logMessage;
//    sprintf(logMessage, "socket_new_connection() : new connection from %s:%d", g_inet_address_to_string(addr), port);
//    fileSystem_write_log(logMessage);

    GSocket *socket = g_socket_connection_get_socket(connection);

    gint fd = g_socket_get_fd(socket);
    GIOChannel *channel = g_io_channel_unix_new(fd);
    g_io_add_watch(channel, G_IO_IN, (GIOFunc) socket_network_read, connection);
    return TRUE;
}


int socket_setup_bindings() {
    
    fileSystem_write_log("socket_setup_bindings()");
    
    GSocketService *service = g_socket_service_new();

    GInetAddress *address = g_inet_address_new_any(G_SOCKET_FAMILY_IPV4);
    GSocketAddress *socket_address = g_inet_socket_address_new(address, 3000);

    g_socket_listener_add_address(G_SOCKET_LISTENER(service), socket_address, G_SOCKET_TYPE_STREAM, G_SOCKET_PROTOCOL_TCP, NULL, NULL, NULL);

    g_object_unref(socket_address);
    g_object_unref(address);
    g_socket_service_start(service);

    g_signal_connect(service, "incoming", G_CALLBACK(socket_new_connection), NULL);
}


//gboolean socket_network_read(GIOChannel *source, GIOCondition cond, gpointer data) {
//    return TRUE;
//    char *logMessage;
//    
//    fileSystem_write_log("socket_network_read() ...");
//
//    GString *s = g_string_new(NULL);
//    GError *error;
//    GIOStatus ret = g_io_channel_read_line_string(source, s, NULL, NULL);
//  
//    if (ret == G_IO_STATUS_ERROR) {
//        sprintf(logMessage, "Network read failed, %s", error->message);
//        fileSystem_write_log(logMessage);
//        g_object_unref (data);
//    }
//    else if (strlen(s->str) > 0) {
//        
//        //snprintf(logMessage, strlen(s->str)+24, "Received packet data, %s", s->str);
//        //fileSystem_write_log(logMessage);
//        
//        if (socket_is_packet_valid(s->str) && strlen(s->str) == 6) {
//            fileSystem_write_log("Packet data is good");
//            
//            gint memAddr = socket_get_mem_addr(s->str);
//            gint memByte = socket_get_mem_byte(s->str);
//
//            if (memAddr >= 0 && memAddr <= MAX_MEM_SIZE && memByte >= 0 && memByte <=255){
//                //memory_write_byte(memAddr, memByte);
//            }
//            else {
//                fileSystem_write_log("Bad data");
//            }
//        }
//        else {
//            fileSystem_write_log("Bad data");
//        }
//    }
//    fileSystem_write_log("socket_network_read() OK");
//
//    return TRUE;
//}
//
//
//gboolean socket_new_connection(GSocketService *service, GSocketConnection *connection, GObject *source_object, gpointer user_data) {
//
//    g_object_ref (connection);
//    
//    fileSystem_write_log("socket_new_connection()");
//
//    GSocketAddress *sockaddr = g_socket_connection_get_remote_address(connection, NULL);
//    GInetAddress *addr = g_inet_socket_address_get_address(G_INET_SOCKET_ADDRESS(sockaddr));
//    guint16 port = g_inet_socket_address_get_port(G_INET_SOCKET_ADDRESS(sockaddr));
//
//    GSocket *socket = g_socket_connection_get_socket(connection);
//
//    gint fd = g_socket_get_fd(socket);
//    GIOChannel *channel = g_io_channel_unix_new(fd);
//    //g_io_add_watch(channel, G_IO_IN, (GIOFunc) socket_network_read, connection);
//    return TRUE;
//}
//
//
//int socket_setup_bindings() {
//
//    fileSystem_write_log("socket_setup_bindings()");
//
//    GSocketService *service = g_socket_service_new();
//    //GInetAddress *address = g_inet_address_new_from_string("127.0.0.1");
//    GInetAddress *address = g_inet_address_new_any(G_SOCKET_FAMILY_IPV4);
//    GSocketAddress *socket_address = g_inet_socket_address_new(address, 3000);
//    
//    //g_socket_listener_add_address(G_SOCKET_LISTENER(service), socket_address, G_SOCKET_TYPE_STREAM, G_SOCKET_PROTOCOL_TCP, NULL, NULL, NULL);
//    
//    g_socket_listener_add_inet_port (G_SOCKET_LISTENER(service), 3000, NULL, NULL);
//
//    g_object_unref(socket_address);
//    g_object_unref(address);
//    g_socket_service_start(service);
//
//    g_signal_connect(service, "incoming", G_CALLBACK(socket_new_connection), NULL);    
//}
//
//
//gint socket_get_mem_byte (gchar *packetData) {
//    
//    fileSystem_write_log("socket_get_mem_byte()");
//    char *logMessage;
//    snprintf(logMessage, strlen(packetData), "%s", packetData);
//    fileSystem_write_log(logMessage);
//    
//    char memByteStr[2], *memErrorCheckStr;
//    
//    for (int memPtr=0; memPtr<5; memPtr++) { memByteStr[memPtr] = packetData[memPtr+4]; } memByteStr[2] = '\0';
//    int memByte = (int)strtol(memByteStr, NULL, 16);
//    
//    return memByte;
//}
//
//gint socket_get_mem_addr (gchar *packetData) {
//    
//    fileSystem_write_log("socket_get_mem_addr()");
//    char *logMessage;
//    snprintf(logMessage, strlen(packetData), "%s", packetData);
//    fileSystem_write_log(logMessage);
//    
//    char memAddrStr[4];
//    
//    // memAddr
//    for (int memPtr=0; memPtr<5; memPtr++) { memAddrStr[memPtr] = packetData[memPtr]; } memAddrStr[4] = '\0';
//    int memAddr = (int)strtol(memAddrStr, NULL, 16);
//    
//    return memAddr;
//}
//
//
//gboolean socket_is_packet_valid (gchar *packetData) {
//    return TRUE;
//    // Get the packet data ...
//    int byteArray[9], errorCheck[3];
//    for (int memPtr=0; memPtr<10;memPtr++) {
//        char byte = packetData[memPtr];
//        byteArray[memPtr] = (byte > '9')? (byte &~ 0x20) - 'A' + 10: (byte - '0'); // Convert from hex CHR to int
//    }
//    
//    // XOR bytes (1&6), (2&5) & (3&4)
//    errorCheck[0] = byteArray[0]^byteArray[5];
//    errorCheck[1] = byteArray[1]^byteArray[4];
//    errorCheck[2] = byteArray[2]^byteArray[3];
//    
//    // Compare the XOR'd bytes against the last 3 bytes sent
//    if ((errorCheck[0] == byteArray[7]) && (errorCheck[1] == byteArray[8]) && (errorCheck[2] == byteArray[9])) {
//        return TRUE;
//    }
//    else { return FALSE; }
//}