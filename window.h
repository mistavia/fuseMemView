/* 
 * File:   window.h
 * Author: andy
 *
 * Created on 28 February 2017, 09:42
 */

#ifndef WINDOW_H
#define WINDOW_H

#ifdef __cplusplus
extern "C" {
#endif

#include <glib.h>
#include "fuseMemView.h"
#include "machine.h"
#include "memory.h"

#define SCREEN_WELCOME 1
#define SCREEN_MEMMAP 2
#define SCREEN_WATCH  3

int window_setup ();
int window_draw_main_screen();
int window_draw_menu();
int window_draw_horizontal_line (int rowNum);
int window_draw_machine_map (bool drawMachineNameOnly);
int window_draw_memory ();
int window_draw_activity_icon();
int window_draw_mem_info();
int window_draw_watches();
int window_draw_watch_history();


#ifdef __cplusplus
}
#endif

#endif /* WINDOW_H */

