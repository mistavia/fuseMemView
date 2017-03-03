#include "machine.h"
#include "window.h"

MACHINE_DEF *machine_get_info (int machineID) {
 
    MACHINE_DEF *machine48;
    machine48 = (MACHINE_DEF *)g_malloc(sizeof(MACHINE_DEF));
    
    machine48->machineName     = "48k";
    machine48->machineLongName = "ZX Spectrum 48k";
    
    machine48->numMemBanks     = 7;
    
    machine48->memName[0]      = "Screen";        machine48->memFrom[0] = 16384; machine48->memTo[0] = 22527; machine48->memWriteable[0] = TRUE;
    machine48->memName[1]      = "Colour";        machine48->memFrom[1] = 22528; machine48->memTo[1] = 23295; machine48->memWriteable[1] = TRUE;
    machine48->memName[2]      = "Prnt bffr";     machine48->memFrom[2] = 23296; machine48->memTo[2] = 23551; machine48->memWriteable[2] = TRUE;
    machine48->memName[3]      = "System";        machine48->memFrom[3] = 23552; machine48->memTo[3] = 23743; machine48->memWriteable[3] = TRUE;
    machine48->memName[4]      = "Reserved";      machine48->memFrom[4] = 23744; machine48->memTo[4] = 23754; machine48->memWriteable[4] = TRUE;
    machine48->memName[5]      = "Free";          machine48->memFrom[5] = 23755; machine48->memTo[5] = 65367; machine48->memWriteable[5] = TRUE;
    machine48->memName[6]      = "Reserved";      machine48->memFrom[6] = 65368; machine48->memTo[6] = 65535; machine48->memWriteable[6] = TRUE;
            
    return machine48;
}