/* 
 * File:   main.h
 * Author: andy
 *
 * Created on 26 February 2017, 20:09
 */

#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

#include "events.h"
#include "network.h"
#include "machine.h"
#include "window.h"
#include "socket.h"
#include "memory.h"
#include "fileSystem.h"
    
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

#define VA_PROGRAM_NAME "fuseMemView"
#define VA_VERSION_NUM  "1.00 alpha"

    
// I'm happy with these variables names ...

    // Timer references (used to cancel them all at quit)
    gint timerIcon, timerKeyboard, timerMemUpdate;
    
    // Watches
    int  watchSelectedOnScreen;  // The current watch selected (with the tab key). This is the watch number, not the memory location
    int  watchSelectedMemAddr;    // This is the memory address of the selected watch on screen
    int  watchCount;             // How many watches have been activated

    // Misc
    char ipAddr[1025];    // Holds the current IP address
        
// These need to be confirmed / renamed ...

int currentMachine_numMemBanks, currentMachine_drawMemFrom, currentMachine_drawMemTo, currentMachine_memPage;
int numTerminalRows, numTerminalCols, activityRotatePos, currentMemBlock, currentScreen, currentMemRow, currentMemCol;
int screenBytesPerRow, debugLogCount;

int memMap_selectedByte;

char listOfWatchAddr[1024];


#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */