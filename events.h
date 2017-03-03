/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   events.h
 * Author: andy
 *
 * Created on 28 February 2017, 22:52
 */

#ifndef EVENTS_H
#define EVENTS_H

#ifdef __cplusplus
extern "C" {
#endif
    
#include <glib.h>
#include "window.h"
#include "fuseMemView.h"
#include "machine.h"

gboolean event_monitor_keyboard (GMainLoop *loop);
gboolean event_update_activity_icon ();
gboolean event_draw_screen();

#ifdef __cplusplus
}
#endif

#endif /* EVENTS_H */

