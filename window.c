#include "window.h"

int window_setup () {
    
    fileSystem_write_log("window_setup()");

    activityRotatePos = 1;
    
    start_color();
    init_color(COLOR_BLACK, 0, 0, 0);
    init_color(COLOR_MAGENTA, 900, 100, 900);
    
    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_BLUE);
    init_pair(5, COLOR_WHITE, COLOR_YELLOW);
      
    network_get_ip4_addr(ipAddr);
    window_draw_main_screen();
}


int window_draw_main_screen () {
    getmaxyx(stdscr, numTerminalRows, numTerminalCols);
    
    clear();
    
    attron(COLOR_PAIR(1));
    window_draw_horizontal_line(0);
    mvprintw(1, 1, "fuseMemView, " VA_VERSION_NUM " [listening on %s] [screen %d,%d]", ipAddr, numTerminalRows, numTerminalCols);
    window_draw_horizontal_line(2);
    
    window_draw_menu();
    window_draw_activity_icon ();
    
    if (currentScreen == SCREEN_MEMMAP) {
        window_draw_machine_map(FALSE);
        window_draw_memory();
        window_draw_mem_info();
    }
    else if (currentScreen == SCREEN_WATCH) {
        window_draw_machine_map(TRUE);
        window_draw_watches();
        window_draw_watch_history();
    }
}


int window_draw_watches() {
    
    int startCol = 1, startRow = 6;
    int rowCtr=0;
    
    attron(COLOR_PAIR(2));
    for (int watchCtr=16384; watchCtr < 65535; watchCtr++) {
        if (virtualMemory_watchFlag[watchCtr] > 0) {

            if (rowCtr == watchSelectedOnScreen) { 
                watchSelectedMemAddr = watchCtr;
                attron(COLOR_PAIR(4)); 
            }
            else { attron(COLOR_PAIR(2)); }
            
            char memAddrHex[5], valueHex[3];
            snprintf(memAddrHex, 5, "%04X", watchCtr);
            snprintf(valueHex, 3, "%02X", virtualMemory[watchCtr]);
            mvprintw(startRow+rowCtr, startCol, "%s:%d = %s:%03d", memAddrHex, watchCtr, valueHex, virtualMemory[watchCtr]);
            rowCtr++;
        }
    }
    return 0;
}


int window_draw_watch_history() {
    
    int startCol = 22, startRow = 6;
    int rowCtr=startRow, colCtr = 0;
    
    int numberOfHostoricalWatches = virtualMemory_watch[watchSelectedMemAddr][0];
    
    attron(COLOR_PAIR(2));
    
    //for (int historyCtr=1; historyCtr <= virtualMemory_watch[watchSelectedMemAddr][0]; historyCtr++) {
    for (int historyCtr=virtualMemory_watch[watchSelectedMemAddr][0]; historyCtr > 0 ; historyCtr--) {
        int colToPrint = startCol + (colCtr*3);
        
        if (colToPrint > (numTerminalCols-startCol)+18) {
            colCtr = 0; rowCtr++;
            colToPrint = startCol + (colCtr*3);
        }
        
        mvprintw(rowCtr, colToPrint, "%02X ", virtualMemory_watch[watchSelectedMemAddr][historyCtr]);
        colCtr++;
    }
    
    return 0;
    
    for (int historyCtr=1; historyCtr <= virtualMemory_watch[virtualMemory_watchFlag[watchSelectedOnScreen]][0]; historyCtr++) {
        char historyValHex[3];
        snprintf(historyValHex, 5, "%02X", virtualMemory_watch[virtualMemory_watchFlag[watchSelectedOnScreen]][historyCtr]);

        mvprintw(startRow+rowCtr, startCol + 18 + (historyCtr*3), "%s", historyValHex);
    }
    rowCtr++;
    return 0;
}


int window_draw_machine_map (bool drawMachineNameOnly) {
 
    int rowStart = 4, colStart = 1 ;
    
    MACHINE_DEF *machineDetails;
    machineDetails = (MACHINE_DEF *)g_malloc(sizeof(MACHINE_DEF));
    
    
    attron(COLOR_PAIR(1));
    machineDetails = machine_get_info(1);
        
    attron(COLOR_PAIR(3));
    mvprintw(rowStart, colStart, "%s", machineDetails->machineLongName);
    
    if (drawMachineNameOnly == TRUE) { return 0; }

    currentMachine_numMemBanks = machineDetails->numMemBanks;

    for (int memCtr=0; memCtr <= machineDetails->numMemBanks-1; memCtr++) {
        char memFromHex[5], memToHex[5];
        snprintf(memFromHex, 5, "%04X", machineDetails->memFrom[memCtr]);
        snprintf(memToHex,   5, "%04X", machineDetails->memTo[memCtr]);
        
        if (memCtr == currentMemBlock) {
            currentMachine_drawMemFrom = machineDetails->memFrom[memCtr];
            currentMachine_drawMemTo   = machineDetails->memTo[memCtr];
            attron(COLOR_PAIR(4));
        }
        else { attron(COLOR_PAIR(2)); }
        
        mvprintw((rowStart+2)+memCtr, colStart, "%s-%s %s", memFromHex, memToHex, machineDetails->memName[memCtr]);
    }
    
    return 0;
}


