//
// Created by rozanecm on 5/6/20.
//

#include "ProcessManager.h"
#include "../Procesos/DebugPrinter.h"
#include "../Procesos/Actores/Panadero.h"
#include "../Procesos/Actores/Pizzero.h"
#include "../Procesos/Actores/Recepcionista.h"
#include "../Procesos/Actores/EspecialistaMasaMadre.h"
#include "../Procesos/Padre.h"
#include <unistd.h>
#include <bits/unique_ptr.h>

std::unique_ptr<Proceso>
 ProcessManager::crear_procesos(int cant_panaderos, int cant_pizzeros, int cant_recepcionistas, bool print_debug_msgs) {
    /* Creacion panaderos */
    for (int i = 0; i < cant_panaderos; ++i){
        if (fork() == 0) {
            return std::make_unique<Panadero>(i);
        }
    }
    /* Creacion pizzeros */
    for (int i = 0; i < cant_pizzeros; ++i){
        if (fork() == 0) {
            return std::make_unique<Pizzero>(i);
        }
    }
    /* Creacion recepcionistas */
    for (int i = 0; i < cant_recepcionistas; ++i){
        if (fork() == 0) {
            return std::make_unique<Recepcionista>(i);
        }
    }
    /* Creacion espec. masa madre */
    if (fork() == 0) {
        return std::make_unique<EspecialistaMasaMadre>();
    }
    /* Creacion Debug Printer */
    if (fork() == 0) {
        return std::make_unique<DebugPrinter>(print_debug_msgs);
    }
    return std::make_unique<Padre>();
}
