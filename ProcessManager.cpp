//
// Created by rozanecm on 5/6/20.
//

#include "ProcessManager.h"
#include "DebugPrint.h"
#include <unistd.h>

ProcessFilialIdentification ProcessManager::crear_panaderos(int cant_panaderos) {
    for (int i = 0; i < cant_panaderos; ++i){
        DebugPrint::print("for loop vuelta: " + std::to_string(i));
        if (fork() == 0) {
            DebugPrint::print("New PANADERO created with pid " + std::to_string(getpid()));
            return Hijo;
        }
//        sleep(1);
    }
    return Padre;
}
