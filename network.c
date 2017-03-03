#include "network.h"

int network_get_ip4_addr (char *host) {
    struct ifaddrs *ifaddr, *ifa;
    int s;
    
    if (getifaddrs(&ifaddr) == -1) { return 1; }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) 
    {
        if (ifa->ifa_addr == NULL) { continue; }  
        //s = getnameinfo(ifa->ifa_addr,sizeof(struct sockaddr_in),host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
        s = getnameinfo(ifa->ifa_addr,sizeof(struct sockaddr_in),host, 1024, NULL, 0, 1);
    }

    freeifaddrs(ifaddr);
    
    return 0;
}