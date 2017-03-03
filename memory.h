/* 
 * File:   memory.h
 * Author: andy
 *
 * Created on 01 March 2017, 21:50
 */

#ifndef MEMORY_H
#define MEMORY_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <string.h>
#include "fileSystem.h"

#define MAX_MEM_SIZE 65535
    
// These char arrays can be shorter as ROM will never be watched, but the memory size will change with 128k+
    
int virtualMemory[MAX_MEM_SIZE];
int virtualMemory_updatedFlag[MAX_MEM_SIZE];
int virtualMemory_watchFlag[MAX_MEM_SIZE];
int virtualMemory_watch[MAX_MEM_SIZE][1024];

int memory_write_byte (int address, int byte);
int memory_initialise ();

#ifdef __cplusplus
}
#endif

#endif /* MEMORY_H */

