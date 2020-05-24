//
// Created by rozanecm on 5/6/20.
//

#ifndef CONCUBREAD_PROCESSMANAGER_H
#define CONCUBREAD_PROCESSMANAGER_H


#include <bits/unique_ptr.h>
#include "../Procesos/Proceso.h"

class ProcessManager {
public:
    static std::unique_ptr<Proceso>
    crear_procesos(int cant_panaderos, int cant_pizzeros,
                   int cant_recepcionistas, bool print_debug_msgs);
};


#endif //CONCUBREAD_PROCESSMANAGER_H
