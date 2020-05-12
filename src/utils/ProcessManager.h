//
// Created by rozanecm on 5/6/20.
//

#ifndef CONCUBREAD_PROCESSMANAGER_H
#define CONCUBREAD_PROCESSMANAGER_H


#include "enums.h"
#include "DebugPrint.h"

class ProcessManager {
public:
    static ProcessIdentification
    crear_procesos(int cant_panaderos, int cant_pizzeros, int cant_recepcionistas, DebugPrint *debug_printer);
};


#endif //CONCUBREAD_PROCESSMANAGER_H
