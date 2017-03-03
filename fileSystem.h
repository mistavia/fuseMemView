/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   fileSystem.h
 * Author: root
 *
 * Created on 03 March 2017, 09:51
 */

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
    
FILE   *fileLogFile;
        
int fileSystem_close_log_file();
int fileSystem_init_new_log_file();
int fileSystem_open_log_file();
int fileSystem_write_log(char *message);

#ifdef __cplusplus
}
#endif

#endif /* FILESYSTEM_H */

