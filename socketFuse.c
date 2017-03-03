#include "socketFuse.h"

    
int socket_send_packet(int address, int byte) {
    
    GError * error = NULL;

    if (client == NULL) {
        //printf("Setting up TCP connection ...\n");
        client = g_socket_client_new();
        connection = g_socket_client_connect_to_host (client, (gchar*)"127.0.0.1", 3000, NULL, &error);
    }
        
    // Compile the message
    char addressString[5];
    snprintf(addressString, 5, "%04X", address);
    
    char byteString[3];
    snprintf(byteString, 3, "%02X", byte);
        
    char messageString[7];
    messageString[0] = addressString[0];
    messageString[1] = addressString[1];
    messageString[2] = addressString[2];
    messageString[3] = addressString[3];
    messageString[4] = byteString[0];
    messageString[5] = byteString[1];
    messageString[6] = '\0';
        
    if (sizeof(messageString) == 7 && connection) {
        GOutputStream * ostream = g_io_stream_get_output_stream (G_IO_STREAM (connection));
        g_output_stream_write  (ostream, messageString, 7, NULL, &error);
    }
    
    //g_socket_close(connection, NULL);
    
    return 0;
}