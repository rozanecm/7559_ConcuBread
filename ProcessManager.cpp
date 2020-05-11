//
// Created by rozanecm on 5/6/20.
//

#include "ProcessManager.h"
#include "DebugPrint.h"
#include <unistd.h>

 ProcessIdentification ProcessManager::crear_procesos(int cant_panaderos, int cant_pizzeros, int cant_recepcionistas) {
    /* Creacion panaderos */
    for (int i = 0; i < cant_panaderos; ++i){
        DebugPrint::print("for loop vuelta: " + std::to_string(i));
        if (fork() == 0) {
            DebugPrint::print("New PANADERO created with pid " + std::to_string(getpid()));
            return MtroPanadero;
        }
    }
    /* Creacion pizzeros */
    for (int i = 0; i < cant_pizzeros; ++i){
        DebugPrint::print("for loop vuelta: " + std::to_string(i));
        if (fork() == 0) {
            DebugPrint::print("New PIZZERO created with pid " + std::to_string(getpid()));
            return MtroPizzero;
        }
    }
    /* Creacion recepcionistas */
    for (int i = 0; i < cant_recepcionistas; ++i){
        DebugPrint::print("for loop vuelta: " + std::to_string(i));
        if (fork() == 0) {
            DebugPrint::print("New RECEPCIONISTA created with pid " + std::to_string(getpid()));
            return Recepcionista;
        }
    }
    /* Creacion espec. masa madre */
    if (fork() == 0) {
        DebugPrint::print("Espec. Masa Madre created with pid " + std::to_string(getpid()));
        return EspecialistaMasaMadre;
    }
    return Padre;
}
