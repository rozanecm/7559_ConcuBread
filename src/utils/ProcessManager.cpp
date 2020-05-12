//
// Created by rozanecm on 5/6/20.
//

#include "ProcessManager.h"
#include "DebugPrint.h"
#include <unistd.h>

 ProcessIdentification
 ProcessManager::crear_procesos(int cant_panaderos, int cant_pizzeros, int cant_recepcionistas, DebugPrint *debug_printer) {
    /* Creacion panaderos */
    for (int i = 0; i < cant_panaderos; ++i){
        if (fork() == 0) {
            debug_printer->print("New PANADERO created with pid " + std::to_string(getpid()) + '\n');
            return MtroPanadero;
        }
    }
    /* Creacion pizzeros */
    for (int i = 0; i < cant_pizzeros; ++i){
        if (fork() == 0) {
            debug_printer->print("New PIZZERO created with pid " + std::to_string(getpid()) + '\n');
            return MtroPizzero;
        }
    }
    /* Creacion recepcionistas */
    for (int i = 0; i < cant_recepcionistas; ++i){
        if (fork() == 0) {
            debug_printer->print("New RECEPCIONISTA created with pid " + std::to_string(getpid()) + '\n');
            return Recepcionista;
        }
    }
    /* Creacion espec. masa madre */
    if (fork() == 0) {
        debug_printer->print("Espec. Masa Madre created with pid " + std::to_string(getpid()) + '\n');
        return EspecialistaMasaMadre;
    }
    return Padre;
}