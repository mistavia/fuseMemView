#include "memory.h"

int memory_write_byte (int address, int byte) {
    
    virtualMemory[address] = byte;
    
    if (byte > 0) { virtualMemory_updatedFlag[address] = 1; }
    
    // Check if this byte is being watched
    if (virtualMemory_watchFlag[address] == 1) {
        
        int watchLen = virtualMemory_watch[address][0];     // Get the current watch count of the byte
        
        // Clear the pointer if it will exceed 1024 bytes. Note the array remains filled
        if (watchLen == 1024) {
            watchLen = 0;        
        }
        
        // Only update the watch if the value has changed
        if (virtualMemory_watch[address][watchLen] == byte) { return 0; }
        
        virtualMemory_watch[address][0] = watchLen + 1;     // Update the watch count
        virtualMemory_watch[address][watchLen+1] = byte;    // Add the watch byte
    }
    
    //fileSystem_write_log("memory_write_byte() OK");
    
    return 0;
}


int memory_initialise () {

    fileSystem_write_log("memory_initialise() ...");

    // Allocate memory for the byte arrays
    memset(virtualMemory, 0, 65535);
    memset(virtualMemory_watchFlag, 0, 65535);
    memset(virtualMemory_updatedFlag, 0, 65535);
    memset(virtualMemory_watch, 0, 65535);
    
    // The first byte of virtualMemory_watch contains the number of watches, so set to zero
    for (int memCtr=0; memCtr <= 1024; memCtr++) { virtualMemory_watch[memCtr][0] = 0; }
    
    fileSystem_write_log("memory_initialise() OK");
    
    return 0;
}