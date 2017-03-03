#ifndef MACHINE_H
#define MACHINE_H

typedef struct machineDef {
    char *machineName;
    char *machineLongName;
    
    int  numMemBanks;
    
    int  memFrom[10];
    int  memTo[10];
    bool memWriteable[10];
    char *memName[10];
    char *memNameLong[10];
    
} MACHINE_DEF;

MACHINE_DEF *machine_get_info (int machineID);

#endif /* MACHINE_H */

