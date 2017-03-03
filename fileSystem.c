#include "fileSystem.h"

int fileSystem_init_new_log_file() {
    FILE *fileLogFileInit = fopen("fuseMemView.log", "w");
    fprintf(fileLogFileInit, "Initialising new log file\n");
    fclose(fileLogFileInit);
}


int fileSystem_open_log_file() {
    fileLogFile = fopen("fuseMemView.log", "a");
}


int fileSystem_write_log(char *message) {
    
    time_t rawTime;
    struct tm * timeinfo;

    time (&rawTime);
    timeinfo = localtime (&rawTime);
    
    fileSystem_open_log_file();
    fprintf(fileLogFile, "[%02d:%02d:%02d] : %s\n", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, message);
    fileSystem_close_log_file();
}


int fileSystem_close_log_file() {
    fclose(fileLogFile);
}