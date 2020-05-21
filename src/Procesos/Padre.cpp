//
// Created by rozanecm on 5/21/20.
//

#include <sys/wait.h>
#include <iostream>
#include "Padre.h"

void Padre::ejercer_tarea() {
    reportarse();

    bool volvieron_todos = false;
    while (sigint_handler.getGracefulQuit() == 0 and not volvieron_todos){
        int status = 0;
        auto wait_val = wait(&status);
        if(wait_val < 0){
            volvieron_todos = true;
        }
    }
}

void Padre::reportarse() {
    canal_debug.abrir();
    std::string mensaje = "Soy el padre con pid " + std::to_string(getpid()) + '\n';
    canal_debug.escribir(static_cast<const void *>(mensaje.c_str()), mensaje.length());
    canal_debug.cerrar();
}
