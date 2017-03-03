#include "events.h"


gboolean event_monitor_keyboard (GMainLoop *loop) {
        
    int keyPress = getch();
    if (keyPress > 0 && keyPress != 91 && keyPress !=27) {
        mvprintw(numTerminalRows-2, numTerminalCols-9, "        ");
        
        if (keyPress == 9) { // Tab
            if (currentScreen == SCREEN_MEMMAP) {
                currentMachine_memPage = 0;
                currentMemBlock++;
                if (currentMemBlock == currentMachine_numMemBanks) { currentMemBlock = 0; }
            }
            else if (currentScreen == SCREEN_WATCH) {
                watchSelectedOnScreen++;
                if (watchSelectedOnScreen == watchCount) { watchSelectedOnScreen = 0; }
            }
        }
        
        else if (keyPress == 43) { // + symbol
            if (currentScreen == SCREEN_MEMMAP) {
                currentMachine_memPage++;
            }
        }
        
        else if (keyPress == 48) { // 0
            int currentValue = virtualMemory[16384];
            currentValue++;
            if (currentValue == 256) { currentValue = 0; }
            memory_write_byte(16384, currentValue); // This is a test that increments location 0x4000
        }
        
        else if (keyPress == 65) { // Up arrow
            if (currentScreen == SCREEN_MEMMAP) {
                currentMemRow--;
                if (currentMemRow < 0) { currentMemRow = 0; }
            }
        }
        
        else if (keyPress == 66) { // Down arrow
            if (currentScreen == SCREEN_MEMMAP) {
                currentMemRow++;
            }
        }
        
        else if (keyPress == 67) { // Right arrow
            if (currentScreen == SCREEN_MEMMAP) {
                currentMemCol++;
                if (currentMemCol > (screenBytesPerRow-1)) { currentMemCol = 0; currentMemRow++; }
            }
        }
        
        else if (keyPress == 68) { // Left arrow
            if (currentScreen == SCREEN_MEMMAP) {
                currentMemCol--;
                if (currentMemCol < 0 && currentMemRow == 0) { currentMemCol = 0; }
                else if (currentMemCol < 0 && currentMemRow > 0) { currentMemCol = (screenBytesPerRow-1); currentMemRow--; }
            }
        }
        
        else if (keyPress == 95) { // - symbol
            if (currentScreen == SCREEN_MEMMAP) {
                currentMachine_memPage--;
                if (currentMachine_memPage < 0) { currentMachine_memPage = 0; }
            }
        }
        
        else if (keyPress == 109) { // m
            currentScreen = SCREEN_MEMMAP;
        }
        
        else if (keyPress == 113) {  // q
            mvprintw(numTerminalRows-2, numTerminalCols-9, "QUIT");
            fileSystem_write_log("Shutting down ...");
            echo();
            clear();
            endwin();
            g_source_remove(timerIcon);
            g_source_remove(timerKeyboard);
            g_source_remove(timerMemUpdate);
            g_main_loop_quit(loop);
            fileSystem_write_log("Shut down complete. Goodbye.");
        }
        
        else if (keyPress == 114) { // r
            window_draw_main_screen();
        }
        
        else if (keyPress == 116) { // t
            if (currentScreen == SCREEN_MEMMAP) {
                if (virtualMemory_watchFlag[memMap_selectedByte] == 0) { 
                    watchCount++;
                    virtualMemory_watchFlag[memMap_selectedByte] = 1; 
                }
                else { virtualMemory_watchFlag[memMap_selectedByte] = 0; }
            }
        }
        
        else if (keyPress == 119) { // w
            currentScreen = SCREEN_WATCH;
        }
        
        else {
            char *logMessage;
            printf(logMessage, "event_monitor_keyboard() : Unmapped key %d", keyPress);
            fileSystem_write_log(logMessage);
        }
    }
    return TRUE;
}


gboolean event_update_activity_icon () {
    activityRotatePos++;
    if (activityRotatePos == 5) { activityRotatePos = 1; }
    return TRUE;
}


gboolean event_draw_screen() {
    window_draw_main_screen();
    return TRUE;
}