int window_draw_memory () {
        
    // Determine how many bytes can be show based on number of columns available
    if      (numTerminalCols > 0   && numTerminalCols <= 81)  { screenBytesPerRow = 8;  }
    else if (numTerminalCols > 81  && numTerminalCols <= 106) { screenBytesPerRow = 16; }
    else if (numTerminalCols > 106 && numTerminalCols <= 129) { screenBytesPerRow = 24; }
    else if (numTerminalCols > 129 && numTerminalCols <= 154) { screenBytesPerRow = 32; }
    else if (numTerminalCols > 154 && numTerminalCols <= 178) { screenBytesPerRow = 40; }
    else if (numTerminalCols > 178 && numTerminalCols <= 300) { screenBytesPerRow = 48; }
    
    int rowStart = 4, colStart = 23, numRows = numTerminalRows - 9;
    
    // How many bytes can be shown per screen?
    int bytesPerScreen = numRows * screenBytesPerRow;
    
    // Clear any prevous memory maps
    int charSize = numTerminalCols - colStart;
    char blankLine[charSize];
    for (int charCtr=0; charCtr < charSize; charCtr++) {
        blankLine[charCtr] = ' ';
    }
    blankLine[charSize] = '\0';
    attron(COLOR_PAIR(2));
    for (int rowCtr = 0; rowCtr <= numRows; rowCtr++) {
        mvprintw(rowStart+rowCtr, colStart, blankLine);
    }
    
    attron(COLOR_PAIR(2));
    for (int rowCtr = 0; rowCtr <= numRows; rowCtr++) {
        
        int memStart = currentMachine_drawMemFrom + (screenBytesPerRow*rowCtr) + (bytesPerScreen * currentMachine_memPage);
    
        if (memStart > currentMachine_drawMemTo) { break; }
        
        char memStartHex[5];

        attron(COLOR_PAIR(2));
        snprintf(memStartHex, 5, "%04X", memStart);
        mvprintw(rowStart+rowCtr, colStart, "%s:%05d", memStartHex, memStart);
        
        for (int colCtr = 0; colCtr < screenBytesPerRow; colCtr++) {
            
            if (memStart+colCtr <= currentMachine_drawMemTo) {
            
                if (rowCtr == currentMemRow && colCtr == currentMemCol) { 
                    memMap_selectedByte = memStart+colCtr;
                    attron(COLOR_PAIR(4));
                }
                else { 
                    if (virtualMemory_watchFlag[memStart+colCtr] > 0) { attron(COLOR_PAIR(5)); }
                    else { attron(COLOR_PAIR(2)); }
                }

                char memByte[3];
                if (virtualMemory_updatedFlag[memStart+colCtr] == 1) { 
                    snprintf(memByte, 3, "%02X", virtualMemory[memStart+colCtr]);
                }
                else {
                    memcpy(memByte, "--", 2);
                }

                mvprintw(rowStart+rowCtr, (colStart+11)+(colCtr*3), memByte);
            }
        }
    }
    
    return 0;
}

int window_draw_mem_info () {
    
    int currentMemByte = memMap_selectedByte;
    
    int currentValue = virtualMemory[currentMemByte], rowStart = 15;
    char *isWatched = "";
    
    if (virtualMemory_watchFlag[currentMemByte] > 0) { isWatched = "yes"; } else { isWatched = "no"; }
    
    char memAddrHex[5]; snprintf(memAddrHex, 5, "%04X", currentMemByte);
    char memValHex[3]; snprintf(memValHex, 3, "%02X", currentValue);
    
    attron(COLOR_PAIR(1));
    mvprintw(rowStart,   1, "location: 0x%s ", memAddrHex);
    mvprintw(rowStart+1, 1, "     b10: %05d ", currentMemByte);
    mvprintw(rowStart+3, 1, "   value: 0x%s ", memValHex);
    mvprintw(rowStart+4, 1, "     b10: %d   ", currentValue);
    mvprintw(rowStart+5, 1, "      b8: "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(currentValue));
    mvprintw(rowStart+7, 1, "   watch: %s   ", isWatched);
    mvprintw(rowStart+8, 1, " updated: %d   ", virtualMemory_updatedFlag[currentMemByte]);

    return 0;
}


int window_draw_horizontal_line (int rowNum) {
    for (int colCtr=0; colCtr < numTerminalCols; colCtr++) {
        mvprintw(rowNum, colCtr, "-");
    }
    return 0;
}


int window_draw_menu() {
    attron(COLOR_PAIR(1));
    window_draw_horizontal_line(numTerminalRows-3);
    mvprintw(numTerminalRows-2, 1, "[m]emory map, [w]atches, [q]uit");
    window_draw_horizontal_line(numTerminalRows-1);
    
    if (currentScreen == SCREEN_MEMMAP) {
        attron(COLOR_PAIR(3));
        mvprintw(numTerminalRows -7, 1, "arrows: navigate");
        mvprintw(numTerminalRows -6, 1, "   tab: switch bank");
        mvprintw(numTerminalRows -5, 1, "     t: toggle watch");
    }
    else if (currentScreen == SCREEN_WATCH) {
        attron(COLOR_PAIR(3));
        mvprintw(numTerminalRows -7, 1, "   tab: switch watch");
    }
}


int window_draw_activity_icon () {
    
    int rowNum = 1;
    
    attron(COLOR_PAIR(3));
    
    if (activityRotatePos == 1)                             { mvprintw(rowNum, numTerminalCols-6, "  []  "); }
    if (activityRotatePos == 2 || activityRotatePos == 4)   { mvprintw(rowNum, numTerminalCols-6, " [--] "); }
    if (activityRotatePos == 3)                             { mvprintw(rowNum, numTerminalCols-6, "[----]"); }
}