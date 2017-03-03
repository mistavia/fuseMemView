/* 
 * File:   main.c
 * Author: andy
 *
 * Created on 26 February 2017, 20:07
 */

#include "fuseMemView.h"

int main(int argc, char** argv) {
 
    int row, col;
    int startx, starty, width, height;
    gboolean isAppRunning = FALSE;
    
    fileSystem_init_new_log_file();
    fileSystem_write_log("Starting application");
    
    // Initialise current machine
    currentMachine_numMemBanks = 0;
    
    watchSelectedMemAddr   = 0;
    watchSelectedOnScreen  = 0;
    memMap_selectedByte    = 0;
    watchCount             = 0;
    currentMachine_memPage = 0;
    debugLogCount          = 0;
    screenBytesPerRow      = 0;
    currentMemRow          = 0;
    currentMemCol          = 0;
    currentMemBlock        = 0;
    currentScreen          = SCREEN_MEMMAP;
    
    memory_initialise();
            
    initscr();
    raw();
    noecho();
    nodelay(stdscr, TRUE);
    window_setup();
    refresh();
    socket_setup_bindings();
    
    GMainLoop *appMainLoop = g_main_loop_new(NULL, isAppRunning);

    timerKeyboard  = g_timeout_add(50,  (GSourceFunc) event_monitor_keyboard, appMainLoop);
    timerIcon      = g_timeout_add(200, (GSourceFunc) event_update_activity_icon, appMainLoop);
    timerMemUpdate = g_timeout_add(50,  (GSourceFunc) event_draw_screen, appMainLoop);
        
    g_main_loop_run(appMainLoop);
}